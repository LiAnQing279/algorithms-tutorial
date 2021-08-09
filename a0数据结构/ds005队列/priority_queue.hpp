#pragma once

#include "heaplib2.hpp"

namespace ds
{

class PriorityQueue
{
	using HeapPtr = unique_ptr<MyHeap>;

  public:
	PriorityQueue() {}
	PriorityQueue(const vector<int> &, int, int);

	int front() const { return m_heap->top(); }
	void pop() const { return m_heap->pop(); }
	void push(int t_key) { return m_heap->push(t_key); }
	int back() { return m_heap->back(); }
	int size() const { return m_heap->size(); }
	bool empty() const { return size() == 0; }
	void sort() const { m_heap->heap_sort(); }
	void print() { m_heap->printHeap(); }

  private:
	HeapPtr m_heap = nullptr;
};

PriorityQueue::PriorityQueue(const vector<int> &m_data, int t_mode, int t_degree = 2)
{
	m_heap = HeapPtr(new MyHeap(m_data, t_degree, t_mode));
}
}; // namespace ds

#define out(x) std::cout << x << std::endl;
void test_pq()
{
	vector<int> data{77, 1, 89, 96, 3, 90};
	ds::PriorityQueue p_queue(data, MAX, 3); //三叉的大顶堆
	// out(p_queue.front());
	p_queue.print();

	p_queue.pop();
	// out(p_queue.back());
	p_queue.print();

	p_queue.push(11);
	p_queue.print();

	p_queue.sort();
	p_queue.print();
}
