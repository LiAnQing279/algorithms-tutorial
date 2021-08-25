#pragma once
#include <algorithm>
#include <functional>
#include <initializer_list>
#include <queue>

namespace ds
{

using Object = int;

class Node
{
  public:
	Node() = default;
	Node(const Object &t_val, Node *t_left = nullptr, Node *t_right = nullptr, int t_height = 0)
		: val(t_val), left(t_left), right(t_right), height(t_height)
	{
	}

  public:
	Node *left{nullptr};
	Node *right{nullptr};
	int height{0};
	Object val;
};

using Ptr = Node *;

class AvlTree
{
	using callback_t = std::function<void(Object &)>;

  public:
	AvlTree() = default;
	AvlTree(const std::initializer_list<Object> &keys);
	~AvlTree() { clear_helper(m_root); }

	void insert(const Object &);
	void remove(const Object &);
	bool contains(const Object &);

	void print(callback_t);

  private:
	Ptr m_root = nullptr;

	// 细细体会这个指针的引用
	void insert_helper(const Object &, Ptr &);
	void remove_helper(const Object &, Ptr &);
	void balancing(Ptr &);

	void rightRotation(Ptr &);
	void leftRotation(Ptr &);
	void leftRightRotation(Ptr &);
	void rightLeftRotation(Ptr &);

	int height(Ptr p) { return p ? p->height : -1; } //叶子高度是零，空指针是-1

	Ptr findMax(Ptr);
	Ptr findMin(Ptr);

