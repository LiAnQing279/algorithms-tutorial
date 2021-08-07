#pragma once

#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>

namespace ds
{

struct DjsetNode {
	int rank;	//叶节点等级最低为0
	int parent; //当前节点的父节点的id编号

	DjsetNode(int t_parent, int t_rank = 0) : parent(t_parent), rank(t_rank) {}
};

// typedef DjsetNode* Ptr;
typedef std::unique_ptr<DjsetNode> UPtr;

class MyDjset
{
  public:
	MyDjset(int);

	void unionSet(int, int);
	int findSet(int);
	void printSet();

  private:
	std::vector<UPtr> m_root;
};

MyDjset::MyDjset(int t_N)
{
	for (int i = 0; i <= t_N; i++) {
		m_root.push_back(UPtr(new DjsetNode(i)));
	}
}

void MyDjset::unionSet(int t_id0, int t_id1)
{
	int root0 = findSet(t_id0);
	int root1 = findSet(t_id1);
	if (root0 == root1)
		return;

	// rank越大，层次越高，树越大
	int rank0 = m_root.at(root0)->rank;
	int rank1 = m_root.at(root1)->rank;

	//小树并入大树
	if (rank0 > rank1) {
		m_root.at(root1)->parent = root0;
	} else {
		m_root.at(root0)->parent = root1;
		if (rank1 == rank0) {
			m_root.at(root1)->rank++;
		}
	}
}
/**
 * @brief 找到id所在集合的根节点id,并将查找路径上的所有节点之间指向根节点
 *
 * @param t_id 待查找的数据id
 * @return int 所在集合的根节点id
 */
int MyDjset::findSet(int t_id)
{
	int pa = m_root.at(t_id)->parent;
	if (pa != t_id) {
		m_root.at(t_id)->parent = findSet(pa);
	}
	return m_root.at(t_id)->parent;
}

inline void MyDjset::printSet()
{
	int n = m_root.size();
	std::cout << "id:\t";
	for (int i = 0; i < n; i++) {
		std::cout << i << " ";
	}
	std::cout << "\nparent:\t";
	for (int i = 0; i < n; i++) {
		std::cout << m_root[i]->parent << " ";
	}
	std::cout << std::endl;
}

}; // namespace ds