#include <cassert>
#include <iostream>
#include "simple_vector.h"
#include "singlelinked_list.h"

void TestPushBack()
{
	Vector<int> vec;
	vec.push_back(12);
	assert(vec[0] == 12 && vec.size() == 1);
	vec.push_back(10);
	assert(vec[1] == 10 && vec.size() == 2);
	vec.push_back(8);
	assert(vec[2] == 8 && vec.size() == 3);
	vec.push_back(6);
	assert(vec[3] == 6 && vec.size() == 4);
	vec.push_back(4);
	assert(vec[4] == 4 && vec.size() == 5);
	vec.push_back(2);
	assert(vec[5] == 2 && vec.size() == 6);
	vec.push_back(0);
	assert(vec[6] == 0 && vec.size() == 7);
}

void TestPopBack()
{
	Vector<int> vec;
	vec.push_back(12);
	vec.push_back(10);
	vec.push_back(8);
	vec.push_back(6);
	vec.push_back(4);
	vec.push_back(2);
	vec.push_back(0);
	vec.pop_back();
	assert(vec.size() == 6);
	vec.pop_back();
	assert(vec.size() == 5);
	vec.pop_back();
	assert(vec.size() == 4);
	vec.pop_back();
	assert(vec.size() == 3);
	vec.pop_back();
	assert(vec.size() == 2);
	vec.pop_back();
	assert(vec.size() == 1);
	vec.pop_back();
	assert(vec.size() == 0);
}

void TestFront()
{
	Vector<int> vec;
	vec.push_back(12);
	vec.push_back(10);
	vec.push_back(8);
	vec.push_back(6);
	vec.push_back(4);
	vec.push_back(2);
	vec.push_back(0);
	assert(vec.front() == 12);
}

void TestInsert()
{
	Vector<int> vec;
	vec.push_back(12);
	vec.push_back(10);
	vec.push_back(8);
	vec.push_back(6);
	vec.push_back(4);
	vec.push_back(2);
	vec.push_back(0);
	vec.insert(21, 0);
	assert(vec.size() == 8);
	assert(*(vec.begin() + 0) == 21);
	vec.insert(7, 3);
	assert(vec.size() == 9);
	assert(*(vec.begin() + 3) == 7);
	vec.insert(-1, 9);
	assert(vec.size() == 10);
	assert(*(vec.begin() + 9) == -1);
}

void TestAt()
{
	Vector<int> vec;
	vec.push_back(12);
	vec.push_back(10);
	vec.push_back(8);
	vec.push_back(6);
	vec.push_back(4);
	vec.push_back(2);
	vec.push_back(0);
	for (int i = 0; i < vec.size(); i++)
	{
		assert(vec[i] == vec.at(i));
	}
}

void Test_rbegin()
{
	Vector<int> vec;
	vec.push_back(12);
	vec.push_back(10);
	vec.push_back(8);
	vec.push_back(6);
	vec.push_back(4);
	vec.push_back(2);
	vec.push_back(0);
	assert(*(vec.rbegin()) == 0);
	assert(vec.rbegin() == vec.end() - 1);
}

void Test_end()
{
	Vector<int> vec;
	vec.push_back(12);
	vec.push_back(10);
	vec.push_back(8);
	vec.push_back(6);
	vec.push_back(4);
	vec.push_back(2);
	vec.push_back(0);
	assert(vec.begin() + vec.size() == vec.end());
}

void TestAccessToElementVector()
{
	Vector<int> vec;
	vec.push_back(12);
	vec.push_back(10);
	vec.push_back(8);
	vec.push_back(6);
	vec.push_back(4);
	vec.push_back(2);
	vec.push_back(0);
	for (int i = 0; i < vec.size(); i++)
	{
		vec[i] = i + 20;
	}
	for (int i = 0; i < vec.size(); i++)
	{
		assert(vec[i] == i + 20);
	}
}

void Test_erase()
{
	Vector<int> vec;
	vec.push_back(12);
	vec.push_back(10);
	vec.push_back(8);
	vec.push_back(6);
	vec.push_back(4);
	vec.push_back(2);
	vec.push_back(0);
	assert(*(vec.begin()) == 12);
	vec.erase(0);
	assert(*(vec.begin()) == 10);
	vec.erase(2);
	assert(*(vec.begin() + 2) == 4);
	vec.erase(vec.size() - 1);
	assert(*(vec.end() - 1) == 2);
}

void TestOperatorEqual()
{
	Vector<int> vec;

	vec.push_back(12);
	vec.push_back(10);
	vec.push_back(8);
	vec.push_back(6);
	vec.push_back(4);
	vec.push_back(2);
	vec.push_back(0);

	Vector<int> vec1 = vec;
	assert(vec.size() == vec1.size());
	assert(vec.begin() != vec1.begin());
	for (int i = 0; i < vec.size(); i++)
	{
		assert(vec[i] == vec1[i]);
	}
}

void TestCopyConstructor()
{
	Vector<int> vec;

	vec.push_back(12);
	vec.push_back(10);
	vec.push_back(8);
	vec.push_back(6);
	vec.push_back(4);
	vec.push_back(2);
	vec.push_back(0);

	Vector<int> vec1(vec);
	assert(vec.size() == vec1.size());
	assert(vec.begin() != vec1.begin());
	for (int i = 0; i < vec.size(); i++)
	{
		assert(vec[i] == vec1[i]);
	}
}

