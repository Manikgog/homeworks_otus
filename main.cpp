#include <algorithm>
#include <iostream>
#include <limits>
#include <thread>
#include <vector>

#include "CRC32.hpp"
#include "IO.hpp"

/// @brief Переписывает последние 4 байта значением value
void replaceLastFourBytes(std::vector<char> &data, uint32_t value) {
  std::copy_n(reinterpret_cast<const char *>(&value), 4, data.end() - 4);
}

// функтор для проверки скорости параллельного вычисления для выбора оптимального количества потоков для окончательного вычисления
struct hack_block_for_dynamic_test {
  void operator()(unsigned int start_index
                  , unsigned int end_index
                  , std::vector<char> original_vector) {
    auto prefix_crc32 = crc32(original_vector.data(), original_vector.size()-4);
    prefix_crc32 = ~prefix_crc32;
    for (unsigned long i = start_index; i < end_index; ++i) {
      // Заменяем последние четыре байта на значение i
      replaceLastFourBytes(original_vector, static_cast<uint32_t>(i));
      // Вычисляем CRC32 текущего вектора result
      crc32(original_vector.data()+(original_vector.size()-4), 4, prefix_crc32);
    }
  }
};

/**
 * функция для определения оптимального количества потоков
 * @param num_threads - максимальное количество потоков
 * @param original_vector - вектор для вычисления crc32
 * @return
 */
unsigned int find_optimal_number_of_threads(unsigned int num_threads, const std::vector<char>& original_vector) {

    auto start = std::chrono::high_resolution_clock::now();
    unsigned int number = 1'000'000;
    std::thread thread_1 = std::thread(hack_block_for_dynamic_test(), 0, number, original_vector);
    thread_1.join();
    auto end = std::chrono::high_resolution_clock::now();
    auto time_spent = end - start;
    auto min_time_spent = time_spent.count();
    unsigned int optimal_number_of_threads = 1;
    // в цикле замеряем время выполнения вычислений различным количеством потоков от 2 до num_threads
    for (unsigned int i = 2; i <= num_threads; ++i) {
        start = std::chrono::high_resolution_clock::now();
        std::vector<std::thread> threads(i-1);
        const unsigned int number_ops_per_thread = number / i;
        for (unsigned int j = 0; j < (i-1); ++j) {
            unsigned int start_index = j * number_ops_per_thread;
            unsigned int end_index = (j + 1) * number_ops_per_thread;
            threads[j] = std::thread(hack_block_for_dynamic_test(), start_index, end_index, original_vector);
        }
        const unsigned int start_index = i * number_ops_per_thread;
        hack_block_for_dynamic_test()(start_index, number, original_vector);
        for (auto it = threads.begin(); it != threads.end(); ++it) {
            it->join();
        }
        end = std::chrono::high_resolution_clock::now();
        time_spent = end - start;
        auto current_time_spent = time_spent.count();
        //std::cout << i << " потока: " << current_time_spent << std::endl;
        if (current_time_spent < min_time_spent) {
            min_time_spent = current_time_spent;
            optimal_number_of_threads = i;
        }
    }
    return optimal_number_of_threads;
}


struct hack_block {
  void operator()(unsigned int start_index
                  , long unsigned int end_index
                  , uint32_t originalCrc32
                  , std::vector<char> original_vector
                  , std::vector<char>& result) {
    auto prefix_crc32 = crc32(original_vector.data(), original_vector.size()-4);
    prefix_crc32 = ~prefix_crc32;
    for (unsigned long i = start_index; i < end_index; ++i) {
      // Заменяем последние четыре байта на значение i
      replaceLastFourBytes(original_vector, static_cast<uint32_t>(i));
      // Вычисляем CRC32 текущего вектора result
      auto currentCrc32 = crc32(original_vector.data()+(original_vector.size()-4), 4, prefix_crc32);
      if (currentCrc32 == originalCrc32) {
        result = original_vector;
        return;
      }
    }
    result.emplace_back();
  }
};


/**
 * @brief Формирует новый вектор с тем же CRC32, добавляя в конец оригинального
 * строку injection и дополнительные 4 байта
 * @details При формировании нового вектора последние 4 байта не несут полезной
 * нагрузки и подбираются таким образом, чтобы CRC32 нового и оригинального
 * вектора совпадали
 * @param original оригинальный вектор
 * @param injection произвольная строка, которая будет добавлена после данных
 * оригинального вектора
 * @return новый вектор
 */
std::vector<char> hack(const std::vector<char> &original,
                       const std::string &injection) {

  const uint32_t originalCrc32 = crc32(original.data(), original.size());
  std::cout << "исходный crc32: " << originalCrc32 << std::endl;
  // вставка дополнительной строки в конец вектора плюс ешё 4 байта для записи числа
  std::vector<char> result(original.size() + injection.size() + 4);
  auto it = std::copy(original.begin(), original.end(), result.begin());
  std::copy(injection.begin(), injection.end(), it);
  // определение количества потоков для параллельного выполнения вычислений
  constexpr size_t maxVal = std::numeric_limits<uint32_t>::max();

  constexpr unsigned long min_per_thread = 25;
  constexpr unsigned int max_threads = (maxVal + min_per_thread - 1) / min_per_thread;
  const unsigned int hardware_threads = std::thread::hardware_concurrency();
  const unsigned int num_threads = std::min(hardware_threads!=0?hardware_threads:2,max_threads);
  const unsigned int optimal_threads_number = find_optimal_number_of_threads(num_threads, original);
  // вычисления количества операций для каждого потока, кроме последнего
  const unsigned int number_ops_per_thread = maxVal / optimal_threads_number;

  std::vector<std::thread> threads(num_threads-1);  // создание вектора потоков

  std::vector<std::vector<char>> results(num_threads);  // создание векторов результатов вычислений для определения в каком потоке crc32 совпал с исходным
  unsigned int i = 0;
  // запуск потоков с передачей в них диапазона чисел для подстановки в последние 4 байта
  for (; i < (num_threads - 1); ++i) {
    unsigned int start_index = i * number_ops_per_thread;
    unsigned int end_index = (i + 1) * number_ops_per_thread;
    threads[i] = std::thread(hack_block(), start_index, end_index, originalCrc32, result, std::ref(results[i]));
  }
  const unsigned int start_index = i * number_ops_per_thread;
  hack_block()(start_index, maxVal+1, originalCrc32, result, results[num_threads-1]);
  // ожидание всех потоков
  for (auto it = threads.begin(); it != threads.end(); ++it) {
    it->join();
  }
  std::vector<char> r;
  // определение в каком из векторов нужный результат
  for (auto it = results.begin(); it != results.end(); ++it) {
    if (it->size() > 1) {
      r = *it;
    }
  }
  // если вектор r все-таки пустой, то crc32 подобрать не удалось
  if (r.empty()) {
    throw std::logic_error("Can't hack");
  }
  return r;
}

int main(int argc, char **argv) {

  if (argc != 3) {
    std::cerr << "Call with two args: " << argv[0]
              << " <input file> <output file>\n";
    return 1;
  }

  try {
    const std::vector<char> data = readFromFile(argv[1]);
    const std::vector<char> badData = hack(data, "He-he-he");
    uint32_t originalCrc32 = crc32(badData.data(), badData.size());
    std::cout << "конечный crc32: " << originalCrc32 << std::endl;
    for (const auto &c : badData) {
      std::cout << c;
    }
    std::cout << std::endl;
    writeToFile(argv[2], badData);
  } catch (std::exception &ex) {
    std::cerr << ex.what() << '\n';
    return 2;
  }
  return 0;
}
