#pragma once

#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>

namespace ds
{
const int NOITEM = -99999;
class MyQueue
{
	using ArrayPtr = std::unique_ptr<std::vector<int>>;

  public:
	MyQueue() {}
	MyQueue(int t_item_num);

	int enqueue(int);
	int dequeue();
	bool isFull() const
	{
		return m_rear - m_front == m_array->size() || m_front == m_rear + 1; //差一个位置
	}
	bool isEmpty() const { return m_front == m_rear; }
	void printQueue() const;

  private:
	int m_front = -1;			//第一个值的前一个位置，会浪费一个空间
	int m_rear = -1;			//指向实际的最后一个值
	ArrayPtr m_array = nullptr; // (m_front,m_rear]
};

MyQueue::MyQueue(int t_item_num)
{
	m_array = ArrayPtr(new std::vector<int>(t_item_num));
}

inline int MyQueue::enqueue(int t_value)
{
	if (isFull()) {
		printf_s("\nThe queue is full!\n");
		return -1;
	}
	int length = m_array->size();
	m_rear = (m_rear + 1) % length;
	m_array->at(m_rear) = t_value;
	return 0;
}

inline int MyQueue::dequeue()
{
	if (isEmpty()) {
		printf_s("\nThe queue is empty!\n");
		return NOITEM;
	}
	int length = m_array->size();
	m_front = (m_front + 1) % length;
	return m_array->at(m_front);
}

inline void MyQueue::printQueue() const
{
	int N = m_array->size();
	for (int i = (m_front + 1) % N; i != m_rear; i = (i + 1) % N) {
		printf_s("%d ", m_array->at(i));
	}
	printf_s("%d\n", m_array->at(m_rear));
}

} // namespace ds

void test_my_queue()
{
	ds::MyQueue myQ(5);
	std::vector<int> data{12, 6, 235, 432, 17, 956, 2435};

	for (auto x : data) {
		if (!myQ.enqueue(x))
			continue;
		else
			break;
	}
	myQ.printQueue();

	int t = 14;
	while (t--) {
		int info = myQ.dequeue();
		if (info == ds::NOITEM) {
			break;
		} else {
			printf("pop->%d ", info);
		}
	}

	myQ.enqueue(333);
	myQ.printQueue();
}