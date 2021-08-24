
#include "BinaryTree.hpp"
#include <stack>
#include <string>
using std::stack;
using std::string;
using biTree = ds::BinaryTree<int>;
using biNode = ds::BiTreeNode<int>;
using biPtr = ds::BiTreeNode<int> *;

bool isOp(int ch)
{
	return ch == '+' || ch == '-' || ch == '/' || ch == '*';
}
/**
 * @brief 将后缀表达式构造一颗二叉的表达式树，同后缀表达式计算值类似
 *
 * @param t_suffix
 * @return biPtr
 */
biPtr suffixToExpTree(string t_suffix)
{
	stack<biPtr> stk;
	biPtr root = nullptr;
	stk.push(root);

	int i = 0;
	int size = t_suffix.size();
	while (i < size) {
		int ch = t_suffix[i++];

		if (isOp(ch)) {
			biPtr b = stk.top();
			stk.pop();
			biPtr a = stk.top();
			stk.pop();
			stk.push(new biNode(ch, a, b));

		} else {
			stk.push(new biNode(ch));
		}
	}

	return stk.top();
}

void postOrder(biPtr root)
{
	if (root) {
		postOrder(root->left);
		postOrder(root->right);
		std::cout << char(root->element) << " ";
	}
}

int main()
{
	string tmp = "ab+cde+**";
	biPtr ans = suffixToExpTree(tmp);
	// ans->printInOrder();
	postOrder(ans);
	return 0;
}