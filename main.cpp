#include "test_vector.h"
#include "test_singlelinkedlist.h"
#include "test_doublelinkedlist.h"

template <typename T>
void printContainer(T& v)
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


int main() {
	TestVector();
	TestSingleLinkedList();
	TestDoubleLinkedList();

	Vector<int> vec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	printContainer(vec);
	std::cout << vec.size() << std::endl;
	size_t index = 0;
	vec.erase(index + 2);
	vec.erase(index + 3);
	vec.erase(index + 4);
	printContainer(vec);
	vec.insert(10, 0);
	printContainer(vec);
	vec.insert(20, 4);
	printContainer(vec);
	vec.push_back(30);
	printContainer(vec);

	Vector<int> vec2{10, 20, 30, 40, 50, 60, 70, 80};
	vec = vec2;
	printContainer(vec);
	printContainer(vec2);



	std::cout << "--------------------------" << std::endl;
	SingleLinkedList<int> s{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	printContainer(s);
	std::cout << s.Size() << std::endl;
	auto its = s.begin();
	std::advance(its, 1);
	s.EraseAfter(its);
	std::advance(its, 1);
	s.EraseAfter(its);
	std::advance(its, 1);
	s.EraseAfter(its);
	printContainer(s);
	s.PushFront(10);
	printContainer(s);
	auto middle_sl = s.begin();
	std::advance(middle_sl, 3);
	s.InsertAfter(middle_sl, 20);
	printContainer(s);
	s.PushBack(30);
	printContainer(s);

	std::cout << "--------------------------" << std::endl;
	DoubleLinkedList<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	printContainer(v);
	std::cout << v.Size() << std::endl;
	auto it = v.begin();
	std::advance(it, 2);
	v.Erase(it);
	std::advance(it, 2);
	v.Erase(it);
	std::advance(it, 2);
	v.Erase(it);
	printContainer(v);
	v.PushFront(10);
	printContainer(v);
	auto middle = v.begin();
	std::advance(middle, 3);
	v.Insert(middle, 20);
	printContainer(v);
	v.PushBack(30);
	printContainer(v);

	return 0;
}