#pragma once

#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>

using std::unique_ptr;
using std::vector;

namespace ds
{

class MyHeap
{
	using ArrPtr = unique_ptr<vector<int>>;

  public:
	MyHeap() {}
	MyHeap(const vector<int> &, int);

	int top() { return m_array->at(0); }
	void pop() { extract_max(); }
	void push(int);

  private:
	int getParent(int);
	int getChild(int, int);
	void max_heapify(int);
	int extract_max();
	void increase_key(int, int);
	int m_degree = 2; //可以是多叉树
	int m_heap_size = 0;
	ArrPtr m_array = nullptr;
};

int MyHeap::getParent(int t_son)
{
	return (t_son - 1) / m_degree;
}

/**
 * @brief 找到序号father的第id(0/1/2..)个孩子
 *
 * @param t_father 父节点在数组中的序号
 * @param t_id_child 表明是父节点的第几个孩子
 * @return int
 */
int MyHeap::getChild(int t_father, int t_id_child)
{
	return m_degree * t_father + t_id_child + 1;
}

MyHeap::MyHeap(const vector<int> &t_data, int t_degree = 2) : m_degree(t_degree), m_heap_size(t_data.size())
{
	int n = t_data.size();

	m_array = ArrPtr(new vector<int>(n * 2)); //空间适当大些

	for (int i = 0; i < n; i++) {
		m_array->at(i) = t_data[i];
	}
	//从下往上调整，第一个是最后一个非叶子节点
	for (int i = n / m_degree - 1; i >= 0; i--) {
		max_heapify(i);
	}
}

/**
 * @brief 从自己，和孩子中找一个最大的当父亲（根），递归调整
 *        或者理解为，自上而下的最小值下沉的过程
 * @param t_id
 */
inline void MyHeap::max_heapify(int t_id)
{
	int largest_id = t_id;

	int first_child_id = getChild(t_id, 0);

	for (int k = 0; k < m_degree; k++) {
		int child = first_child_id + k;
		if (child < m_heap_size && m_array->at(child) > m_array->at(largest_id)) {
			largest_id = child;
		}
	}

	if (largest_id != t_id) {
		std::swap(m_array->at(t_id), m_array->at(largest_id));
		max_heapify(largest_id);
	}
}

inline int MyHeap::extract_max()
{
	int l_max = m_array->at(0);
	m_array->at(0) = m_array->at(m_heap_size - 1);
	m_heap_size--;
	max_heapify(0);
	return l_max;
}

inline void MyHeap::push(int t_key)
{
	m_heap_size++;
	m_array->at(m_heap_size - 1) = INT_MIN;
	increase_key(m_heap_size - 1, t_key);
}
/**
 * @brief 自底向上，新值(变大后的关键字）上浮的过程
 *
 * @param t_id 在数组中的位置
 * @param t_key 增大后的新值
 */
inline void MyHeap::increase_key(int t_id, int t_key)
{
	if (t_key < m_array->at(t_id)) {
		std::cerr << "new key is samller than current key." << std::endl;
		exit(-1);
	}

	int adjust_id = t_id; //向上找到新key的位置adjust_id
	int parent_id = getParent(adjust_id);
	while (adjust_id > 0 && m_array->at(parent_id) < t_key) {
		m_array->at(adjust_id) = m_array->at(parent_id);
		adjust_id = parent_id;
		parent_id = getParent(adjust_id);
	}

	m_array->at(adjust_id) = t_key;
}

}; // namespace ds

void test()
{
	vector<int> data{23, 12, 0, 34, 1, 4, 2};
	ds::MyHeap heap(data);
	std::cout << heap.top() << std::endl;
	heap.pop();
	heap.push(4478);
	std::cout << heap.top() << std::endl;
}