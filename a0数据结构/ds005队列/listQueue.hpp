#pragma once

#include <iostream>

namespace ds
{
/**
 * @brief 用循环链表构成队列
 *
 */
class ListQueue
{
	struct Node {
		int val;
		struct Node *next;

		Node(int t_val, struct Node *t_next = nullptr) : val(t_val), next(t_next) {}
	};

	typedef Node *Nptr;

  public:
	ListQueue() {}

	void enqueue(int val);
	void dequeue();

	int front()
	{
		if (m_tail)
			return m_tail->next->val;
		return -1;
	}
	int back()
	{
		if (m_tail)
			return m_tail->val;
		return -1;
	}

	void clear();
	bool empty() { return m_tail == nullptr; }

  private:
	Nptr m_tail = nullptr; //单链表构成环，指向末尾元素
};

void ListQueue::enqueue(int val)
{
	Nptr newNode = new Node(val);
	if (m_tail == nullptr) {
		m_tail = newNode;
		m_tail->next = newNode;
	} else {
		Nptr head = m_tail->next;
		m_tail->next = newNode;
		newNode->next = head;
	}
	m_tail = newNode; //更新到末尾
	newNode = nullptr;
}
inline void ListQueue::clear()
{
	while (m_tail) {
		dequeue();
	}
}
inline void ListQueue::dequeue()
{
	if (m_tail == m_tail->next) {
		delete m_tail;
		m_tail = nullptr;
		return;
	}

	Nptr pre = m_tail;
	while (pre->next != m_tail)
		pre = pre->next;

	pre->next = m_tail->next;
	delete m_tail;
	m_tail = pre;
}
} // namespace ds

void test_ListQueue()
{
	ds::ListQueue myStk;

	myStk.enqueue(321);
	myStk.enqueue(123);
	std::cout << myStk.front() << std::endl;
	myStk.clear();
	myStk.enqueue(231);

	for (size_t i = 0; i < 5; i++) {
		myStk.enqueue(i);
	}

	while (!myStk.empty()) {
		std::cout << myStk.back() << " ";
		myStk.dequeue();
	}

	std::cout << myStk.front() << std::endl;
}