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
    static void insertVertex(vector<int>& input, int vertexPosition, TreeNode& currentNode) {
        // if (vertexPosition >= input.size()) return;
        // if (vertexPosition == 0) {

        //     currentNode.left = 
        // }

        // for (int i=0; i<input.size(); ++i)
        // {
        //     int iPosition = i + 1;
        //     std::cout << std::bitset<16>(iPosition) << '\n';
        // }
        // TreeNode tn;
        // return tn;
        // return currentNode;
    }

    static void fillTreeNode(vector<int>& input, int pos, TreeNode* pCurNode) {
        int size = input.size();
        int leftPos = 2 * pos + 1;
        int rightPos = 2 * pos + 2;
        if (leftPos < size) {
            int leftVal = input[leftPos];
            if (leftVal > 0) {
                TreeNode *pLeftNode = new TreeNode(leftVal);
                pCurNode->left = pLeftNode;
                fillTreeNode(input, leftPos, pLeftNode);
            }
        }
        if (rightPos < size) {
            int rightVal = input[rightPos];
            if (rightVal) {
                TreeNode *pRightNode = new TreeNode(rightVal);
                pCurNode->right = pRightNode;
                fillTreeNode(input, rightPos, pRightNode);
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
    TreeNode tn(input[0]);
    Solution::fillTreeNode(input, 0, &tn);
    Solution::outputTree(&tn, 's', 0);

    vector<int> queries = { 4 };

    vector<int> res = s.treeQueries(&tn, queries);

    cout << "res: " << "TODO" << endl;
    return 0;
}
