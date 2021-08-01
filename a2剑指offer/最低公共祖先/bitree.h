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
typedef TreeNode *Ptr; //树节点指针

template <typename T>
Ptr setNode(T val)
{
    return new TreeNode(val);
}

//二叉树，构建，销毁，打印
class BiTree
{
private:
    Ptr m_root = nullptr;
    void destroy(Ptr);
    void preVis(Ptr);
    Ptr getPtr(Ptr, int);

public:
    BiTree(vector<int> vals);
    ~BiTree();

    Ptr find(int val);
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

    queue<Ptr> que;
    m_root = setNode(vals[0]);
    que.push(m_root);

    int len = vals.size();
    int loops = len / 2;
    for (int i = 0; i < loops; i++)
    {
        Ptr ptr = que.front();
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
void BiTree::destroy(Ptr ptr)
{
    if (!ptr)
        return;
    Ptr tmp = ptr;
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

void BiTree::preVis(Ptr ptr)
{
    if (ptr)
    {
        cout << ptr->val << " ";
        preVis(ptr->left);
        preVis(ptr->right);
    }
}
Ptr BiTree::find(int val)
{
    return getPtr(m_root, val);
}
Ptr BiTree::getPtr(Ptr ptr, int goal)
{
    if (ptr)
    {
        if (ptr->val == goal)
            return ptr;
        Ptr l = getPtr(ptr->left, goal);
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