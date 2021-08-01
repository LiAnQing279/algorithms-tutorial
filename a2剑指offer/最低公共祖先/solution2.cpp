#include <list>
#include "bitree.h"
/**
 * @brief 几个细节的调整
 * 1. 当指针在函数内不改变时，要加上const限制
 * 2. 把记录路径的数据结构改为list，强调平凡的插入，而只需要访问一次
 * 3. 指向同一个节点的指针的值是相同的，不用刻意强调所指的值相同
 * 4. 加入一个测试函数，尽量定义有意义的名字(驼峰)，不要用单个字符
 */

class Solution
{
public:
    typedef const TreeNode *constPtr;
    typedef list<constPtr> Road;

    void showRoad(Road &road)
    {
        list<constPtr>::iterator i = road.begin();
        cout << "Path: ";
        while (i != road.end())
        {
            cout << (*i)->val << " ";
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
            msg = dfs(root->left, goal, road);
            if (msg)
                return 1;

            msg = dfs(root->right, goal, road);
            if (msg)
                return 1;

            // 左右孩子都找不到，自己也得被弹出
            road.pop_back();
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

int main()
{
    /**
     * @brief 创建一棵测试二叉树
     *           700
     *          /   \
     *         100   600
     *        / \   /  \
     *       30 70 200  400
     */
    vector<int> v{700, 100, 600, 30, 70, 400, 200};
    BiTree bitree(v);
    Ptr root = bitree.find(700);
    Ptr p = bitree.find(70);
    Ptr q = bitree.find(30);

    //查找50 和 50的最低的共同祖先
    Solution sol;
    int ans = sol.lowestCommonAncestor(root, p, q)->val;
    cout << ans << endl;
    return 0;
}