#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>

using namespace std;

string input();

vector<pair<int,int>> get_adjacent_gears(vector<string>& m, int rows, int cols, int i, int j) {
    vector<pair<int,int>> res;
    for (int i1=-1; i1<=1; ++i1) {
        for (int j1=-1; j1<=1; ++j1) {
            int i_new = i + i1;
            int j_new = j + j1;
            if (i_new == i && j_new == j) continue;
            if (i_new >= 0 && i_new < rows && j_new >=0 && j_new < cols) {
                char cur_symbol = m[i_new][j_new];
                if (cur_symbol == '*')
                    res.push_back({i_new, j_new});
            }
        }
    }
    return res;
}

void update_gears_map(const string& num_str, const set<pair<int,int>>& adj_gears_set, map<pair<int,int>, vector<int>>& gears_map) {
    int num = stoi(num_str);
    for (pair<int,int> p : adj_gears_set) {
        if (!gears_map.count(p)) {
            gears_map.insert({p, vector<int>()});
        }
        gears_map[p].push_back(num);
    }
}

int main()
{
    // Lambda
    auto is_number = [](char c) { return c >='0' && c <= '9'; };

    vector<string> matrix;
    string str;
    map<pair<int,int>, vector<int>> gears_map;

    for (stringstream file(input()); getline(file, str);)
        matrix.push_back(str);

    int ROWS = matrix.size();
    int COLS = matrix[0].length();

    for (int i=0; i<ROWS; ++i) {
        int start_num = -1;
        set<pair<int,int>> adj_gears_set;
        string cur_str = matrix[i];
        for (int j=0; j<COLS; ++j) {
            if (is_number(cur_str[j])) {
                bool is_start_num = start_num == -1;
                if (is_start_num) start_num = j;
                vector<pair<int,int>> adj_gears = get_adjacent_gears(matrix, ROWS, COLS, i, j);
                for (pair<int,int> p : adj_gears) {
                    adj_gears_set.insert(p);
                }
            } else {
                bool is_end_num = start_num != -1;
                if (is_end_num) {
                    if (adj_gears_set.size()) {
                        string num_str = cur_str.substr(start_num, j - start_num);
                        update_gears_map(num_str, adj_gears_set, gears_map);
                    }
                    start_num = -1;
                    adj_gears_set.clear();
                }
            }
        }
        bool is_end_num = start_num != -1;
        if (is_end_num && adj_gears_set.size()) {
            string num_str = cur_str.substr(start_num);
            update_gears_map(num_str, adj_gears_set, gears_map);
        }
    }
    int res = 0;
    for (auto const& m : gears_map) {
        if (m.second.size() == 2) {
            res += m.second[0]*m.second[1];
        }
    }
    cout << "res " << res << endl;
    return 0;
}

string input()
{
    return R"(467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..
)";
}