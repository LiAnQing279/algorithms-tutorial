/**
 * @file doubleStack.hpp
 * @author LiAnQing279
 * @brief 用一个数组实现两个栈，头对头
 * @version 0.1
 * @date 2021-08-21
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once
#include <iostream>

namespace ds
{

class DoubleStack
{
	using arrPtr = int *;

  public:
	DoubleStack() {}
	DoubleStack(int);

	void push(int t_val, int isleft);
	void pop(int isleft);
	bool empty(int isleft);
	void clear(int isleft);

	void print();

  private:
	arrPtr m_arr = nullptr;

	int m_capacity = 0;
	int m_leftTop = 0;	//指向实际真正栈顶的下一个位置
	int m_rightTop = 0; //指向实际真正栈顶的下一个位置
};

DoubleStack::DoubleStack(int t_capacity) : m_capacity(t_capacity), m_rightTop(t_capacity - 1)
{
	m_arr = new int[m_capacity];
}

inline void DoubleStack::push(int t_val, int isleft)
{
	if (m_leftTop > m_rightTop) {
		std::cout << "the stack is full! " << std::endl;
		return;
	}

	if (isleft) {
		m_arr[m_leftTop++] = t_val;
	} else {
		m_arr[m_rightTop--] = t_val;
	}
}

inline void DoubleStack::pop(int isleft)
{
	if (isleft) {
		if (m_leftTop == 0)
			return;
		--m_leftTop;
	} else {
		if (m_rightTop == m_capacity - 1)
			return;
		++m_rightTop;
	}
}

inline bool DoubleStack::empty(int isleft)
{
	if (isleft) {
		return m_leftTop == 0;
	} else {
		return m_rightTop == m_capacity - 1;
	}
}

inline void DoubleStack::clear(int isleft)
{
	if (isleft) {
		m_leftTop = 0;
	} else {
		m_rightTop = m_capacity - 1;
	}
}

inline void DoubleStack::print()
{

	std::cout << "Left (->top): ";
	for (int i = 0; i < m_leftTop; i++) {
		std::cout << m_arr[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Right(->top): ";
	for (int i = m_capacity - 1; i > m_rightTop; i--) {
		std::cout << m_arr[i] << " ";
	}
	std::cout << std::endl;
}

} // namespace ds

void test_doubleStack()
{

	ds::DoubleStack dstk(12);

	// push
	for (size_t i = 0; i < 6; i++) {
		dstk.push(i + 11, 1);
	}
	for (size_t i = 1; i < 7; i++) {
		dstk.push(11 * i, 0);
	}

	dstk.print();

	// pop
	dstk.pop(1);
	dstk.pop(1);

	dstk.pop(0);
	dstk.pop(0);
	dstk.pop(0);

	dstk.print();
	// clear
	dstk.clear(1);
	dstk.print();
}