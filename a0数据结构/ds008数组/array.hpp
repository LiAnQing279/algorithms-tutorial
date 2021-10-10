#pragma once

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>

namespace ds
{

class Array
{
	friend void copyOfRange(Array &t_a, Array &t_b, int t_begin, int t_end); //访问受保护元素

  public:
	Array() {}
	Array(int t_len);
	Array(int t_len, int t_init);
	void fill(int t_val);
	virtual ~Array();

	int &at(int t_id)
	{
		assert(t_id >= 0 && t_id < m_size);
		return m_array[t_id];
	}
	const int size() const { return m_size; }

	void push_back(int t_val);
	void pop_back() { m_size--; }

	virtual void reverse();

	Array &operator=(const Array &t_arr);
	const int operator[](int t_id) const
	{
		assert(t_id >= 0 && t_id < m_size); //确认合法条件
		return m_array[t_id];
	}

  private:
	void swap(int t_i, int t_j);

  protected:
	int *m_array = nullptr;
	int m_length = 0; //空间大小
	int m_size = 0;	  //元素个数
};

Array::Array(int t_len) : m_length(t_len * 2), m_size(t_len)
{
	m_array = new int[m_length];
	fill(0);
}

inline Array::Array(int t_len, int t_init) : m_length(t_len * 2), m_size(t_len)
{
	m_array = new int[m_length];
	fill(t_init);
}

inline void Array::fill(int t_val)
{
	std::fill(m_array, m_array + m_size, t_val);
}

Array::~Array()
{
	if (m_array != nullptr)
		delete[] m_array;
}

inline Array &Array::operator=(const Array &t_arr)
{
	if (m_array != nullptr) {
		delete[] m_array;
		m_array = nullptr;
	}

	m_size = t_arr.size();
	m_length = m_size * 2;
	m_array = new int[m_length];

	for (int i = 0; i < m_size; i++) {
		m_array[i] = t_arr[i];
	}
	return *this;
}

inline void Array::push_back(int t_val)
{

	if (m_length <= m_size + 1) {
		m_length = m_size * 2;
		int *t_arr = new int[m_length];
		for (int i = 0; i < m_size; i++) {
			t_arr[i] = m_array[i];
		}
		delete[] m_array;
		m_array = t_arr;
	}

	m_size++;
	m_array[m_size - 1] = t_val;
}

inline void Array::reverse()
{
	// std::reverse(m_array, m_array + m_size);
	for (int i = 0; i < m_size / 2; i++) {
		swap(i, m_size - i - 1);
	}
}

inline void Array::swap(int t_i, int t_j)
{
	assert(t_i < m_size && t_j < m_size);
	if (t_i == t_j)
		return;

	int tmp = m_array[t_i];
	m_array[t_i] = m_array[t_j];
	m_array[t_j] = tmp;
}

void copyOfRange(Array &t_dest, Array &t_src, int t_begin, int t_end)
{
	Array ans(t_end - t_begin); //[begin,end)
	std::copy(t_src.m_array + t_begin, t_src.m_array + t_end, ans.m_array);
	t_dest = ans;
}

} // namespace ds

void out(ds::Array &a)
{
	for (int i = 0; i < a.size(); i++) {
		printf_s("%2d ", a[i]);
	}
	std::cout << std::endl;
}

void testArray()
{
	ds::Array myArr(12);
	for (size_t i = 0; i < 12; i++) {
		myArr.at(i) = i;
	}

	out(myArr);
	// myArr.reverse();
	// out(myArr);

	myArr.pop_back();
	out(myArr);
	// myArr.fill(11);
	// out(myArr);

	ds::Array arr1;
	ds::copyOfRange(arr1, myArr, 1, 5);
	out(arr1);
}