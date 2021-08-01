#pragma once
#include <vector>
#include <unordered_map>
using namespace std;
struct TreeNode
{
    int m_nValue;
    vector<TreeNode *> m_vChildren;
    TreeNode(int v) : m_nValue(v)
    {
        m_vChildren.clear();
    }
};

typedef TreeNode *Ptr;

Ptr CreateTreeNode(int value);
void ConnectTreeNodes(Ptr pParent, Ptr pChild);
void PrintTreeNode(const Ptr pNode);
void PrintTree(const Ptr pRoot);
void DestroyTree(Ptr pRoot);
Ptr SetTree(vector<int> &vals, vector<vector<int>> &sons);
Ptr findVal(Ptr root, int value);

Ptr CreateTreeNode(int value)
{
    Ptr pNode = new TreeNode(value);
    return pNode;
}

void ConnectTreeNodes(Ptr pParent, Ptr pChild)
{
    if (pParent != nullptr)
    {
        pParent->m_vChildren.push_back(pChild);
    }
}

void PrintTreeNode(const Ptr pNode)
{
    if (pNode != nullptr)
    {
        printf("value of this node is: %d.\n", pNode->m_nValue);

        printf("its children is as the following:\n");
        vector<Ptr>::const_iterator i = pNode->m_vChildren.begin();
        while (i < pNode->m_vChildren.end())
        {
            if (*i != nullptr)
                printf("%d\t", (*i)->m_nValue);
        }

        printf("\n");
    }
    else
    {
        printf("this node is nullptr.\n");
    }

    printf("\n");
}

void PrintTree(const Ptr pRoot)
{
    PrintTreeNode(pRoot);

    if (pRoot != nullptr)
    {
        vector<Ptr>::const_iterator i = pRoot->m_vChildren.begin();
        while (i < pRoot->m_vChildren.end())
        {
            PrintTree(*i);
            ++i;
        }
    }
}

void DestroyTree(Ptr pRoot)
{
    if (pRoot != nullptr)
    {
        vector<Ptr>::iterator i = pRoot->m_vChildren.begin();
        while (i < pRoot->m_vChildren.end())
        {
            DestroyTree(*i);
            ++i;
        }

        delete pRoot;
    }
}

/**
 * @brief Create a Tree object
 * 
 * @param vals 所有的节点值，保证第一个是根节点
 * @param starts 起点值
 * @param ends 终点值
 * @return Ptr 返回树的根指针
 */

Ptr SetTree(vector<int> &vals, vector<vector<int>> &sons)
{

    int N = vals.size();
    unordered_map<int, Ptr> table;

    for (int i = 0; i < N; i++)
    {
        table[vals[i]] = new TreeNode(vals[i]);
    }

    int M = sons.size();
    for (int i = 0; i < M; i++)
    {
        int n = sons[i].size();
        for (int s = 0; s < n; s++)
        {
            table[vals[i]]->m_vChildren.push_back(table[sons[i][s]]);
        }
    }

    return table[vals[0]];
}

Ptr findVal(Ptr root, int value)
{
    if (root)
    {
        if (root->m_nValue == value)
            return root;
        Ptr ans = nullptr;
        vector<Ptr>::const_iterator i = root->m_vChildren.begin();
        while (!ans && i < root->m_vChildren.end())
        {
            ans = findVal(*i, value);
            i++;
        }
        if (ans)
            return ans;
    }
    return nullptr;
}