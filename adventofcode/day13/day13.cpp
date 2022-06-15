// Day 13: Transparent Origami - https://adventofcode.com/2021/day/11

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

string input();

int main() {
    string str;
    set<pair<int, int>> points;
    stringstream file(input());
    while (getline(file, str) && size(str)) {
        auto pos = str.find(',');
        auto x = stoi(str.substr(0, pos)), y = stoi(str.substr(pos + 1));
        points.insert({ x, y });
    }
    while (getline(file, str)) {
        auto pos = str.find('=');
        int axis = str[pos - 1], fold = stoi(str.substr(pos + 1));
        auto ttt = exchange(points, {});
        for (auto [x, y] : ttt) {
            int& z = axis == 'x' ? x : y;
            z = z > fold ? 2 * fold - z : z;
            points.insert({ x, y });
        }
        cout << "Count: " << size(points) << endl;
    }
    int X = 0, Y = 0;
    for (auto [x, y] : points)
        X = max(x, X), Y = max(y, Y);
    vector<string> lines(Y + 1, string(X + 1, ' '));
    for (auto [x, y] : points)
        lines[y][x] = 219;
    for (auto line : lines)
        cout << line << endl;
}

string input() {
    return R"(6,10
0,14
9,10
0,3
10,4
4,11
6,0
6,12
4,1
0,13
10,12
3,4
3,0
8,4
1,10
2,14
8,10
9,0

fold along y=7
fold along x=5
)";
}