void Test_swap()
{
	Vector<int> v1;
	Vector<int> v2;
	for (size_t i = 0; i < 10; i++)
	{
		v1.push_back(i + 1);
	}
	for (size_t i = 0; i < 10; i++)
	{
		v2.push_back(i + 10);
	}
	v1.swap(v2);
	for (size_t i = 0; i < 10; i++)
	{
		assert(v1[i] == (i + 10));
	}
	for (size_t i = 0; i < 10; i++)
	{
		assert(v2[i] == (i + 1));
	}
}

void Test()
{
	TestPushBack();
	TestPopBack();
	TestFront();
	TestInsert();
	TestAt();
	Test_rbegin();
	Test_end();
	TestAccessToElementVector();
	Test_erase();
	TestOperatorEqual();
	TestCopyConstructor();
	Test_swap();
}


template <typename T>
void printVector(T& v)
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


// Эта функция проверяет работу класса SingleLinkedList
void TestList() {
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
        SingleLinkedList<int> numbers{ 3, 14, 15, 92, 6 };
        numbers.PopFront();
        assert((numbers == SingleLinkedList<int>{14, 15, 92, 6}));

        SingleLinkedList<DeletionSpy> list;
        list.PushFront(DeletionSpy{});
        int deletion_counter = 0;
        list.begin()->deletion_counter_ptr = &deletion_counter;
        assert(deletion_counter == 0);
        list.PopFront();
        assert(deletion_counter == 1);
    }

    // Доступ к позиции, предшествующей begin
    {
        SingleLinkedList<int> empty_list;
        const auto& const_empty_list = empty_list;
        assert(empty_list.before_begin() == empty_list.cbefore_begin());
        assert(++empty_list.before_begin() == empty_list.begin());
        assert(++empty_list.cbefore_begin() == const_empty_list.begin());

        SingleLinkedList<int> numbers{ 1, 2, 3, 4 };
        const auto& const_numbers = numbers;
        assert(numbers.before_begin() == numbers.cbefore_begin());
        assert(++numbers.before_begin() == numbers.begin());
        assert(++numbers.cbefore_begin() == const_numbers.begin());
    }

    // Вставка элемента после указанной позиции
    {  // Вставка в пустой список
        {
            SingleLinkedList<int> lst;
            const auto inserted_item_pos = lst.InsertAfter(lst.before_begin(), 123);
            assert((lst == SingleLinkedList<int>{123}));
            assert(inserted_item_pos == lst.begin());
            assert(*inserted_item_pos == 123);
        }

        // Вставка в непустой список
        {
            SingleLinkedList<int> lst{ 1, 2, 3 };
            auto inserted_item_pos = lst.InsertAfter(lst.before_begin(), 123);

            assert(inserted_item_pos == lst.begin());
            assert(inserted_item_pos != lst.end());
            assert(*inserted_item_pos == 123);
            assert((lst == SingleLinkedList<int>{123, 1, 2, 3}));

            inserted_item_pos = lst.InsertAfter(lst.begin(), 555);
            assert(++SingleLinkedList<int>::Iterator(lst.begin()) == inserted_item_pos);
            assert(*inserted_item_pos == 555);
            assert((lst == SingleLinkedList<int>{123, 555, 1, 2, 3}));
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
            SingleLinkedList<ThrowOnCopy> list{ ThrowOnCopy{}, ThrowOnCopy{}, ThrowOnCopy{} };
            try {
                int copy_counter = max_copy_counter;
                list.InsertAfter(list.cbegin(), ThrowOnCopy(copy_counter));
                assert(list.GetSize() == 4u);
            }
            catch (const std::bad_alloc&) {
                exception_was_thrown = true;
                assert(list.GetSize() == 3u);
                break;
            }
        }
        assert(exception_was_thrown);
    }

    // Удаление элементов после указанной позиции
    {
        {
            SingleLinkedList<int> lst{ 1, 2, 3, 4 };
            const auto& const_lst = lst;
            const auto item_after_erased = lst.EraseAfter(const_lst.cbefore_begin());
            assert((lst == SingleLinkedList<int>{2, 3, 4}));
            assert(item_after_erased == lst.begin());
        }
        {
            SingleLinkedList<int> lst{ 1, 2, 3, 4 };
            const auto item_after_erased = lst.EraseAfter(lst.cbegin());
            assert((lst == SingleLinkedList<int>{1, 3, 4}));
            assert(item_after_erased == (++lst.begin()));
        }
        {
            SingleLinkedList<int> lst{ 1, 2, 3, 4 };
            const auto item_after_erased = lst.EraseAfter(++(++lst.cbegin()));
            assert((lst == SingleLinkedList<int>{1, 2, 3}));
            assert(item_after_erased == lst.end());
        }
        {
            SingleLinkedList<DeletionSpy> list{ DeletionSpy{}, DeletionSpy{}, DeletionSpy{} };
            auto after_begin = ++list.begin();
            int deletion_counter = 0;
            after_begin->deletion_counter_ptr = &deletion_counter;
            assert(deletion_counter == 0u);
            list.EraseAfter(list.cbegin());
            assert(deletion_counter == 1u);
        }
    }
}



int main() {
	//Test();
	//Vector<double> v1{ 1.2, 3.4 };
	//printVector(v1);
	TestList();
	return 0;
}