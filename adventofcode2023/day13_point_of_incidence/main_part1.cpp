#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
string input();

bool is_vertical_mirror(const vector<string> &pattern, int index) {
    int rows = pattern.size();
    int cols = pattern[0].length();
    for (int i=0;i<rows;++i) {
        for (int j=0; j<=min(index,cols-index-2);++j) {
            int j1=index-j;
            int j2=index+1+j;
            if (pattern[i][j1]!=pattern[i][j2]) return false;
        }
    }
    return true;
}

int get_vertical_mirror_index(const vector<string> &pattern) {
    int cols = pattern[0].length();
    for (int j=0;j<=cols-2;++j) {
        if (is_vertical_mirror(pattern,j)) return j+1;
    }
    return 0;
}

bool is_horizontal_mirror(const vector<string> &pattern, int index) {
    int rows = pattern.size();
    int cols = pattern[0].length();
    for (int j=0;j<cols;++j) {
        for (int i=0; i<=min(index,rows-index-2);++i) {
            int i1=index-i;
            int i2=index+1+i;
            if (pattern[i1][j]!=pattern[i2][j]) return false;
        }
    }
    return true;
}

int get_horizontal_mirror_index(const vector<string> &pattern) {
    int rows = pattern.size();
    for (int i=0;i<=rows-2;++i) {
        if (is_horizontal_mirror(pattern,i)) return i+1;
    }
    return 0;
}

int main()
{
    vector<vector<string>> all_patterns;
    vector<string> one_pattern;
    string str;

    for (stringstream file(input()); getline(file, str);) {
        if (str != "") {
            one_pattern.push_back(str);
        } else {
            all_patterns.push_back(one_pattern);
            one_pattern.clear();
        }
    }
    int res = 0;
    int idx = 0;
    for (vector<string> p : all_patterns) {
        int vert = get_vertical_mirror_index(p);
        int hor = get_horizontal_mirror_index(p);
        // if (vert == 0 && hor == 0 ) cout << "!!! " << idx;
        // cout << "idx " << idx << " vert " << vert << " hor " << hor << endl;
        res += (vert + 100 * hor);
        idx++;
    }

    cout << "res " << res << endl;
    return 0;
}

string input()
{
    return R"(#.##..##.
..#.##.#.
##......#
##......#
..#.##.#.
..##..##.
#.#.##.#.

#...##..#
#....#..#
..##..###
#####.##.
#####.##.
..##..###
#....#..#

)";
}