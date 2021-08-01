#include <list>
#include <cstdio>
#include <iostream>
#include "tree.h"

using namespace std;
typedef const TreeNode *constPtr;
typedef list<constPtr> Road;

/**
 * @brief 参考 剑指offer的o01最低公共祖先
 * 
 */
class Solution
{
public:
    void showRoad(Road &road)
    {
        list<constPtr>::const_iterator i = road.begin();
        cout << "Path: ";
        while (i != road.end())
        {
            cout << (*i)->m_nValue << " ";
            i++;
        }
        cout << endl;
    }

    /**
     * @brief 查找二叉树p,q所指位置的最近祖先
     * 
     * @param root 二叉树根节点指针
     * @param p 待查元素指针
     * @param q 待查元素指针
     * @return TreeNode* 最近公共祖先的指针
     */
    constPtr lowestCommonAncestor(constPtr root, constPtr p, constPtr q)
    {
        if (root == nullptr)
            return nullptr;
        Road pRoad, qRoad;
        dfs(root, p, pRoad);
        // showRoad(pRoad);
        dfs(root, q, qRoad);

        return get(qRoad, pRoad);
    }

    /**
     * @brief 得到先序查找的路径
     * 
     * @param root 二叉树根节点指针
     * @param goal 待查找元素指针
     * @param road 记录从根到当前节点的指针序列
     * @return int 代表一种信息，当前路径不含目标值为0，反之为一
     */
    int dfs(constPtr root, constPtr goal, Road &road)
    {
        if (root)
        {
            if (root == goal)
                return 1;
            road.push_back(root);

            int msg = 0;
            vector<TreeNode *>::const_iterator i = root->m_vChildren.begin();
            while (!msg && i < root->m_vChildren.end())
            {
                msg = dfs(*i, goal, road);
                ++i;
            }
            if (msg < 1)
                road.pop_back();
            return 1;
        }
        return 0;
    }
    /**
     * @brief 求两条路的第一个分叉点
     * @return TreeNode* 指向分叉值的指针
     */
    constPtr get(Road &aRoad, Road &bRoad)
    {
        typedef list<constPtr>::iterator listIdx;

        listIdx aIdx = aRoad.begin();
        listIdx bIdx = bRoad.begin();
        listIdx pre;

        while (aIdx != aRoad.end() && bIdx != bRoad.end())
        {
            if ((*aIdx) == (*bIdx)) //指向同一节点的指针的值相同
            {
                pre = aIdx;
                ++aIdx;
                ++bIdx;
            }
            else
            {
                break;
            }
        }
        return (*pre);
    }
};

void Test(const char *testName, constPtr pRoot, constPtr pNode1, constPtr pNode2, TreeNode *pExpected)
{
    if (testName != nullptr)
        printf("%s begins: ", testName);

    Solution sol;
    constPtr pResult = sol.lowestCommonAncestor(pRoot, pNode1, pNode2);

    if ((pExpected == nullptr && pResult == nullptr) ||
        (pExpected != nullptr && pResult != nullptr && pResult->m_nValue == pExpected->m_nValue))
        printf("Passed.\n");
    else
        printf("Failed.\n");
}

void Test0()
{
    vector<int> vals{700, 100, 600, 10, 20, 70, 200, 150, 250};
    vector<vector<int>> sons{
        {100, 600},
        {10, 20, 70},
        {200, 150, 250}};
    TreeNode *root = SetTree(vals, sons);
    // PrintTree(root);
    constPtr p = findVal(root, 70);
    constPtr q = findVal(root, 100);
    Test("Test0", root, q, p, root);
}

// 形状普通的树
//              1
//            /   \
//           2     3
//       /       \
//      4         5
//     / \      / |  \
//    6   7    8  9  10
void Test1()
{
    TreeNode *pNode1 = CreateTreeNode(1);
    TreeNode *pNode2 = CreateTreeNode(2);
    TreeNode *pNode3 = CreateTreeNode(3);
    TreeNode *pNode4 = CreateTreeNode(4);
    TreeNode *pNode5 = CreateTreeNode(5);
    TreeNode *pNode6 = CreateTreeNode(6);
    TreeNode *pNode7 = CreateTreeNode(7);
    TreeNode *pNode8 = CreateTreeNode(8);
    TreeNode *pNode9 = CreateTreeNode(9);
    TreeNode *pNode10 = CreateTreeNode(10);

    ConnectTreeNodes(pNode1, pNode2);
    ConnectTreeNodes(pNode1, pNode3);

    ConnectTreeNodes(pNode2, pNode4);
    ConnectTreeNodes(pNode2, pNode5);

    ConnectTreeNodes(pNode4, pNode6);
    ConnectTreeNodes(pNode4, pNode7);

    ConnectTreeNodes(pNode5, pNode8);
    ConnectTreeNodes(pNode5, pNode9);
    ConnectTreeNodes(pNode5, pNode10);

    Test("Test1", pNode1, pNode4, pNode10, pNode2);
}

// 树退化成一个链表
//               1
//              /
//             2
//            /
//           3
//          /
//         4
//        /
//       5
void Test2()
{
    TreeNode *pNode1 = CreateTreeNode(1);
    TreeNode *pNode2 = CreateTreeNode(2);
    TreeNode *pNode3 = CreateTreeNode(3);
    TreeNode *pNode4 = CreateTreeNode(4);
    TreeNode *pNode5 = CreateTreeNode(5);

    ConnectTreeNodes(pNode1, pNode2);
    ConnectTreeNodes(pNode2, pNode3);
    ConnectTreeNodes(pNode3, pNode4);
    ConnectTreeNodes(pNode4, pNode5);

    Test("Test2", pNode1, pNode5, pNode4, pNode3);
}

// 树退化成一个链表，一个结点不在树中
//               1
//              /
//             2
//            /
//           3
//          /
//         4
//        /
//       5
void Test3()
{
    TreeNode *pNode1 = CreateTreeNode(1);
    TreeNode *pNode2 = CreateTreeNode(2);
    TreeNode *pNode3 = CreateTreeNode(3);
    TreeNode *pNode4 = CreateTreeNode(4);
    TreeNode *pNode5 = CreateTreeNode(5);

    ConnectTreeNodes(pNode1, pNode2);
    ConnectTreeNodes(pNode2, pNode3);
    ConnectTreeNodes(pNode3, pNode4);
    ConnectTreeNodes(pNode4, pNode5);

    TreeNode *pNode6 = CreateTreeNode(6);

    Test("Test3", pNode1, pNode5, pNode6, nullptr);
}

// 输入nullptr
void Test4()
{
    Test("Test4", nullptr, nullptr, nullptr, nullptr);
}

int main(int argc, char *argv[])
{
    Test0();
    Test1();
    Test2();
    Test3();
    Test4();

    return 0;
}