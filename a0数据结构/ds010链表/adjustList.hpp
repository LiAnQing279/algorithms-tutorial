#pragma once
/**
 * @file adjustList.hpp
 * @author LiAnQing279
 * @brief 带头结点的单链表，将上次访问的节点放到开头
 * @version 0.1
 * @date 2021-08-21
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <iostream>
namespace ds
{

class AdjustList
{

	struct Node {
		int val;
		int used; // 0 表示已经删除
		struct Node *next;
		Node(int t_val, int t_used = 1, struct Node *t_next = nullptr) : val(t_val), used(t_used), next(t_next) {}
	};
	typedef Node *Nptr;

  public:
	AdjustList() { m_header = new Node(-1); }

	void insert(int t_val);
	void remove(int t_val); //懒惰删除方法
	Nptr find(int t_val);

	bool empty() { return m_header->next == nullptr; }
	void clear();
	void printList();

  private:
	Nptr m_header = nullptr;
	int m_capacity = 0;	 //实际含有的物理
	int m_deleteNum = 0; //已经被标记删除的节点数
};

inline void AdjustList::insert(int t_val)
{
	Nptr pre = m_header;
	//在开头附近查找已删除的标记节点
	while (pre->next && pre->next->used) {
		pre = pre->next;
	}

	if (pre->next) {
		Nptr blank = pre->next;

		pre->next = blank->next;

		blank->val = t_val;
		blank->next = m_header->next;
		blank->used = 1;
		m_header->next = blank;

		m_deleteNum--;
	} else { //头插法
		Nptr newNode = new Node(t_val, 1, m_header->next);
		m_header->next = newNode;
	}

	m_capacity++;
}
inline void AdjustList::remove(int t_val)
{
	Nptr goal = find(t_val);
	if (!goal)
		return;

	goal->used = 0;
	m_deleteNum++;
	//懒惰删除，只有当要删除的节点超过实际容量的一半，才真的释放空间
	if (m_deleteNum > m_capacity / 2) {
		Nptr pre = m_header;
		Nptr ptr = m_header->next;
		while (ptr) {
			if (ptr->used == 0) {
				pre->next = ptr->next;
				delete ptr;
				ptr = pre->next;
			} else {
				pre = ptr;
				ptr = ptr->next;
			}
		}

		m_capacity -= m_deleteNum;
		m_deleteNum = 0;
	}
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
		return nullptr; // not exit
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
	m_capacity = 0;
	m_deleteNum = 0;
}

inline void AdjustList::printList()
{
	Nptr ptr = m_header->next;
	while (ptr) {
		std::cout << ptr->val << "(" << ptr->used << ") ";
		ptr = ptr->next;
	}
	std::cout << std::endl;
}

} // namespace ds

#define nextLine std::cout << std::endl
void test_adjust_list()
{
	ds::AdjustList alist;

	// insert
	for (int i = 0; i < 12; i++) {
		alist.insert(i);
	}
	alist.printList();

	//删除小于一半，只是标记一下
	alist.remove(4);
	alist.remove(6);
	alist.remove(7);
	alist.remove(9);
	alist.remove(10);
	alist.printList();
	nextLine;
	//删除大于一半，释放物理空间
	alist.remove(1);
	alist.remove(0);
	alist.printList();
	nextLine;

	//查找过的元素靠近头部
	alist.find(5);
	if (!alist.find(7))
		std::cout << "not exit." << std::endl;
	alist.printList();
	nextLine;

	//测试clear，以及新插入节点利用标记的删除节点
	alist.clear();
	for (int i = 1; i <= 8; i++) {
		alist.insert(i * 111);
	}
	alist.printList();
	for (int i = 1; i <= 3; i++) {
		alist.remove(i * 111);
	}
	alist.printList();
	for (int i = 1; i <= 3; i++) {
		alist.insert(i * 222);
	}
	alist.printList();
}
