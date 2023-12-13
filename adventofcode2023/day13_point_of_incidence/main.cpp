#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
string input();

bool is_vertical_mirror(const vector<string> &pattern, int index, int i0, int j0) {
    int rows = pattern.size();
    int cols = pattern[0].length();
    for (int i=0;i<rows;++i) {
        for (int j=0; j<=min(index,cols-index-2);++j) {
            int j1=index-j;
            int j2=index+1+j;
            bool condition = pattern[i][j1]!=pattern[i][j2];
            // if (i0 == 5 && j0 == 8) {
            //     cout << "---- condition " << condition << endl;
            //     cout << "i " << i << " j " << j << " j1 " << j1 << " j2 " << j2 << endl;
            //     cout << "pattern[i][j1] " << pattern[i][j1] << " pattern[i][j2] " << pattern[i][j2] << endl;
            // }
            if (i==i0 && (j1==j0 || j2==j0)) condition = !condition;
            if (condition) return false;
        }
    }
    return true;
}

int get_vertical_mirror_index(const vector<string> &pattern, int i0, int j0, int exclude) {
    int cols = pattern[0].length();
    for (int j=0;j<=cols-2;++j) {
        if (j!=exclude && is_vertical_mirror(pattern,j,i0,j0)) return j+1;
    }
    return 0;
}

bool is_horizontal_mirror(const vector<string> &pattern, int index, int i0, int j0) {
    int rows = pattern.size();
    int cols = pattern[0].length();
    for (int j=0;j<cols;++j) {
        for (int i=0; i<=min(index,rows-index-2);++i) {
            int i1=index-i;
            int i2=index+1+i;
            bool condition = pattern[i1][j]!=pattern[i2][j];
            if ((i1==i0||i2==i0)&&j==j0) condition = !condition;
            if (condition) return false;
        }
    }
    return true;
}

int get_horizontal_mirror_index(const vector<string> &pattern, int i0, int j0, int exclude) {
    int rows = pattern.size();
    for (int i=0;i<=rows-2;++i) {
        if (i!=exclude && is_horizontal_mirror(pattern,i,i0,j0)) return i+1;
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
        int rows = p.size();
        int cols = p[0].length();
        int vert = 0;
        int hor = 0;
        int original_vert = get_vertical_mirror_index(p,-1,-1, -1);
        int original_hor = get_horizontal_mirror_index(p, -1,-1, -1);
        for (int i=0;i<rows;i++) {
            if (hor!=0 || vert!=0) break;
            for (int j=0;j<cols;j++) {
                int new_vert = get_vertical_mirror_index(p,i,j, original_vert-1);
                if (new_vert != 0) {
                    vert = new_vert;
                    break;
                }
                int new_hor = get_horizontal_mirror_index(p,i,j, original_hor-1);
                if (new_hor !=0) {
                    hor = new_hor;
                    break;
                }
            }
        }
        if (vert == 0 && hor == 0) {
            cout << "row " << p[0] << endl;
            cout << "orig vert " << original_vert << " orig hor " << original_hor << endl; 
            cout << "idx " << idx << " rows " << rows << " cols " << cols << " vert " << vert << " hor " << hor << endl;
        }
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