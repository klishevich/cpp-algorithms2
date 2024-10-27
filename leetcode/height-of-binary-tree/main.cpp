// https://leetcode.com/problems/height-of-binary-tree-after-subtree-removal-queries/description
#include <iostream>
#include <sstream>
#include <vector>
#include <bitset>

using namespace std;

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

    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        vector<int> res = {1};
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

    cout << "res: " << "TODO" << endl;
    return 0;
}
