// Day 15: Chiton - https://adventofcode.com/2021/day/15

#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <iostream>

using namespace std;

string input();

string up(string str, size_t inc) {
    for (char& ch : str)
        ch = '1' + (ch - '1' + inc) % 9;
    return str;
}

int main() {
    static const size_t k = 1; // set to 1 for part1
    static const int dir[]{ 1, 0, -1, 0, 1 };

    string str;
    vector<string> cave;
    for (stringstream file(input()); getline(file, str);) {
        cave.push_back(str);
        for (size_t i = 1; i < k; ++i)
            cave.back() += up(str, i);
    }
    for (size_t i = 1, R = size(cave); i < k; ++i)
        for (size_t r = 0; r < R; ++r)
            cave.push_back(up(cave[r], i));

    // Dijkstra
    size_t R = size(cave), C = size(cave[0]);
    vector<vector<int>> dst(R, vector<int>(C, INT_MAX));
    typedef tuple<int, int, int> i3;
    priority_queue<i3, vector<i3>, greater<>> pq;
    pq.push({});
    while (size(pq)) {
        auto [w, r, c] = pq.top();
        pq.pop();
        if (r < 0 || c < 0 || r == R || c == C) continue;
        if (r + c) w += cave[r][c] - '0';
        if (w >= dst[r][c]) continue;
        dst[r][c] = w;
        for (int i = 0; i < 4; ++i)
            pq.push({ w, r + dir[i], c + dir[i + 1] });
    }
    cout << dst.back().back() << endl;
}

string input() {
    return R"(1163751742
1381373672
2136511328
3694931569
7463417111
1319128137
1359912421
3125421639
1293138521
2311944581
)";
}