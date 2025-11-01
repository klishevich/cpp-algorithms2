// https://adventofcode.com/2024/day/8

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stdexcept>
#include <iterator>

using namespace std;

string input1();

int main()
{
    string str;
    int res = 0;
    unordered_map<char, vector<pair<int, int>>> antennas_map;

    int i = 0;
    int j = 0;
    for (stringstream file(input1()); getline(file, str); i++) {
        for (j=0; j<str.size(); j++) {
            char cur_char = str[j];
            if (cur_char == '.') continue;
            antennas_map[cur_char].push_back(make_pair(i,j));
        }
    }
    int height = i;
    int width = j;

    cout << "antennas map size " << antennas_map.size() << endl;

    vector<vector<bool>> visited_vec(height, vector<bool> (width, false));

    for (auto const &a_kv : antennas_map) {
        size_t size = a_kv.second.size();
        cout << "row " << a_kv.first << " size " << size << endl;
        for (int i=0; i< size; i++) {
            pair<int,int> from = a_kv.second[i];
            for (int j=i+1;j<size;j++) {
                pair<int,int> to = a_kv.second[j];
                int iDiff = to.first - from.first;
                int jDiff = to.second - from.second;
                int iCur = from.first;
                int jCur = from.second;
                while (iCur >=0 && jCur >= 0 && iCur < height && jCur < width) {
                    visited_vec[iCur][jCur] = true;
                    iCur -= iDiff;
                    jCur -= jDiff;
                }
                iCur = from.first;
                jCur = from.second;
                while (iCur >=0 && jCur >= 0 && iCur < height && jCur < width) {
                    visited_vec[iCur][jCur] = true;
                    iCur += iDiff;
                    jCur += jDiff;
                }
            }
        }
    }

    for (auto const &a: visited_vec)
        for (auto const &b: a) if (b) res++;
    

    cout << " res " << res << endl;

    return 0;
}

string input1()
{
    return R"(............
........0...
.....0......
.......0....
....0.......
......A.....
............
............
........A...
.........A..
............
............
)";
}
