#pragma once

#include "dsexceptions.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>

template<typename Object>
class Vector
{
	static const int SPARE_CAPACITY = 2;

  public:
	explicit Vector(int initSize = 0) : theSize{initSize}, theCapacity{initSize + SPARE_CAPACITY}
	{
		objects = new Object[theCapacity];
	}

	Vector(const Vector &rhs) : theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{nullptr}
	{
		objects = new Object[theCapacity];
		for (int k = 0; k < theSize; ++k)
			objects[k] = rhs.objects[k];
	}

	Vector &operator=(const Vector &rhs)
	{
		Vector copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	~Vector() { delete[] objects; }

	Vector(Vector &&rhs) : theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{rhs.objects}
	{
		rhs.objects = nullptr;
		rhs.theSize = 0;
		rhs.theCapacity = 0;
	}

	Vector &operator=(Vector &&rhs)
	{
		std::swap(theSize, rhs.theSize);
		std::swap(theCapacity, rhs.theCapacity);
		std::swap(objects, rhs.objects);

		return *this;
	}

	bool empty() const { return size() == 0; }
	int size() const { return theSize; }
	int capacity() const { return theCapacity; }

	Object &operator[](int index)
	{
#ifndef NO_CHECK
		if (index < 0 || index >= size())
			throw ArrayIndexOutOfBoundsException{};
#endif
		return objects[index];
	}

	const Object &operator[](int index) const
	{
#ifndef NO_CHECK
		if (index < 0 || index >= size())
			throw ArrayIndexOutOfBoundsException{};
#endif
		return objects[index];
	}

	void resize(int newSize)
	{
		if (newSize > theCapacity)
			reserve(newSize * 2);
		theSize = newSize;
	}

	void reserve(int newCapacity)
	{
		if (newCapacity < theSize)
			return;

		Object *newArray = new Object[newCapacity];
		for (int k = 0; k < theSize; ++k)
			newArray[k] = std::move(objects[k]);

		theCapacity = newCapacity;
		std::swap(objects, newArray);
		delete[] newArray;
	}

	// Stacky stuff
	void push_back(const Object &x)
	{
		if (theSize == theCapacity)
			reserve(2 * theCapacity + 1);
		objects[theSize++] = x;
	}
	// Stacky stuff
	void push_back(Object &&x)
	{
		if (theSize == theCapacity)
			reserve(2 * theCapacity + 1);
		objects[theSize++] = std::move(x);
	}

	void pop_back()
	{
		if (empty())
			throw UnderflowException{};
		--theSize;
	}

	const Object &back() const
	{
		if (empty())
			throw UnderflowException{};
		return objects[theSize - 1];
	}

	// Iterator stuff: not bounds checked
	typedef Object *iterator;
	typedef const Object *const_iterator;

	iterator begin() { return &objects[0]; }
	const_iterator begin() const { return &objects[0]; }
	iterator end() { return &objects[size()]; }
	const_iterator end() const { return &objects[size()]; }

	iterator find(const Object &t_obj);
	void insert(iterator t_pos, const Object &t_obj);
	void erase(iterator t_obj);
	void print();

  private:
	int theSize;
	int theCapacity;
	Object *objects;
};

template<typename Object>
inline Object *Vector<Object>::find(const Object &t_obj)
{
	iterator it = begin();
	iterator stop = end();
	while (it != stop) {
		if (*it == t_obj) {
			return it;
		}
		++it;
	}
	return nullptr;
}

template<typename Object>
inline void Vector<Object>::insert(iterator t_pos, const Object &t_obj)
{
	iterator it = end(); //末尾的后一个位置
	while (it != t_pos) {
		*(it) = *(it - 1);
		it--;
	}
	*it = t_obj;
}

template<typename Object>
inline void Vector<Object>::erase(iterator t_pos)
{
	iterator stop = end();
	iterator it = t_pos + 1;
	while (it != stop) {
		*(it - 1) = *it;
		++it;
	}
	theSize--;
}

template<typename Object>
inline void Vector<Object>::print()
{
	int n = size();
	for (size_t i = 0; i < n; i++) {
		std::cout << objects[i] << " ";
	}
	std::cout << std::endl;
}

//-------------------------Test-----------------------//
void test_vector()
{
	Vector<int> vec;

	for (size_t i = 0; i < 12; i++) {
		vec.push_back(i);
	}

	vec.insert(vec.find(5), 2333);

	vec.print();

	vec.erase(vec.find(6));

	vec.print();
}