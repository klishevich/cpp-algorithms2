// https://adventofcode.com/2024/day/4

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

string input();

bool is_xmas(vector<string> &input, int i, int j) {
    int height = input.size();
    int width = input[0].size();
    if (input[i][j]!='A') return false;
    int diff = abs('S' - 'M');
    // cout << " diff " << diff << endl;
    if (i>0 && i<height-1 && j>0 && j<width-1) {
        if (abs(input[i-1][j-1] - input[i+1][j+1]) == diff && abs(input[i-1][j+1]-input[i+1][j-1]) == diff) return true; 
    }
    return false;
}

int main()
{
    string str;
    vector<string> vec1;
    for (stringstream file(input()); getline(file, str);)
    {
        vec1.push_back(str);
    }

    int res = 0;
    for (int i=0;i<vec1.size();i++) {
        string s = vec1[i];
        for (int j=0;j<s.size();j++) {
            if (is_xmas(vec1, i, j)) res++;
        }
    }
    cout << res << endl;

    return 0;
}

string input()
{
    return R"(MMMSXXMASM
MSAMXMSMSA
AMXSXMAAMM
MSAMASMSMX
XMASAMXAMM
XXAMMXXAMA
SMSMSASXSS
SAXAMASAAA
MAMMMXMMMM
MXMXAXMASX
    )";
}