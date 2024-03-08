#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution
{
public:
    int minFallingPathSum(vector<vector<int>> &matrix)
    {
        size_t s = matrix.size();
        vector<int> min_paths_sum(s);
        vector<int> min_paths_sum_prev(s);
        for (int i = 0; i < s; i++)
        {
            min_paths_sum_prev = min_paths_sum;
            for (int j = 0; j < s; j++)
            {
                if (i == 0)
                    min_paths_sum[j] = matrix[0][j];
                else
                {
                    int min_j = j;
                    int min_path = min_paths_sum_prev[j];
                    if (j - 1 >= 0 && min_paths_sum_prev[j - 1] < min_path)
                        min_path = min_paths_sum_prev[j - 1];
                    if (j + 1 < s && min_paths_sum_prev[j + 1] < min_path)
                        min_path = min_paths_sum_prev[j + 1];
                    min_paths_sum[j] = min_path + matrix[i][j];
                }
            }
            cout << "step " << i << " " << endl;
            for (const auto &val : min_paths_sum)
                std::cout << val << ' ';
            cout << endl;
        }
        int res = INT_MAX;
        for (int i = 0; i < s; i++)
        {
            if (min_paths_sum[i] < res)
                res = min_paths_sum[i];
        }
        return res;
    }
};

int main()
{
    Solution *s = new Solution();

    vector<vector<int>> vec{{2, 1, 3}, 
                            {6, 5, 4},
                            {7, 8, 9}};
    int res = s->minFallingPathSum(vec); // 13

    // vector<vector<int>> vec{{-19, 57},
    //                         {-40, -5}};
    // int res = s->minFallingPathSum(vec); // -59

    // vector<vector<int>> vec{{8, 93, 21},
    //                         {18, -11, 19},
    //                         {-23, 15, -42}};
    // int res = s->minFallingPathSum(vec); // -45

    cout << "res: " << res << endl;
    return 0;
}
