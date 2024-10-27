// https://leetcode.com/problems/height-of-binary-tree-after-subtree-removal-queries/description
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct TreeCacheNode {
    int height;
    int level;
    int parent;
    int val = 0;
    int other = 0;
    TreeCacheNode(int x) : height(x) {}
    TreeCacheNode(int x, int l, int p, int v, int o) : height(x), level(l), parent(p), val(v), other(o) {}
    TreeCacheNode() {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution
{
public:
    static void fillTreeNode(vector<int>& input, int pos, TreeNode* pCurNode) {
        int size = input.size();
        int leftPos = 2 * pos + 1;
        if (leftPos < size) {
            int leftVal = input[leftPos];
            if (leftVal > 0) {
                pCurNode->left = new TreeNode(leftVal);
                fillTreeNode(input, leftPos, pCurNode->left);
            }
        }
        int rightPos = 2 * pos + 2;
        if (rightPos < size) {
            int rightVal = input[rightPos];
            if (rightVal > 0) {
                pCurNode->right = new TreeNode(rightVal);
                fillTreeNode(input, rightPos, pCurNode->right);
            }
        }
    }

    static void outputTree(TreeNode* pTn, char position, int level) {
        if (pTn == nullptr) return;
        cout << std::string( level, ' ' ) << position << " " << pTn -> val << endl;
        outputTree(pTn -> left, 'l', level + 1);
        outputTree(pTn -> right, 'r', level + 1);
    }

    static TreeCacheNode calcTreeCache(const TreeNode* pT, unordered_map<int, TreeCacheNode>& cache, int level, int parent) {
        if (pT == nullptr) return TreeCacheNode(-1);

        int curVal = pT->val;
        if (curVal == 0) return TreeCacheNode(-1);

        TreeCacheNode leftCache = calcTreeCache(pT -> left, cache, level + 1, curVal);
        TreeCacheNode rightCache = calcTreeCache(pT -> right, cache, level + 1, curVal);
        if (leftCache.val !=0) cache[leftCache.val].other = rightCache.val;
        if (rightCache.val != 0) cache[rightCache.val].other = leftCache.val;

        int curHeight = max(leftCache.height, rightCache.height) +1;
        TreeCacheNode curCache = TreeCacheNode(curHeight, level, parent, curVal, 0);
        cache[curVal] = curCache;

        return curCache;
    }

    vector<int> treeQueries(TreeNode* pRoot, vector<int>& queries) {
        vector<int> res;

        unordered_map<int, TreeCacheNode> cache;
        Solution::calcTreeCache(pRoot, cache, 0, -1);
        for (auto x : cache)
            cout << x.first << ": " << x.second.height << " " << x.second.level << " " << x.second.parent << " : " << x.second.val << " " << x.second.other << endl;
        
        // int wholeHeight = cache[pRoot->val].height;
        // for (int& i: queries) {
        //     TreeCacheNode tc = cache[i];
        //     int qHeight = tc.height;
        //     int otherHeight = tc.other == 0 ? 0 : cache[tc.other].height;
        //     int newHeight = tc.level + otherHeight;
        //     while 
        // }

        return res;
    }
};

int main()
{
    Solution s;

    // vector<int> input{ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
    vector<int> input = { 1,3,4,2,0,6,5,0,0,0, 0, 0, 0, 0, 7 };
    
    TreeNode* pRootNode = new TreeNode(input[0]);
    Solution::fillTreeNode(input, 0, pRootNode);
    Solution::outputTree(pRootNode, 's', 0);

    vector<int> queries = { 4 };

    vector<int> res = s.treeQueries(pRootNode, queries);
    for (int& i: res)
        std::cout << i << ' ';
    return 0;
}
