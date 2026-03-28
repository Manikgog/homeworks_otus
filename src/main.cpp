#include <iostream>
#include <vector>

#include "singlelinked_list.h"
#include "../src/simple_vector.h"

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
	// Vector<int> source{1, 2, 3, 4, 5};
	// printContainer(source);
	//
	// Vector<int> dest{10, 20, 30};
	// printContainer(dest);
	//
	// dest = std::move(source);
	// printContainer(source);
	// printContainer(dest);

	SingleLinkedList<size_t> list1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	SingleLinkedList<size_t> list2{100, 200, 300};
	// Act
	list1.swap(list2);

	for (size_t i = 0; i < list1.Size(); ++i) {
		std::cout << list1[i] << " ";
	}

	std::cout << std::endl;

	for (size_t i = 0; i < list2.Size(); ++i) {
		std::cout << list2[i] << " ";
	}


	return 0;
}