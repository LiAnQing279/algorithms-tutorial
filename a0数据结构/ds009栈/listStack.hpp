#pragma once

#include <iostream>

namespace ds
{

/**
 * @brief 用循环链表，实现栈的基本操作
 *
 */
class ListStack
{
	struct Node {
		int val;
		struct Node *next;

		Node(int t_val, struct Node *t_next = nullptr) : val(t_val), next(t_next) {}
	};

	typedef Node *Nptr;

  public:
	ListStack() {}

	void push(int val);
	int top()
	{
		if (m_top)
			return m_top->val;
		return -1;
	}
	void clear();
	bool empty() { return m_top == nullptr; }
	void pop();

  private:
	Nptr m_top = nullptr; //单链表构成环，指向末尾元素
};

void ListStack::push(int val)
{
	Nptr newNode = new Node(val);
	if (m_top == nullptr) {
		m_top = newNode;
		m_top->next = newNode;
	} else {
		Nptr head = m_top->next;
		m_top->next = newNode;
		newNode->next = head;
	}
	m_top = newNode;
	newNode = nullptr;
}
inline void ListStack::clear()
{
	while (m_top) {
		pop();
	}
}
inline void ListStack::pop()
{
	//小心只有一个节点的情况
	if (m_top == m_top->next) {
		delete m_top;
		m_top = nullptr;
		return;
	}

	Nptr pre = m_top;
	while (pre->next != m_top)
		pre = pre->next;

	pre->next = m_top->next;
	delete m_top;
	m_top = pre;
}
} // namespace ds

void test_listStack()
{
	ds::ListStack myStk;

	myStk.push(321);
	myStk.push(123);
	myStk.push(231);

	for (size_t i = 0; i < 5; i++) {
		myStk.push(i);
	}

	//后出先出
	while (!myStk.empty()) {
		std::cout << myStk.top() << " ";
		myStk.pop();
	}
	myStk.clear();

	std::cout << myStk.top() << std::endl;
}