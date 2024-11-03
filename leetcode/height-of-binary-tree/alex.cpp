class Solution {
public: 
	vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
		unordered_map<TreeNode*, int> hei;
		function<int(TreeNode*)> fill = [&](auto me) -> int {
			return hei[me] = me ? 1 + max(fill(me->left), fill(me->right)) : 0;
		};
		fill(root);

		unordered_map<int, int> res;
		function<void(TreeNode*, int, int)> dfs = [&](auto me, int res_wo_me, int lvl) {
			if (me) {
				res[me->val] = res_wo_me;
				dfs(me->left, max(res_wo_me, lvl + hei[me->right]), lvl + 1);
				dfs(me->right, max(res_wo_me, lvl + hei[me->right]), lvl + 1);
			}
		}
		dfs(root, 0, 0);

		for (int& x : queries) x = res[x];
		return queries;
	}
};