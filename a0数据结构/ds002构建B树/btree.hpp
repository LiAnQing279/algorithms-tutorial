#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>

namespace btree
{

unsigned int g_t = 3; // minimum_degree >=2

template<typename T>
struct BTreeNode {
	int n;	  // key number
	int leaf; // 1 is leaf node
	int height;
	T *key;
	struct BTreeNode **child;

	BTreeNode() {}
	BTreeNode(int t_ksize, int t_leaf, int t_height) : n(t_ksize), leaf(t_leaf), height(t_height)
	{
		key = new T[2 * g_t - 1];
		child = new BTreeNode<T> *[2 * g_t];
	}
	bool isFull() { return n == 2 * g_t - 1; }
	void printNode()
	{
		for (int i = 0; i < n; i++) {
			std::cout << key[i] << " ";
		}
		std::cout << std::endl;
	}
};

template<typename T>
class BTree
{
	using NPtr = BTreeNode<T> *;

  public:
	BTree();
	void setDegree(int t_min_degree);
	void insert(const T &t_key);
	void search(const T &t_key);
	void visit();

  private:
	NPtr m_root = nullptr;
	void insertNonFull(NPtr, const T &);
	void splitChlid(NPtr, const T &);
	void search_helper(NPtr, const T &);
	void visit_helper(NPtr);
	void update_height(NPtr);
};

template<typename T>
BTree<T>::BTree()
{
	m_root = new BTreeNode<T>(0, true, 0);
}
template<typename T>
void BTree<T>::setDegree(int t_min_degree)
{
	g_t = t_min_degree;
}

template<typename T>
void BTree<T>::insert(const T &t_key)
{
	auto t_root = m_root;
	if (t_root->isFull()) {
		auto t_node = new BTreeNode<T>(0, false, t_root->height);
		t_node->child[0] = t_root;
		m_root = t_node;

		splitChlid(t_node, 0);
		insertNonFull(t_node, t_key);
	} else {
		insertNonFull(t_root, t_key);
	}
}

template<typename T>
void BTree<T>::insertNonFull(NPtr t_now, const T &t_key)
{
	int last_key_idx = t_now->n - 1;
	if (t_now->leaf) {
		while (last_key_idx >= 0 && t_key < (t_now->key[last_key_idx])) {
			t_now->key[last_key_idx + 1] = t_now->key[last_key_idx];
			last_key_idx--;
		} //递增有序，需要后移找到位置
		t_now->key[last_key_idx + 1] = t_key;
		t_now->n += 1;
	} else {
		while (last_key_idx >= 0 && t_key < (t_now->key[last_key_idx])) {
			last_key_idx--;
		}
		last_key_idx++;

		auto tmp = t_now->child[last_key_idx];

		if (tmp->isFull()) {
			splitChlid(t_now, last_key_idx);
			if (t_key > (t_now->key[last_key_idx])) {
				last_key_idx++;
			}
		}
		insertNonFull(t_now->child[last_key_idx], t_key);
	}
}

template<typename T>
void BTree<T>::splitChlid(NPtr t_father, const T &t_child_i)
{
	int j;
	int size = g_t - 1; //左右儿子的关键字个数
	auto l_son = t_father->child[t_child_i];
	auto r_son = new BTreeNode<T>(size, l_son->leaf, t_father->height + 1);

	// r_son的key值：来自待分裂节点的后一半key(不含中心值)
	for (j = 0; j < size; j++) {
		r_son->key[j] = l_son->key[g_t + j];
	}
	l_son->n = size; //左孩子（待分裂）节点留下前一半

	// r_son的child:来自待分裂节点的后一半child(前提不是叶子，child各得g_t个)
	if (!(l_son->leaf)) {
		for (j = 0; j < g_t; j++)
			r_son->child[j] = l_son->child[g_t + j];
	}

	//为中间值腾位置
	int final_key_i = (t_father->n) - 1;
	for (j = final_key_i; j >= t_child_i; j--) {
		t_father->key[j + 1] = t_father->key[j];
	}
	t_father->key[t_child_i] = l_son->key[size];
	t_father->n = t_father->n + 1;

	// 把右孩子插入父节点：孩子总数比关键字多一
	int final_child_i = t_father->n;
	for (j = final_child_i; j > t_child_i; j--) {
		t_father->child[j + 1] = t_father->child[j];
	}
	t_father->child[t_child_i + 1] = r_son;

	l_son->height = t_father->height + 1;

	//向下传播高度变化
	update_height(r_son);
	update_height(l_son);
}

template<typename T>
void BTree<T>::search(const T &t_key)
{
	search_helper(m_root, t_key);
}
template<typename T>
void BTree<T>::search_helper(NPtr t_now, const T &t_key)
{
	int child_i = 0;
	int n = t_now->n; //当前节点的关键字个数

	while (child_i < n && t_key > (t_now->key[child_i])) {
		child_i++;
	} // t_key <= now_key[child_i]，child_i可以取到n

	if (child_i < n && t_key == (t_now->key[child_i])) {
		std::cout << "Final keys: ";
		t_now->printNode();
		std::cout << "Goal found at position " << child_i + 1 << ", height is " << t_now->height << "." << std::endl;
	} else if (t_now->leaf) {
		std::cout << "\nKey not found" << std::endl;
	} else {
		search_helper(t_now->child[child_i], t_key);
	}
}

template<typename T>
void BTree<T>::visit()
{
	visit_helper(m_root);
}
template<typename T>
void BTree<T>::visit_helper(NPtr t_now)
{
	if (t_now) {
		std::cout << t_now->height << "th floor: ";
		t_now->printNode();

		int child_num = t_now->n + 1;
		for (int i = 0; !t_now->leaf && i < child_num; i++) {
			visit_helper(t_now->child[i]);
		}
	}
}

template<typename T>
inline void BTree<T>::update_height(NPtr t_now)
{
	if (t_now->leaf) {
		return;
	} else {
		int child_num = t_now->n + 1;
		for (int i = 0; i < child_num; i++) {
			t_now->child[i]->height += 1; //每个孩子高度加一
			update_height(t_now->child[i]);
		}
	}
}

}; // namespace btree