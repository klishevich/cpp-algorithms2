// https://adventofcode.com/2024/day/4

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

string input();

string get_word(vector<string> &input, int i, int j, int iDir, int jDir) {
    int height = input.size();
    int width = input[0].size();
    string res = "";
    for (int k=0;k<4;k++) {
        int iNext = i + iDir * k;
        int jNext = j + jDir * k;
        if (iNext >= 0 && iNext < height && jNext >=0 && jNext < width) {
            res.push_back(input[iNext][jNext]);
        } else {
            break;
        }
    }
    return res;
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
            if (get_word(vec1, i, j, 1, 1) == "XMAS") res++;
            if (get_word(vec1, i, j, 1, 0) == "XMAS") res++;
            if (get_word(vec1, i, j, 1, -1) == "XMAS") res++;
            if (get_word(vec1, i, j, 0, -1) == "XMAS") res++;
            if (get_word(vec1, i, j, -1, -1) == "XMAS") res++;
            if (get_word(vec1, i, j, -1, 0) == "XMAS") res++;
            if (get_word(vec1, i, j, -1, 1) == "XMAS") res++;
            if (get_word(vec1, i, j, 0, 1) == "XMAS") res++;
        }
    }
    cout << res << endl;

    return 0;
}

string input()
{
    return R"(....XXMAS.
.SAMXMS...
...S..A...
..A.A.MS.X
XMASAMX.MM
X.....XA.A
S.S.S.S.SS
.A.A.A.A.A
..M.M.M.MM
.X.X.XMASX
    )";
}