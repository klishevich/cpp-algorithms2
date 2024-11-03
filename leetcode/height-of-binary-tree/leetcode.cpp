struct TreeCacheNode {
    int height = -1;
    int level;
    int result = -1;
    TreeCacheNode(int h, int l) : height(h), level(l) {}
    TreeCacheNode() {}
};

typedef unordered_map<int, TreeCacheNode> type_cache;

class Solution {
public:
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
        if (leftHeight==rightHeight) {
            preCalcResults(pLeft, cache, curHeight, true);
            preCalcResults(pRight, cache, curHeight, true);
            return;
        }

        TreeNode* pMaxElement = leftHeight > rightHeight ? pLeft : pRight;
        TreeNode* pMinElement = leftHeight > rightHeight ? pRight : pLeft;
        preCalcResults(pMinElement, cache, curHeight, true);
        int anotherAlternativeHeight = pMinElement == nullptr ? pCurCache->level : cache[pMinElement->val].height + cache[pMinElement->val].level;
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