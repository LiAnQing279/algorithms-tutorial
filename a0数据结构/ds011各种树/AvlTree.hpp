#pragma once

#include <algorithm>
#include <cstdint>
#include <functional>
#include <optional>
#include <queue>

namespace ds
{
template<typename T>
class AVLTree;

template<typename T>
class AVLTreeNode
{
  public:
	friend class AVLTree<T>;

  public:
	AVLTreeNode() = default;
	explicit AVLTreeNode(const T &key) : key_(key) {}
	AVLTreeNode(const AVLTreeNode &) = delete;
	AVLTreeNode(AVLTreeNode &&) = delete;
	~AVLTreeNode() = default;
	AVLTreeNode &operator=(const AVLTreeNode &) = delete;
	AVLTreeNode &operator=(AVLTreeNode &&) = delete;
	T key_;

  private:
	AVLTreeNode *left_{nullptr};
	AVLTreeNode *right_{nullptr};
	int height_{1};
};

template<typename T>
class AVLTree
{
  public:
	using callback_t = std::function<void(T &)>;

  public:
	AVLTree() = default;
	AVLTree(std::initializer_list<T> keys);
	AVLTree(const AVLTree &) = delete;
	AVLTree(AVLTree &&) = delete;
	~AVLTree();
	AVLTree &operator=(const AVLTree &) = delete;
	AVLTree &operator=(AVLTree &&) = delete;
	void pre_order_traversal(callback_t callback);
	void in_order_traversal(callback_t callback);
	void post_order_traversal(callback_t callback);
	void level_order_traversal(callback_t callback);
	void insert(const T &key);
	template<typename U>
	void remove(const U &key);
	template<typename U>
	auto search(const U &key);
	auto minimum();
	auto maximum();
	auto height();
	auto size();
	void clear();

