// Day 9: Smoke Basin - https://adventofcode.com/2021/day/9
#include <iostream>
#include <queue>
#include <sstream>
using namespace std;

string input();

int main() {
    string line;
    vector<string> area;
    for (stringstream file(input()); getline(file, line);)
        area.push_back(line);

    priority_queue<int> top3;
    size_t m = size(area), n = size(area[0]), res = 1;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j) {
            // iterative DFS
            int basin = 0;
            vector<pair<int, int>> stack{ {i, j} };
            while (size(stack)) {
                auto [r, c] = stack.back();
                stack.pop_back();
                if (r < 0 || c < 0 || r == m || c == n) continue;
                if (exchange(area[r][c], '9') == '9') continue;
                ++basin;
                stack.insert(end(stack), { {r + 1,c}, {r - 1,c}, {r,c + 1}, {r,c - 1} });
            }

            // maintain 3 largest basins
            if (basin) top3.push(-basin);
            if (top3.size() > 3) top3.pop();
        }

    // product of 3 largest basins
    for (; top3.size(); top3.pop())
        res *= -top3.top();
    cout << "Part 2: " << res << endl;
}

string input() {
    return R"(2199943210
3987894921
9856789892
8767896789
9899965678
)";
}
