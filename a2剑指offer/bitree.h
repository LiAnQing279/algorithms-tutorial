#pragma once

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//辅助工具
typedef TreeNode *TNptr;

template <typename T>
TNptr setNode(T val)
{
    return new TreeNode(val);
}

//二叉树，构建，销毁，打印
class BiTree
{
private:
    TNptr m_root = nullptr;
    void destroy(TNptr);
    void preVis(TNptr);
    TNptr getPtr(TNptr, int);

public:
    BiTree(vector<int> vals);
    ~BiTree();

    TNptr find(int val);
    void printTree();
};

/**
 * @brief Construct a new Bi Tree:: Bi Tree object
 * 
 * @param vals 层次遍历形式的数组，空位置用-1代指，结构是一棵满二叉树
 */
BiTree::BiTree(vector<int> vals)
{
    if (vals.empty() || vals[0] == -1)
        return;

    queue<TNptr> que;
    m_root = setNode(vals[0]);
    que.push(m_root);

    int len = vals.size();
    int loops = len / 2;
    for (int i = 0; i < loops; i++)
    {
        TNptr ptr = que.front();
        que.pop();
        if (!ptr)
            continue;
        int left = 2 * i + 1, right = 2 * i + 2;
        if (left < len && vals[left] != -1)
        {
            ptr->left = setNode(vals[left]);
            que.push(ptr->left);
        }
        if (right < len && vals[right] != -1)
        {
            ptr->right = setNode(vals[right]);
            que.push(ptr->right);
        }
    }
}

BiTree::~BiTree()
{
    destroy(m_root);
}
void BiTree::destroy(TNptr ptr)
{
    if (!ptr)
        return;
    TNptr tmp = ptr;
    destroy(tmp->left);
    destroy(tmp->right);

    delete ptr;
    ptr = nullptr;
}

void BiTree::printTree()
{
    cout << "preVis: ";
    preVis(m_root);
}

void BiTree::preVis(TNptr ptr)
{
    if (ptr)
    {
        cout << ptr->val << " ";
        preVis(ptr->left);
        preVis(ptr->right);
    }
}
TNptr BiTree::find(int val)
{
    return getPtr(m_root, val);
}
TNptr BiTree::getPtr(TNptr ptr, int goal)
{
    if (ptr)
    {
        if (ptr->val == goal)
            return ptr;
        TNptr l = getPtr(ptr->left, goal);
        if (!l)
            return getPtr(ptr->right, goal);
        else
            return l;
    }
    return nullptr;
}

void testBiTree()
{
    vector<int> v{12, 1, 24, -1, 7, -1, 22};
    BiTree bitree(v);
    cout << bitree.find(22)->val << endl;
    bitree.printTree();
}