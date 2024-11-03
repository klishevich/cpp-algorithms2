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

    static TreeCacheNode calcTreeCache(const TreeNode* pT, type_cache& cache, int level) {
        if (pT == nullptr) return TreeCacheNode();

        int curVal = pT->val;
        if (curVal == 0) return TreeCacheNode();

        TreeCacheNode leftCache = calcTreeCache(pT -> left, cache, level + 1);
        TreeCacheNode rightCache = calcTreeCache(pT -> right, cache, level + 1);

        int curHeight = max(leftCache.height, rightCache.height) + 1;
        TreeCacheNode curCache = TreeCacheNode(curHeight, level);
        cache[curVal] = curCache;

        return curCache;
    }

    static void preCalcResults(const TreeNode* pT, type_cache& cache, int alternativeHeight, int shortBranch) {
        if (pT == nullptr) return;

        int curVal = pT -> val;
        if (curVal == 0) return;

        TreeCacheNode* pCurCache = &cache[curVal];
        cout << curVal << ": " << "altH " << alternativeHeight << endl; 
        pCurCache -> result = alternativeHeight;

        if (shortBranch) {
            preCalcResults(pT->left, cache, alternativeHeight, true);
            preCalcResults(pT->right, cache, alternativeHeight, true);
            return;
        }

        int curHeight = pCurCache -> height + pCurCache -> level;
        TreeNode* pLeft = pT -> left;
        int leftHeight = pLeft != nullptr ? cache[pLeft->val].height : 0;
        TreeNode* pRight = pT -> right;
        int rightHeight = pRight != nullptr ? cache[pRight->val].height : 0;
        if (leftHeight==rightHeight) {
            preCalcResults(pLeft, cache, curHeight, true);
            preCalcResults(pRight, cache, curHeight, true);
            return;
        }

        TreeNode* pMaxElement = nullptr;
        TreeNode* pMinElement = nullptr;
        if (leftHeight>rightHeight) {
            pMaxElement = pLeft;
            pMinElement = pRight;
        } else if (rightHeight>leftHeight) {
            pMaxElement = pRight;
            pMinElement = pLeft;
        }
        preCalcResults(pMinElement, cache, curHeight, true);
        int alternativeHeight2 = cache[pMinElement->val].height + cache[pMinElement->val].level;
        preCalcResults(pMaxElement, cache, max(alternativeHeight, alternativeHeight2), false);
    }
};

int main()
{
    Solution s;

    // vector<int> input{ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
    // vector<int> input = { 1,3,4,2,0,6,5,0,0,0, 0, 0, 0, 0, 7 };
    vector<int> input = { 5,8,9,2,1,3,7,4,6,0,0,0,0,0,0 };
    
    TreeNode* pRootNode = new TreeNode(input[0]);
    Solution::fillTreeNode(input, 0, pRootNode);
    cout << "---tree--" << endl;
    Solution::outputTree(pRootNode, 's', 0);
    type_cache cache;
    Solution::calcTreeCache(pRootNode, cache, 0);
    cout << "---cache---" << endl;
    for (auto x : cache)
        cout << x.first << ": " << x.second.level << " " << x.second.height << " " << endl;
    cout << "---calc results---" << endl;
    Solution::preCalcResults(pRootNode, cache, 0, false);

    // vector<int> queries = { 4 };
    vector<int> queries = { 3, 2, 4, 8 };

    cout << "---result---" << endl;
    for (int& i: queries)
        std::cout << i << ": " << cache[i].result << endl;
    return 0;
}
