#pragma once

#include <iostream>
namespace ds
{
/**
 * @brief 头插法建立单链表，每次查找元素后移动到表头
 *
 */
class AdjustList
{

	struct Node {
		int val;
		struct Node *next;
		Node(int t_val, struct Node *t_next = nullptr) : val(t_val), next(t_next) {}
	};
	typedef Node *Nptr;

  public:
	AdjustList() { m_header = new Node(-1); }

	void insertFront(int t_val);
	Nptr find(int t_val);
	bool empty() { return m_header->next == nullptr; }
	void clear();
	void printList();

  private:
	Nptr m_header = nullptr;
};

void AdjustList::insertFront(int t_val)
{ //头插法
	Nptr newNode = new Node(t_val, m_header->next);
	m_header->next = newNode;
}

inline AdjustList::Nptr AdjustList::find(int t_val)
{
	Nptr pre = m_header;
	Nptr goal = m_header->next;

	while (goal && goal->val != t_val) {
		pre = pre->next;
		goal = pre->next;
	}

	if (!goal) {
		std::cout << "not exit." << std::endl;
		return nullptr;
	}

	pre->next = goal->next;
	//调整到开头
	goal->next = m_header->next;
	m_header->next = goal;
	return goal;
}

inline void AdjustList::clear()
{
	Nptr ptr = m_header->next;
	while (ptr) {
		m_header->next = ptr->next;
		delete ptr;
		ptr = m_header->next;
	}
}

inline void AdjustList::printList()
{
	Nptr ptr = m_header->next;
	while (ptr) {
		std::cout << ptr->val << " ";
		ptr = ptr->next;
	}
	std::cout << std::endl;
}

} // namespace ds

void test_adjust_list()
{
	ds::AdjustList alist;
	for (int i = 0; i < 12; i++) {
		alist.insertFront(i);
	}

	alist.find(5);
	alist.find(0);
	alist.find(7);

	alist.printList();
	alist.clear();
	alist.insertFront(1245);
	alist.printList();
}
