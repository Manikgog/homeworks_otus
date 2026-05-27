// Read files and prints top k word by frequency - Thread pool version

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <condition_variable>
#include <functional>

const size_t TOPK = 10;

using Counter = std::map<std::string, std::size_t>;

class ThreadPool {
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;

public:
    ThreadPool(size_t threads) : stop(false) {
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock, [this] {
                            return this->stop || !this->tasks.empty();
                        });
                        if (this->stop && this->tasks.empty()) {
                            return;
                        }
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    template<class F>
    void enqueue(F&& f) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            tasks.emplace(std::forward<F>(f));
        }
        condition.notify_one();
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }
};

std::string tolower(const std::string &str);
void process_file(const std::string& filename, Counter& counter, std::mutex& mutex);
void print_topk(std::ostream& stream, const Counter&, const size_t k);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    auto start = std::chrono::high_resolution_clock::now();

    Counter freq_dict;
    std::mutex dict_mutex;

    // Определяем оптимальное количество потоков
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads > argc - 1)
        num_threads = argc - 1;
    if (num_threads == 0)
        num_threads = 2;

    ThreadPool pool(num_threads);
    std::vector<std::thread> sync_threads; // Для ожидания завершения

    std::atomic<int> files_remaining(argc - 1);
    std::mutex wait_mutex;
    std::condition_variable wait_cv;

    // Добавляем задачи в пул потоков
    for (int i = 1; i < argc; ++i) {
        pool.enqueue([&, filename = std::string(argv[i])]() {
            std::ifstream input(filename);
            if (!input.is_open()) {
                std::cerr << "Failed to open file " << filename << '\n';
            } else {
                Counter local_counter;

                std::for_each(std::istream_iterator<std::string>(input),
                              std::istream_iterator<std::string>(),
                              [&local_counter](const std::string &s) {
                                  ++local_counter[tolower(s)];
                              });

                {
                    std::lock_guard<std::mutex> lock(dict_mutex);
                    for (const auto& [word, count] : local_counter) {
                        freq_dict[word] += count;
                    }
                }
            }

            // Уменьшаем счетчик и уведомляем при завершении
            if (--files_remaining == 0) {
                std::lock_guard<std::mutex> lock(wait_mutex);
                wait_cv.notify_one();
            }
        });
    }

    // Ожидаем завершения всех задач
    {
        std::unique_lock<std::mutex> lock(wait_mutex);
        wait_cv.wait(lock, [&] { return files_remaining == 0; });
    }

    print_topk(std::cout, freq_dict, TOPK);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_us.count() << " us\n";
}

std::string tolower(const std::string &str) {
    std::string lower_str;
    lower_str.reserve(str.size());
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
}

void print_topk(std::ostream& stream, const Counter& counter, const size_t k) {
    if (counter.empty()) {
        stream << "No words found\n";
        return;
    }

    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    size_t actual_k = std::min(k, words.size());

    std::partial_sort(
        std::begin(words), std::begin(words) + actual_k, std::end(words),
        [](auto lhs, auto rhs) { return lhs->second > rhs->second; });

    std::for_each(
        std::begin(words), std::begin(words) + actual_k,
        [&stream](const Counter::const_iterator &pair) {
            stream << std::setw(4) << pair->second << " " << pair->first << '\n';
        });
}