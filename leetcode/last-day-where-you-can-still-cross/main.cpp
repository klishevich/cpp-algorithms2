// https://leetcode.com/problems/last-day-where-you-can-still-cross/description/

// i indexes for rows
// j indexes for columns

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int latestDayToCross(int row, int col, vector<vector<int>> &cells)
    {
        return 0;
    }

    vector<vector<int>> fill_matrix(int row, int col, vector<vector<int>> &vec, int day)
    {
        vector<vector<int>> data = vector<vector<int>>(row, vector<int>(col, 0));
        for (int k = 0; k < day; k++)
        {
            vector<int> a = vec[k];
            data[a[0] - 1][a[1] - 1] = 1;
        }
        return data;
    }

    bool has_route(int row, int col, const vector<vector<int>> &matrix)
    {
        cout << "one " << endl;
        vector<vector<int>> stack;
        vector<vector<int>> visited = matrix;
        for (int j = 0; j < col; j++)
        {
            if (matrix[0][j] == 0)
            {
                stack.push_back(vector<int>{0, j});
                visited[0][j] = 1;
            }
        }
        if (stack.size() == 0)
            return false;
        do
        {
            cout << "two " << endl;
            vector<int> cur_element = stack.back();
            int i_cur = cur_element[0];
            int j_cur = cur_element[1];
            cout << "i_cur " << i_cur << " j_cur " << j_cur << endl;
            stack.pop_back();
            if (i_cur == row - 1)
                return true;

            int i_up = i_cur - 1;
            int i_down = i_cur + 1;
            int j_left = j_cur - 1;
            int j_right = j_cur + 1;
            if (i_up >= 0 && !visited[i_up][j_cur])
            {
                stack.push_back(vector<int>{i_up, j_cur});
                visited[i_up][j_cur] = 1;
            }
            if (i_down < row && !visited[i_down][j_cur])
            {
                stack.push_back(vector<int>{i_down, j_cur});
                visited[i_down][j_cur] = 1;
            }
            if (j_left >= 0 && !visited[i_cur][j_left])
            {
                stack.push_back(vector<int>{i_cur, j_left});
                visited[i_cur][j_left] = 1;
            }
            if (j_right < col && !visited[i_cur][j_right])
            {
                stack.push_back(vector<int>{i_cur, j_right});
                visited[i_cur][j_right] = 1;
            }
        } while (stack.size() > 0);
        cout << "ten " << endl;
        return false;
    }
};

int main()
{
    Solution *s = new Solution();

    int row = 2;
    int col = 2;
    vector<vector<int>> vec{{1, 1},
                            {2, 1},
                            {1, 2},
                            {2, 2}};

    auto matrix = s->fill_matrix(row, col, vec, 3);
    for (auto &vv : matrix)
    {
        for (int &v : vv)
            cout << v << " ";
        cout << endl;
    }


    // int res = s->latestDayToCross(2, 2, vec); // 2
    bool res = s->has_route(row, col, matrix);

    cout << "res: " << res << endl;
    return 0;
}
