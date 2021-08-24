#pragma once
#include <iostream>

/*
**静态成员函数与普通成员函数的根本区别在于：普通成员函数有 this 指针，可以访问类中的任意成员；
**而静态成员函数没有 this 指针，只能访问静态成员（包括静态成员变量和静态成员函数）。
*/

namespace ds
{

template<typename Object>
class BiTreeNode
{
  public:
	BiTreeNode(const Object &t_element = Object(), BiTreeNode *t_left = nullptr, BiTreeNode *t_right = nullptr)
		: element(t_element), left(t_left), right(t_right)
	{
	}

	static int size(BiTreeNode *t_ptr);
	static int height(BiTreeNode *t_ptr);

	void printPreOrder() const;
	void printPostOrder() const;
	void printInOrder() const;

	BiTreeNode *duplicate() const;

  public:
	Object element;
	BiTreeNode *left;
	BiTreeNode *right;
};

template<class Object>
class BinaryTree
{
  public:
	BinaryTree() : root(nullptr) {}
	BinaryTree(const Object &rootItem) : root(new Node(rootItem)) {}
	BinaryTree(const BinaryTree &rhs) : root(nullptr) { *this = rhs; }

	~BinaryTree() { makeEmpty(); }

	const BinaryTree &operator=(const BinaryTree &rhs);

	// Recursive traversals, with printing
	void printPreOrder() const
	{
		if (root != nullptr)
			root->printPreOrder();
	}
	void printInOrder() const
	{
		if (root != nullptr)
			root->printInOrder();
	}
	void printPostOrder() const
	{
		if (root != nullptr)
			root->printPostOrder();
	}

	void makeEmpty() { makeEmpty(root); }
	bool isEmpty() const { return root == nullptr; }

	// Combine t1 and t2
	void merge(const Object &rootItem, BinaryTree &t1, BinaryTree &t2);

	int size() const { return Node::size(root); }
	int height() const { return Node::height(root); }

  private:
	typedef BiTreeNode<Object> Node;
	Node *root;

	// friend class TreeIterator<Object>;
	void makeEmpty(BiTreeNode<Object> *&t);
};

// Return size of tree rooted at t.
template<class Object>
int BiTreeNode<Object>::size(BiTreeNode<Object> *t)
{
	if (t == nullptr)
		return 0;
	else
		return 1 + size(t->left) + size(t->right);
}

#define max MAX

template<class Comparable>
Comparable max(const Comparable &a, const Comparable &b)
{
	return a > b ? a : b;
}

// Return height of tree rooted at t.
template<class Object>
int BiTreeNode<Object>::height(BiTreeNode<Object> *t)
{
	if (t == nullptr)
		return -1;
	else
		return 1 + max(height(t->left), height(t->right));
}

#undef max

// Print the tree rooted at current node using preorder traversal.
template<class Object>
void BiTreeNode<Object>::printPreOrder() const
{
	std::cout << element << std::endl; // Node
	if (left != nullptr)
		left->printPreOrder(); // Left
	if (right != nullptr)
		right->printPreOrder(); // Right
}

// Print the tree rooted at current node using postorder traversal.
template<class Object>
void BiTreeNode<Object>::printPostOrder() const
{
	if (left != nullptr) // Left
		left->printPostOrder();
	if (right != nullptr) // Right
		right->printPostOrder();
	std::cout << element << std::endl; // Node
}

// Print the tree rooted at current node using inorder traversal.
template<class Object>
void BiTreeNode<Object>::printInOrder() const
{
	if (left != nullptr) // Left
		left->printInOrder();
	std::cout << element << std::endl; // Node
	if (right != nullptr)
		right->printInOrder(); // Right
}

// Return a pointer to a node that is the root of a
// duplicate of the tree rooted at the current node.
template<class Object>
BiTreeNode<Object> *BiTreeNode<Object>::duplicate() const
{
	BiTreeNode<Object> *root = new BiTreeNode<Object>(element);

	if (left != nullptr)				  // If there's a left subtree
		root->left = left->duplicate();	  // Duplicate; attach
	if (right != nullptr)				  // If there's a right subtree
		root->right = right->duplicate(); // Duplicate; attach

	return root; // Return resulting tree
}

// Deep copy.
template<class Object>
const BinaryTree<Object> &BinaryTree<Object>::operator=(const BinaryTree<Object> &rhs)
{
	if (this != &rhs) {
		makeEmpty();
		if (rhs.root != nullptr)
			root = rhs.root->duplicate();
	}

	return *this;
}

// Merge routine for BinaryTree class.
// Forms a new tree from rootItem, t1 and t2.
// Does not allow t1 and t2 to be the same.
// Correctly handles other aliasing conditions.
template<class Object>
void BinaryTree<Object>::merge(const Object &rootItem, BinaryTree<Object> &t1, BinaryTree<Object> &t2)
{
	if (t1.root == t2.root && t1.root != nullptr) {
		std::cerr << "Cannot merge a tree with itself; merge aborted." << std::endl;
		return;
	}

	Node *oldRoot = root; // Save old root

	// Allocate new node
	root = new Node(rootItem, t1.root, t2.root);

	// Deallocate nodes in the original tree
	if (this != &t1 && this != &t2)
		makeEmpty(oldRoot);

	// Ensure that every node is in one tree
	if (this != &t1)
		t1.root = nullptr;
	if (this != &t2)
		t2.root = nullptr;
}

// Make tree rooted at t empty, freeing nodes, and setting t to nullptr.
template<class Object>
void BinaryTree<Object>::makeEmpty(BiTreeNode<Object> *&t)
{
	if (t != nullptr) {
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
		t = nullptr;
	}
}
} // namespace ds
