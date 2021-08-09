#pragma once

#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>

using std::unique_ptr;
using std::vector;

enum { MAX, MIN };

/**
 * @brief 改进
 *
 */
namespace ds
{

class MyHeap
{
	using ArrPtr = unique_ptr<vector<int>>;

  public:
	MyHeap() {}
	MyHeap(const vector<int> &, int, int);

	int top() { return m_array->at(0); }
	void pop();
	void push(int);
	int size() { return m_heap_size; }
	int back() { return m_array->at(m_heap_size - 1); }
	void printHeap() const;
	void heap_sort();

  private:
	int getParent(int);
	int getChild(int, int);
	void sink(int);
	void swim(int, int);

	int m_mode = MAX; //大顶堆 0，或者小顶堆 1
	int m_degree = 2;
	int m_heap_size = 0;
	ArrPtr m_array = nullptr;
};

int MyHeap::getParent(int t_son)
{
	return (t_son - 1) / m_degree;
}
//找到序号father的第id_child（从0开始）个孩子
int MyHeap::getChild(int t_father, int t_id_child)
{
	return m_degree * t_father + t_id_child + 1;
}

MyHeap::MyHeap(const vector<int> &t_data, int t_degree = 2, int t_mode = 0) : m_degree(t_degree), m_mode(t_mode)
{
	int n = t_data.size();
	if (m_heap_size < n) {
		m_array.reset();
		m_array = ArrPtr(new vector<int>(n * 2));
	}

	for (int i = 0; i < n; i++) {
		m_array->at(i) = t_data[i];
	}
	m_heap_size = n;

	for (int i = n / m_degree - 1; i >= 0; i--) {
		sink(i);
	}
}

inline void MyHeap::pop()
{
	m_array->at(0) = m_array->at(m_heap_size - 1);
	m_heap_size--;
	sink(0);
}

inline void MyHeap::push(int t_key)
{
	//这里的初始化，保证满足上浮条件
	m_array->at(m_heap_size) = (m_mode == MIN) ? INT_MAX : INT_MIN;
	swim(m_heap_size, t_key);
	m_heap_size++; //小心不是放在开头
}

inline void MyHeap::printHeap() const
{
	for (int i = 0; i < m_heap_size; i++) {
		std::cout << m_array->at(i) << " ";
	}
	std::cout << std::endl;
}

inline void MyHeap::sink(int t_id)
{
	int extremum_id = t_id; //差找极值的id

	int first_child_id = getChild(t_id, 0);

	for (int k = 0; k < m_degree; k++) {
		int child = first_child_id + k;
		if (child < m_heap_size) {
			if (m_mode == MAX && m_array->at(child) > m_array->at(extremum_id)) {
				extremum_id = child;
			} else if (m_mode == MIN && m_array->at(child) < m_array->at(extremum_id)) {
				extremum_id = child;
			}
		}
	}

	if (extremum_id != t_id) {
		std::swap(m_array->at(t_id), m_array->at(extremum_id));
		sink(extremum_id);
	}
}

inline void MyHeap::swim(int t_id, int t_key)
{
	if (m_mode == MAX && t_key < m_array->at(t_id)) {
		std::cerr << "new key is samller than current key." << std::endl;
		exit(-1);
	}
	if (m_mode == MIN && t_key > m_array->at(t_id)) {
		//小顶堆，减小关键字后，发生上浮
		std::cerr << "new key is bigger than current key." << std::endl;
		exit(-1);
	}

	int adjust_id = t_id; //向上找到新key的位置adjust_id
	int parent_id = getParent(adjust_id);
	while (adjust_id > 0) {
		if (m_mode == MAX && m_array->at(parent_id) < t_key) {
			m_array->at(adjust_id) = m_array->at(parent_id);
		} else if (m_mode == MIN && m_array->at(parent_id) > t_key) {
			m_array->at(adjust_id) = m_array->at(parent_id);
		} else {
			break; //区分两种模式的条件要更加清楚
		}

		adjust_id = parent_id;
		parent_id = getParent(adjust_id);
	}

	m_array->at(adjust_id) = t_key;
}

inline void MyHeap::heap_sort()
{
	int old_size = m_heap_size;
	vector<int> tmp(m_heap_size);
	int id = 0;

	for (int i = m_heap_size; i >= 1; i--) {
		tmp.at(id++) = m_array->at(0);
		m_array->at(0) = m_array->at(m_heap_size - 1);
		sink(0);

		m_heap_size--;
	}
	m_heap_size = old_size;

	for (int i = 0; i < id; i++) {
		m_array->at(i) = tmp[i];
	}
}

}; // namespace ds

void test_heap()
{
	vector<int> data{23, 11, 120, 33, 121, 44, 232};
	ds::MyHeap heap(data, 3, 1);
	heap.printHeap();
	// std::cout << heap.top() << std::endl;//11
	heap.pop();
	heap.printHeap();
	// std::cout << heap.top() << std::endl;//33
	heap.push(22);
	// std::cout << heap.top() << std::endl;//22
	heap.printHeap();
}