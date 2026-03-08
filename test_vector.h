#pragma once

#include <iostream>
#include "simple_vector.h"

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

void TestVector()
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