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