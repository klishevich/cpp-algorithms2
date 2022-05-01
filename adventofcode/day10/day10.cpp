// Day 10: Syntax Scoring - https://adventofcode.com/2021/day/10

#include <algorithm>
#include <iostream>
#include <ranges>
#include <stack>
#include <sstream>
using namespace std;

string input();

int main() {
    string chars = "<{[( )]}>", line;
    auto ch2pos = [&](char ch) { return (int)chars.find(ch) - 4; };
    int sc[]{ 0, 3, 57, 1197, 25137 }, res1 = 0;
    deque<long long> res2;
    for (stringstream file(input()); getline(file, line);) {
        stack<int> st;
        for (int pos : line | views::transform(ch2pos))
            if (pos < 0) st.push(-pos);
            else if (st.top() == pos) st.pop();
            else {
                res1 += sc[pos];
                st = {};
                break;
            }
        if (size(st)) res2.push_back(0);
        for (; size(st); st.pop())
            res2.back() = 5 * res2.back() + st.top();
    }
    cout << "Part 1: " << res1 << endl;
    nth_element(begin(res2), begin(res2) + size(res2) / 2, end(res2));
    cout << "Part 2: " << res2[size(res2) / 2] << endl;
}

string input() {
    return R"(
[({(<(())[]>[[{[]{<()<>>
[(()[<>])]({[<{<<[]>>(
{([(<{}[<>[]}>{[]{[(<()>
(((({<>}<{<{<>}{[]{[]{}
[[<[([]))<([[{}[[()]]]
[{[{({}]{}}([{[{{{}}([]
{<[[]]>}<{[{[{[]{()[[[]
[<(<(<(<{}))><([]([]()
<{([([[(<>()){}]>(<<{{
<{([{{}}[<[[[<>{}]]]>[]]
)";
}