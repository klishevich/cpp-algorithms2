// https://leetcode.com/problems/height-of-binary-tree-after-subtree-removal-queries/description
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct TreeCacheNode {
    int height = -1;
    int level;
    int result = -1;
    TreeCacheNode(int h, int l) : height(h), level(l) {}
    TreeCacheNode() {}
};

typedef unordered_map<int, TreeCacheNode> type_cache;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
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
                pCurNode->left = new TreeNode(leftVal, nullptr, nullptr);
                fillTreeNode(input, leftPos, pCurNode->left);
            }
        }
        int rightPos = 2 * pos + 2;
        if (rightPos < size) {
            int rightVal = input[rightPos];
            if (rightVal > 0) {
                pCurNode->right = new TreeNode(rightVal, nullptr, nullptr);
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

    /////////////////// for leetcode //////////////////

    static TreeCacheNode calcTreeCache(const TreeNode* pT, type_cache& cache, int level) {
        if (pT == nullptr || pT->val == 0) return TreeCacheNode();

        TreeCacheNode leftCache = calcTreeCache(pT -> left, cache, level + 1);
        TreeCacheNode rightCache = calcTreeCache(pT -> right, cache, level + 1);

        int curHeight = max(leftCache.height, rightCache.height) + 1;
        TreeCacheNode curCache = TreeCacheNode(curHeight, level);
        cache[pT->val] = curCache;

        return curCache;
    }

    static void preCalcResults(const TreeNode* pT, type_cache& cache, int alternativeHeight, int shortBranch) {
        if (pT == nullptr || pT->val == 0) return;

        TreeCacheNode* pCurCache = &cache[pT->val];
        // cout << pT->val << ": " << "altH " << alternativeHeight << endl;
        pCurCache -> result = alternativeHeight;

        if (shortBranch) {
            preCalcResults(pT->left, cache, alternativeHeight, true);
            preCalcResults(pT->right, cache, alternativeHeight, true);
            return;
        }

        int curHeight = pCurCache->height + pCurCache->level;
        TreeNode* pLeft = pT -> left;
        int leftHeight = pLeft != nullptr ? cache[pLeft->val].height : -1;
        TreeNode* pRight = pT -> right;
        int rightHeight = pRight != nullptr ? cache[pRight->val].height : -1;
        // cout << " leftHeight " << leftHeight << " rightHeight " << rightHeight << endl;
        if (leftHeight==rightHeight) {
            preCalcResults(pLeft, cache, curHeight, true);
            preCalcResults(pRight, cache, curHeight, true);
            return;
        }

        TreeNode* pMaxElement = leftHeight > rightHeight ? pLeft : pRight;
        TreeNode* pMinElement = leftHeight > rightHeight ? pRight : pLeft;
        // cout << " cur height " << curHeight << endl;
        preCalcResults(pMinElement, cache, curHeight, true);
        int anotherAlternativeHeight = pMinElement == nullptr ? pCurCache->level : cache[pMinElement->val].height + cache[pMinElement->val].level;
        // cout << " another alternative " << anotherAlternativeHeight << endl;
        preCalcResults(pMaxElement, cache, max(alternativeHeight, anotherAlternativeHeight), false);
    }

    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        type_cache cache;
        Solution::calcTreeCache(root, cache, 0);
        Solution::preCalcResults(root, cache, 0, false);

        vector<int> res;
        for (int i: queries)
            res.push_back(cache[i].result);
        return res;
    }
};

int main()
{
    Solution s;

    // vector<int> input = { 1,3,4,2,0,6,5,0,0,0, 0, 0, 0, 0, 7 };
    vector<int> input = { 5,8,9,2,1,3,7,4,6,0,0,0,0,0,0 };
    // vector<int> input = { 1,0,5,0,0,3,0,0,0,0,0,2,4,0,0 };
    // vector<int> input = {2,1,4,0,0,3,0};

    // vector<int> queries = { 4 };
    vector<int> queries = { 3, 2, 4, 8 }; // 3 2 3 2
    // vector<int> queries = {3,5,4,2,4}; // 1 0 3 3 3
    // vector<int> queries = {1, 4, 3, 4}; // 2 1 1 1
    
    TreeNode* pRootNode = new TreeNode(input[0], nullptr, nullptr);
    Solution::fillTreeNode(input, 0, pRootNode);
    cout << "---tree--" << endl;
    Solution::outputTree(pRootNode, 's', 0);

    vector<int> res = s.treeQueries(pRootNode, queries);
   
    vector<int> result = s.treeQueries(pRootNode, queries);

    cout << "---result---" << endl;
    for (int r: result)
        std::cout << r << endl;
    return 0;
}