	void bfs_helper(Ptr, callback_t);
	Ptr find_helper(const Object &, Ptr);
	void clear_helper(Ptr);
};

AvlTree::AvlTree(const std::initializer_list<Object> &keys)
{
	auto it = keys.begin();
	auto stop = keys.end();
	while (it != stop) {
		insert(*it++);
	}
}

inline void AvlTree::insert(const Object &t_obj)
{
	insert_helper(t_obj, m_root);
}

inline void AvlTree::remove(const Object &t_obj)
{
	remove_helper(t_obj, m_root);
}

inline bool AvlTree::contains(const Object &t_obj)
{
	return find_helper(t_obj, m_root) != nullptr;
}

inline void AvlTree::print(callback_t callback)
{
	bfs_helper(m_root, callback);
}

inline void AvlTree::insert_helper(const Object &t_obj, Ptr &t_ptr)
{
	if (t_ptr == nullptr) {
		t_ptr = new Node(t_obj);
	}
	if (t_ptr->val < t_obj) {
		insert_helper(t_obj, t_ptr->right);
	} else if (t_ptr->val > t_obj) {
		insert_helper(t_obj, t_ptr->left);
	} else {
		return; //已经存在什么也不做
	}

	balancing(t_ptr);
}

inline void AvlTree::remove_helper(const Object &t_obj, Ptr &t_ptr)
{
	if (t_ptr == nullptr)
		return;
	if (t_ptr->val < t_obj) {
		remove_helper(t_obj, t_ptr->right);
	} else if (t_ptr->val > t_obj) {
		remove_helper(t_obj, t_ptr->left);
	} else if (t_ptr->left && t_ptr->right) {
		//有两个儿子
		t_ptr->val = findMax(t_ptr->left)->val;
		remove_helper(t_ptr->val, t_ptr->left);
	} else {
		Ptr old = t_ptr;
		t_ptr = t_ptr->left ? t_ptr->left : t_ptr->right;
		delete old;
	}

	balancing(t_ptr);
}

inline Ptr AvlTree::find_helper(const Object &t_obj, Ptr ptr)
{
	if (ptr == nullptr)
		return nullptr;

	Ptr ans = nullptr;
	if (ptr->val < t_obj) {
		ans = find_helper(t_obj, ptr->right);
	} else if (ptr->val > t_obj) {
		ans = find_helper(t_obj, ptr->left);
	} else
		ans = ptr;
	return ans;
}

inline void AvlTree::clear_helper(Ptr ptr)
{
	if (ptr == nullptr)
		return;
	if (ptr->left)
		clear_helper(ptr->left);
	if (ptr->right)
		clear_helper(ptr->right);
	delete ptr;
}

static int ALLOWED_UNBALANCE = 1;
inline void AvlTree::balancing(Ptr &t_ptr)
{
	if (t_ptr == nullptr)
		return;
	Ptr lson = t_ptr->left, rson = t_ptr->right;

	if (height(lson) - height(rson) > ALLOWED_UNBALANCE) {
		if (height(lson->left) >= height(lson->right)) {
			rightRotation(t_ptr);
		} else {
			leftRightRotation(t_ptr);
		}
	} else if (height(rson) - height(lson) > ALLOWED_UNBALANCE) {
		if (height(rson->right) >= height(rson->left)) {
			leftRotation(t_ptr);
		} else {
			rightLeftRotation(t_ptr);
		}
	}

	//递归回来之后，t_ptr已经改变，t_ptr->left != lson
	t_ptr->height = std::max(height(t_ptr->left), height(t_ptr->right)) + 1;
}

inline Ptr AvlTree::findMax(Ptr ptr)
{
	if (ptr == nullptr)
		return nullptr;
	while (ptr->right)
		ptr = ptr->right;
	return ptr;
}
inline Ptr AvlTree::findMin(Ptr ptr)
{
	if (ptr == nullptr)
		return nullptr;
	while (ptr->left)
		ptr = ptr->left;
	return ptr;
}

inline void AvlTree::rightRotation(Ptr &ptr)
{
	Ptr pivot = ptr->left;
	Ptr orphan = pivot->right;

	pivot->right = ptr;
	ptr->left = orphan;

	//注意这两个更新的次序不能颠倒了
	ptr->height = std::max(height(ptr->left), height(ptr->right)) + 1;
	pivot->height = std::max(height(pivot->left), height(pivot->right)) + 1;

	ptr = pivot;
}

inline void AvlTree::leftRotation(Ptr &ptr)
{
	Ptr pivot = ptr->right;
	Ptr orphan = pivot->left;

	pivot->left = ptr;
	ptr->right = orphan;
	// 更加简明的
	ptr->height = std::max(height(ptr->left), height(ptr->right)) + 1;
	pivot->height = std::max(ptr->height, height(pivot->right)) + 1;

	ptr = pivot;
}

inline void AvlTree::leftRightRotation(Ptr &ptr)
{
	// 巧合的先左旋左孩子，再右旋自己
	leftRotation(ptr->left);
	rightRotation(ptr);
}

inline void AvlTree::rightLeftRotation(Ptr &ptr)
{
	// 先右旋右孩子，然后左旋自己
	rightRotation(ptr->right);
	leftRotation(ptr);
}

inline void AvlTree::bfs_helper(Ptr ptr, callback_t callback)
{
	if (!ptr)
		return;
	std::queue<Ptr> queue;
	queue.push(ptr);
	while (!queue.empty()) {
		Ptr current{queue.front()};
		callback(current->val);
		queue.pop();
		if (current->left)
			queue.push(current->left);
		if (current->right)
			queue.push(current->right);
	}
}

} // namespace ds

#include <iostream>

void visit(int x)
{
	std::cout << x << " ";
}
void test_avl()
{

	ds::AvlTree tree;
	// insert
	tree.insert(8);
	tree.insert(25);
	tree.insert(13);
	tree.print(visit);
	std::cout << std::endl;

	tree.insert(7);
	tree.insert(2);
	tree.print(visit);
	std::cout << std::endl;

	tree.insert(10);
	tree.print(visit);
	std::cout << std::endl;

	tree.insert(5);
	tree.print(visit);
	std::cout << std::endl;

	// remove
	if (tree.contains(13))
		tree.remove(8);
	tree.print(visit);
	std::cout << std::endl;
}