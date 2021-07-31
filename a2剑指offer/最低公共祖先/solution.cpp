#include "bitree.h"

class Solution
{
public:
    typedef vector<TreeNode *> Road;
    /**
     * @brief 查找二叉树p,q所指位置的最近祖先
     * 
     * @param root 二叉树根节点指针
     * @param p 待查元素指针
     * @param q 待查元素指针
     * @return TreeNode* 最近公共祖先的指针
     */
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        Road p_road, q_road;
        dfs(root, p, p_road);
        dfs(root, q, q_road);

        return get(q_road, p_road);
    }

    /**
     * @brief 得到先序查找的路径
     * 
     * @param root 二叉树根节点指针
     * @param goal 待查找元素指针
     * @param road 记录从根到当前节点的指针序列
     * @return int 代表一种信息，当前路径不含目标值为0，反之为一
     */
    int dfs(TreeNode *root, TreeNode *goal, Road &road)
    {
        if (root)
        {
            if (root->val == goal->val)
            {
                road.push_back(goal);
                return 1;
            }
            road.push_back(root);
            int msg_l = dfs(root->left, goal, road);
            if (msg_l)
                return 1; //剪枝加速，删掉不影响逻辑
            int msg_r = dfs(root->right, goal, road);
            if (msg_r)
                return 1;

            // 左右孩子都找不到，自己也得被弹出
            if (msg_r == 0 && msg_l == 0)
            {
                road.pop_back();
                return 0;
            }
        }
        return 0;
    }
    /**
     * @brief 求两条路的第一个分叉点
     * 
     * @param a 
     * @param b 
     * @return TreeNode* 指向分叉值的指针
     */
    TreeNode *get(Road a, Road b)
    {
        int pos = 0;
        int pre = 0;
        int alen = a.size(), blen = b.size();
        while (pos < alen && pos < blen)
        {
            if (a[pos]->val == b[pos]->val)
            {
                pre = pos++;
            }
            else
                return a[pre];
        }
        return nullptr;
    }
};

int main()
{
    // testBiTree();
    //创建一棵测试树
    vector<int> v{12344, 2, 33, 201, 444, -1, 555};
    BiTree bitree(v);

    Solution sol;
    TNptr ans = sol.lowestCommonAncestor(bitree.find(12344), bitree.find(444), bitree.find(201));
    cout << ans->val << endl;
    return 0;
}