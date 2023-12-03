#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

string input();

bool is_number(char c) {
    return c >='0' && c <= '9';
}

bool is_dot(char c) {
    return c == '.';
}

bool has_adjacent_symbol(vector<string>& m, int rows, int cols, int i, int j) {
    for (int i1=-1; i1<=1; ++i1) {
        for (int j1=-1; j1<=1; ++j1) {
            int i_new = i + i1;
            int j_new = j + j1;
            if (i_new == i && j_new == j) continue;
            if (i_new >= 0 && i_new < rows && j_new >=0 && j_new < cols) {
                char cur_symbol = m[i_new][j_new];
                if (!is_number(cur_symbol) && !is_dot(cur_symbol))
                    return true;
            }
        }
    }
    return false;
}

int main()
{
    // bool is_number = [](char c) { return c >='0' && c <= '9'; };
    // bool is_dot = [](char c) { return c == '.'; };

    int ROWS;
    int COLS;
    vector<string> matrix;
    string str;

    for (stringstream file(input()); getline(file, str);)
    {
        COLS = str.length();
        matrix.push_back(str);
    }
    ROWS = matrix.size();

    int res = 0;
    for (int i=0; i<ROWS; ++i) {
        int start_num = -1;
        bool has_symbol = false;
        string cur_str = matrix[i];
        for (int j=0; j<COLS; ++j) {
            if (is_number(cur_str[j])) {
                bool is_start_num = start_num == -1;
                if (is_start_num) start_num = j;
                if (!has_symbol && has_adjacent_symbol(matrix, ROWS, COLS, i, j)) {
                    has_symbol = true;
                }
            } else {
                bool is_end_num = start_num != -1;
                if (is_end_num) {
                    if (has_symbol) {
                        string num_str = cur_str.substr(start_num, j - start_num);
                        res += stoi(num_str);
                    }
                    start_num = -1;
                    has_symbol = false;
                }
            }
        }
        bool is_end_num = start_num != -1;
        if (is_end_num && has_symbol) {
            string num_str = cur_str.substr(start_num);
            res += stoi(num_str);
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