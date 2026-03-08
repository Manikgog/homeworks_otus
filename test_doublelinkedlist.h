#pragma once

#include <cassert>
#include "doublelinked_list.h"

inline void TestDoubleLinkedList() {
    struct DeletionSpy {
        ~DeletionSpy() {
            if (deletion_counter_ptr) {
                ++(*deletion_counter_ptr);
            }
        }
        int* deletion_counter_ptr = nullptr;
    };

    // Проверка PopFront
    {
        DoubleLinkedList<int> numbers{ 3, 14, 15, 92, 6 };
        numbers.PopFront();
        assert((numbers == DoubleLinkedList<int>{14, 15, 92, 6}));

        DoubleLinkedList<DeletionSpy> list;
        list.PushFront(DeletionSpy{});
        int deletion_counter = 0;
        list.begin()->deletion_counter_ptr = &deletion_counter;
        assert(deletion_counter == 0);
        list.PopFront();
        assert(deletion_counter == 1);
    }

    // Доступ к позиции, предшествующей begin
    {
        DoubleLinkedList<int> empty_list;
        const auto& const_empty_list = empty_list;
        assert(empty_list.before_begin() == empty_list.cbefore_begin());
        assert(++empty_list.before_begin() == empty_list.begin());
        assert(++empty_list.cbefore_begin() == const_empty_list.begin());

        DoubleLinkedList<int> numbers{ 1, 2, 3, 4 };
        const auto& const_numbers = numbers;
        assert(numbers.before_begin() == numbers.cbefore_begin());
        assert(++numbers.before_begin() == numbers.begin());
        assert(++numbers.cbefore_begin() == const_numbers.begin());
    }

    // Вставка элемента после указанной позиции
    {  // Вставка в пустой список
        {
            DoubleLinkedList<int> lst;
            const auto inserted_item_pos = lst.Insert(lst.before_begin(), 123);
            assert((lst == DoubleLinkedList<int>{123}));
            assert(inserted_item_pos == lst.begin());
            assert(*inserted_item_pos == 123);
        }

        // Вставка в непустой список
        {
            DoubleLinkedList<int> lst{ 1, 2, 3 };
            auto inserted_item_pos = lst.Insert(lst.before_begin(), 123);

            assert(inserted_item_pos == lst.begin());
            assert(inserted_item_pos != lst.end());
            assert(*inserted_item_pos == 123);
            assert((lst == DoubleLinkedList<int>{123, 1, 2, 3}));

            inserted_item_pos = lst.Insert(lst.begin(), 555);
            assert(++DoubleLinkedList<int>::Iterator(lst.begin()) == inserted_item_pos);
            assert(*inserted_item_pos == 555);
            assert((lst == DoubleLinkedList<int>{123, 555, 1, 2, 3}));
        };
    }

    // Вспомогательный класс, бросающий исключение после создания N-копии
    struct ThrowOnCopy {
        ThrowOnCopy() = default;
        explicit ThrowOnCopy(int& copy_counter) noexcept
            : countdown_ptr(&copy_counter) {
        }
        ThrowOnCopy(const ThrowOnCopy& other)
            : countdown_ptr(other.countdown_ptr)  //
        {
            if (countdown_ptr) {
                if (*countdown_ptr == 0) {
                    throw std::bad_alloc();
                }
                else {
                    --(*countdown_ptr);
                }
            }
        }
        // Присваивание элементов этого типа не требуется
        ThrowOnCopy& operator=(const ThrowOnCopy& rhs) = delete;
        // Адрес счётчика обратного отсчёта. Если не равен nullptr, то уменьшается при каждом копировании.
        // Как только обнулится, конструктор копирования выбросит исключение
        int* countdown_ptr = nullptr;
    };

    // Проверка обеспечения строгой гарантии безопасности исключений
    {
        bool exception_was_thrown = false;
        for (int max_copy_counter = 10; max_copy_counter >= 0; --max_copy_counter) {
            DoubleLinkedList<ThrowOnCopy> list{ ThrowOnCopy{}, ThrowOnCopy{}, ThrowOnCopy{} };
            try {
                int copy_counter = max_copy_counter;
                list.Insert(list.cbegin(), ThrowOnCopy(copy_counter));
                assert(list.Size() == 4u);
            }
            catch (const std::bad_alloc&) {
                exception_was_thrown = true;
                assert(list.Size() == 3u);
                break;
            }
        }
        assert(exception_was_thrown);
    }

    {
        {
            DoubleLinkedList<int> lst{ 1, 2, 3, 4 };
            const auto item_after_erased = lst.Erase(lst.cbegin());
            assert((lst == DoubleLinkedList<int>{2, 3, 4}));
            assert(item_after_erased == lst.begin());
        }
        {
            DoubleLinkedList<int> lst{ 1, 2, 3, 4 };
            auto pos = ++(++lst.cbegin());
            const auto item_after_erased = lst.Erase(pos);
            assert((lst == DoubleLinkedList<int>{1, 2, 4}));
            assert(item_after_erased == --lst.end());
        }
        {
            DoubleLinkedList<DeletionSpy> list{ DeletionSpy{}, DeletionSpy{}, DeletionSpy{} };
            auto after_begin = list.begin();
            int deletion_counter = 0;
            after_begin->deletion_counter_ptr = &deletion_counter;
            assert(deletion_counter == 0u);
            list.Erase(list.cbegin());
            assert(deletion_counter == 1u);
        }
    }

    // Проверка работы оператора []
    {
        DoubleLinkedList<int> lst{ 1, 2, 3, 4 };
        int element = lst[1];
        assert(element == 2);
        try {
            int element = lst[4];
        } catch (const std::out_of_range& e) {
            assert(std::string(e.what()) == "DoubleLinkedList out of range");
        }
    }
}


template <typename T>
void printDoubleLinkedList(T& v)
{
    bool is_first = true;
    for (const auto& elem : v)
    {
        if (!is_first)
            std::cout << ", ";
        is_first = false;
        std::cout << elem;
    }
    std::cout << std::endl;
}