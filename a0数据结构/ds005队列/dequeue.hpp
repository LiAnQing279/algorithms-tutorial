#pragma once

#include <iostream>
#include <list>
#include <memory>

using std::list;
using std::unique_ptr;

namespace ds
{
/**
 * @brief 利用list实现双端队列的主要的借口
 *
 */
class dequeue
{
	using ListPtr = unique_ptr<list<int>>;

  public:
	dequeue() {}

	void push(int t_val);	//头部插入
	int pop();				//头部删除后返回
	void inject(int t_val); //在尾部插入
	int eject();			//尾部删除后返回

	void print();
	void clear() { m_list->clear(); }

  private:
	ListPtr m_list = nullptr;
};

void dequeue::push(int t_val)
{
	if (m_list == nullptr) {
		m_list = ListPtr(new list<int>(1, t_val));
		return;
	}

	m_list->push_front(t_val);
}
inline int dequeue::pop()
{
	int ans = m_list->front();
	m_list->pop_front();
	return ans;
}
inline void dequeue::inject(int t_val)
{
	if (m_list == nullptr) {
		m_list = ListPtr(new list<int>(1, t_val));
		return;
	}
	m_list->push_back(t_val);
}
inline int dequeue::eject()
{
	int ans = m_list->back();
	m_list->pop_back();
	return ans;
}
inline void dequeue::print()
{
	auto it = m_list->cbegin();
	auto end = m_list->cend();
	while (it != end) {
		std::cout << *it++ << " ";
	}
	std::cout << std::endl;
}
} // namespace ds

void test_dequeue()
{
	ds::dequeue que;
	que.push(100);
	que.inject(200);
	que.push(900);
	que.inject(7000);

	que.print();
	que.eject();
	que.print();
	que.pop();
	que.eject();
	que.print();
}
