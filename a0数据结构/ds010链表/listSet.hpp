#pragma once

#include <iostream>
namespace ds
{

class ListSet
{
	struct Node {
		int val;
		struct Node *next;
		Node(int t_val, struct Node *t_next = nullptr) : val(t_val), next(t_next) {}
	};
	typedef Node *Nptr;

  public:
	ListSet() { m_header = new Node(-1); }

	int size() { return m_size; }
	bool contains(int t_val) { return find(t_val) != nullptr; }
	bool empty() { return m_size == 0; }
	void clear();

	void erase(int t_val);
	void insert(int t_val);	 //头插法
	void keepOdd(int t_val); //偶数次数据不保存
	void print();

  private:
	Nptr m_header = nullptr;
	int m_size = 0;
	Nptr find(int t_val); //查找后移动到开头
	void insert_helper(int t_val);
};

void ListSet::insert(int t_val)
{
	if (contains(t_val))
		return;
	insert_helper(t_val);
}
inline void ListSet::keepOdd(int val)
{
	Nptr pos = find(val);
	if (pos) {
		//删除第一个节点
		m_header->next = pos->next;
		m_size--;
		//释放空间
		delete pos;
		pos = nullptr;
	} else {
		insert_helper(val);
	}
}
void ListSet::erase(int t_val)
{
	Nptr pos = find(t_val);
	//删除第一个节点
	m_header->next = pos->next;
	m_size--;
	//释放空间
	delete pos;
	pos = nullptr;
}

inline ListSet::Nptr ListSet::find(int t_val)
{
	Nptr pre = m_header;
	Nptr goal = m_header->next;

	while (goal && goal->val != t_val) {
		pre = pre->next;
		goal = pre->next;
	}

	if (!goal) {
		// std::cout << "not exit." << std::endl;
		return nullptr;
	}

	pre->next = goal->next;
	//调整到开头
	goal->next = m_header->next;
	m_header->next = goal;
	return goal;
}

inline void ListSet::insert_helper(int t_val)
{
	Nptr newNode = new Node(t_val, m_header->next);
	m_header->next = newNode;
	m_size++;
}

inline void ListSet::clear()
{
	Nptr ptr = m_header->next;
	while (ptr) {
		m_header->next = ptr->next;
		delete ptr;
		ptr = m_header->next;
	}
	m_size = 0;
}

inline void ListSet::print()
{
	Nptr ptr = m_header->next;
	while (ptr) {
		std::cout << ptr->val << " ";
		ptr = ptr->next;
	}
	std::cout << std::endl;
}

} // namespace ds

void test_list_set()
{
	ds::ListSet set;
	int arr[] = {111, 121, 131, 121, 132, 132};
	int arr_n = 6;

	for (size_t i = 0; i < arr_n; i++) {
		set.insert(arr[i]);
	}
	set.print();
	std::cout << set.size() << std::endl;

	set.clear();
	for (size_t i = 0; i < arr_n; i++) {
		set.keepOdd(arr[i]);
	}
	set.print();

	std::cout << set.size() << std::endl;
}