  private:
	void pre_order_traversal_helper(AVLTreeNode<T> *root, callback_t callback);
	void in_order_traversal_helper(AVLTreeNode<T> *root, callback_t callback);
	void post_order_traversal_helper(AVLTreeNode<T> *root, callback_t callback);
	void breadth_first_traversal_helper(AVLTreeNode<T> *root, callback_t callback);
	auto balance(const AVLTreeNode<T> *root);
	AVLTreeNode<T> *rotate_left(AVLTreeNode<T> *root);
	AVLTreeNode<T> *rotate_right(AVLTreeNode<T> *root);
	AVLTreeNode<T> *insert_helper(AVLTreeNode<T> *root, const T &key);
	template<typename U>
	AVLTreeNode<T> *remove_helper(AVLTreeNode<T> *root, const U &key);
	template<typename U>
	AVLTreeNode<T> *search_helper(AVLTreeNode<T> *root, const U &key);
	AVLTreeNode<T> *minimum_helper(AVLTreeNode<T> *root);
	AVLTreeNode<T> *maximum_helper(AVLTreeNode<T> *root);
	auto height_helper(const AVLTreeNode<T> *root);
	auto size_helper(const AVLTreeNode<T> *root);
	void clear_helper(AVLTreeNode<T> *root);
	AVLTreeNode<T> *root_{nullptr};
};

template<typename T>
AVLTree<T>::AVLTree(std::initializer_list<T> keys)
{
	for (auto key : keys) {
		insert(key);
	}
}

template<typename T>
AVLTree<T>::~AVLTree()
{
	clear();
}

template<typename T>
void AVLTree<T>::pre_order_traversal(AVLTree::callback_t callback)
{
	pre_order_traversal_helper(root_, callback);
}

template<typename T>
void AVLTree<T>::in_order_traversal(AVLTree::callback_t callback)
{
	in_order_traversal_helper(root_, callback);
}

template<typename T>
void AVLTree<T>::post_order_traversal(AVLTree::callback_t callback)
{
	post_order_traversal_helper(root_, callback);
}

template<typename T>
void AVLTree<T>::level_order_traversal(AVLTree::callback_t callback)
{
	breadth_first_traversal_helper(root_, callback);
}

template<typename T>
void AVLTree<T>::insert(const T &key)
{
	root_ = insert_helper(root_, key);
}

template<typename T>
template<typename U>
void AVLTree<T>::remove(const U &key)
{
	root_ = remove_helper(root_, key);
}

template<typename T>
template<typename U>
auto AVLTree<T>::search(const U &key)
{
	auto res = search_helper(root_, key);
	return res ? std::optional<std::reference_wrapper<T>>{res->key_} : std::nullopt;
}

template<typename T>
auto AVLTree<T>::minimum()
{
	auto min = minimum_helper(root_);
	return min ? std::optional<std::reference_wrapper<T>>{min->key_} : std::nullopt;
}

template<typename T>
auto AVLTree<T>::maximum()
{
	auto max = maximum_helper(root_);
	return max ? std::optional<std::reference_wrapper<T>>{max->key_} : std::nullopt;
}

template<typename T>
auto AVLTree<T>::height()
{
	return height_helper(root_);
}

template<typename T>
auto AVLTree<T>::size()
{
	return size_helper(root_);
}

template<typename T>
void AVLTree<T>::clear()
{
	clear_helper(root_);
	root_ = nullptr;
}

template<typename T>
void AVLTree<T>::pre_order_traversal_helper(AVLTreeNode<T> *root, AVLTree::callback_t callback)
{
	if (!root)
		return;
	callback(root->key_);
	pre_order_traversal_helper(root->left_, callback);
	pre_order_traversal_helper(root->right_, callback);
}

template<typename T>
void AVLTree<T>::in_order_traversal_helper(AVLTreeNode<T> *root, AVLTree::callback_t callback)
{
	if (!root)
		return;
	in_order_traversal_helper(root->left_, callback);
	callback(root->key_);
	in_order_traversal_helper(root->right_, callback);
}

template<typename T>
void AVLTree<T>::post_order_traversal_helper(AVLTreeNode<T> *root, AVLTree::callback_t callback)
{
	if (!root)
		return;
	post_order_traversal_helper(root->left_, callback);
	post_order_traversal_helper(root->right_, callback);
	callback(root->key_);
}

template<typename T>
void AVLTree<T>::breadth_first_traversal_helper(AVLTreeNode<T> *root, AVLTree::callback_t callback)
{
	if (!root)
		return;
	std::queue<AVLTreeNode<T> *> queue;
	queue.push(root);
	while (!queue.empty()) {
		AVLTreeNode<T> *current{queue.front()};
		callback(current->key_);
		queue.pop();
		if (current->left_)
			queue.push(current->left_);
		if (current->right_)
			queue.push(current->right_);
	}
}

template<typename T>
auto AVLTree<T>::balance(const AVLTreeNode<T> *root)
{
	if (!root)
		return 0;
	return height_helper(root->left_) - height_helper(root->right_);
}

template<typename T>
AVLTreeNode<T> *AVLTree<T>::rotate_left(AVLTreeNode<T> *root)
{
	AVLTreeNode<T> *pivot{root->right_};
	AVLTreeNode<T> *orphan{pivot->left_};

	pivot->left_ = root;
	root->right_ = orphan;

	root->height_ = std::max(height_helper(root->left_), height_helper(root->right_)) + 1;
	pivot->height_ = std::max(height_helper(pivot->left_), height_helper(pivot->right_)) + 1;

	return pivot;
}

template<typename T>
AVLTreeNode<T> *AVLTree<T>::rotate_right(AVLTreeNode<T> *root)
{
	AVLTreeNode<T> *pivot{root->left_};
	AVLTreeNode<T> *orphan{pivot->right_};

	pivot->right_ = root;
	root->left_ = orphan;

	root->height_ = std::max(height_helper(root->left_), height_helper(root->right_)) + 1;
	pivot->height_ = std::max(height_helper(pivot->left_), height_helper(pivot->right_)) + 1;

	return pivot;
}

template<typename T>
AVLTreeNode<T> *AVLTree<T>::insert_helper(AVLTreeNode<T> *root, const T &key)
{
	if (!root)
		return new AVLTreeNode(key);
	if (key < root->key_)
		root->left_ = insert_helper(root->left_, key);
	else if (root->key_ < key)
		root->right_ = insert_helper(root->right_, key);

	root->height_ = std::max(height_helper(root->left_), height_helper(root->right_)) + 1;

	if (balance(root) > 1) {
		if (key < root->left_->key_) {
			return rotate_right(root);
		}
		if (root->left_->key_ < key) {
			root->left_ = rotate_left(root->left_);
			return rotate_right(root);
		}
	} else if (balance(root) < -1) {
		if (root->right_->key_ < key) {
			return rotate_left(root);
		}
		if (key < root->right_->key_) {
			root->right_ = rotate_right(root->right_);
			return rotate_left(root);
		}
	}

	return root;
}

template<typename T>
template<typename U>
AVLTreeNode<T> *AVLTree<T>::remove_helper(AVLTreeNode<T> *root, const U &key)
{
	if (!root)
		return nullptr;
	if (key < root->key_)
		root->left_ = remove_helper(root->left_, key);
	else if (root->key_ < key)
		root->right_ = remove_helper(root->right_, key);
	else {
		if (!root->left_ && !root->right_) {
			delete root;
			root = nullptr;
		} else if (!root->left_) {
			AVLTreeNode<T> *tmp{root};
			root = root->right_;
			delete tmp;
		} else if (!root->right_) {
			AVLTreeNode<T> *tmp{root};
			root = root->left_;
			delete tmp;
		} else {
			AVLTreeNode<T> *min{minimum_helper(root->right_)};
			root->key_ = min->key_;
			root->right_ = remove_helper(root->right_, min->key_);
			// AVLTreeNode<T> *max{Maximum(root->left_)};
			// root->key_ = max->key_;
			// root->left_ = remove(root->left_, max->key_);
		}
	}

	if (!root)
		return nullptr;

	root->height_ = std::max(height_helper(root->left_), height_helper(root->right_)) + 1;

	if (balance(root) > 1) {
		if (balance(root->left_) >= 0) {
			return rotate_right(root);
		}
		root->left_ = rotate_left(root->left_);
		return rotate_right(root);
	}
	if (balance(root) < -1) {
		if (balance(root->right_) <= 0) {
			return rotate_left(root);
		}
		root->right_ = rotate_right(root->right_);
		return rotate_left(root);
	}

	return root;
}

template<typename T>
template<typename U>
AVLTreeNode<T> *AVLTree<T>::search_helper(AVLTreeNode<T> *root, const U &key)
{
	while (root) {
		if (root->key_ < key) {
			root = root->right_;
		} else if (key < root->key_) {
			root = root->left_;
		} else {
			return root;
		}
	}
	return nullptr;
}

template<typename T>
AVLTreeNode<T> *AVLTree<T>::minimum_helper(AVLTreeNode<T> *root)
{
	if (!root)
		return nullptr;
	while (root->left_)
		root = root->left_;
	return root;
}

template<typename T>
AVLTreeNode<T> *AVLTree<T>::maximum_helper(AVLTreeNode<T> *root)
{
	if (!root)
		return nullptr;
	while (root->right_)
		root = root->right_;
	return root;
}

template<typename T>
auto AVLTree<T>::height_helper(const AVLTreeNode<T> *root)
{
	if (!root)
		return 0;
	return root->height_;
}

template<typename T>
auto AVLTree<T>::size_helper(const AVLTreeNode<T> *root)
{
	if (!root)
		return 0;
	return size_helper(root->left_) + size_helper(root->right_) + 1;
}

template<typename T>
void AVLTree<T>::clear_helper(AVLTreeNode<T> *root)
{
	if (!root)
		return;
	if (root->left_)
		clear_helper(root->left_);
	if (root->right_)
		clear_helper(root->right_);
	delete root;
}
} // namespace ds
