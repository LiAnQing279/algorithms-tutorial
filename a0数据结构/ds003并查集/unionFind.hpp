#pragma once
#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::vector;
namespace ds
{
class MyUF
{
	using ArrPtr = unique_ptr<vector<int>>;

  public:
	MyUF() {}
	MyUF(int t_N);

	int count() const { return m_count; }
	bool isConnected(int p, int q) { return findSet(p) == findSet(q); }
	int findSet(int);
	void unionSet(int, int);

	void print() const;

  private:
	ArrPtr m_father = nullptr; //父亲指针
	ArrPtr m_size = nullptr;   //集合大小
	int m_count = 0;		   //联通分量个数
};

MyUF::MyUF(int t_N) : m_count(t_N)
{
	m_father = ArrPtr(new vector<int>(t_N));
	m_size = ArrPtr(new vector<int>(t_N));
	for (size_t i = 0; i < t_N; i++) {
		m_father->at(i) = i;
		m_size->at(i) = 1;
	}
}

inline int MyUF::findSet(int t_id)
{
	if (m_father->at(t_id) == t_id)
		return t_id; //出口
	return m_father->at(t_id) = findSet(m_father->at(t_id));
	//核心的核心：路上各点都接到根上
}

inline void MyUF::unionSet(int t_q, int t_p)
{
	int set_i = findSet(t_q);
	int set_j = findSet(t_p);
	if (set_i == set_j)
		return;

	if (m_size->at(set_i) < m_size->at(set_j)) {
		m_father->at(set_i) = set_j;
		m_size->at(set_j) += m_size->at(set_i);
	} else {
		m_father->at(set_j) = set_i;
		m_size->at(set_i) += m_size->at(set_j);
	}

	m_count--;
}

inline void MyUF::print() const
{
	int n = m_father->size();
	cout << "i: \t";
	for (int i = 0; i < n; i++) {
		cout << i << " ";
	}
	cout << endl;
	cout << "fa: \t";
	for (int i = 0; i < n; i++) {
		cout << m_father->at(i) << " ";
	}
	cout << endl;
}

} // namespace ds

void test_union_find()
{
	ds::MyUF myUF(9);
	myUF.unionSet(2, 4);
	myUF.unionSet(1, 3);
	myUF.unionSet(0, 2);

	myUF.print();
	myUF.unionSet(5, 3);
	myUF.unionSet(6, 5);
	myUF.unionSet(6, 7);
	myUF.print();

	myUF.findSet(0);
	myUF.print();
	cout << myUF.count() << endl;
}