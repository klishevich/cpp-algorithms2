// Advent of code 2022 day 9 https://adventofcode.com/2022/day/9

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <set>

using namespace std;
string input();
void rope_simulation(vector<string>& lines, int num_knots);

int main()
{
    string str;
    vector<string> lines;
    for (stringstream file(input()); getline(file, str);) {
        lines.push_back(str);
    }
    rope_simulation(lines, 10);
}

void rope_simulation(vector<string> &lines, int num_knots) {
    vector<tuple<int, int>> knots(num_knots, make_tuple(0,0));
    set<tuple<int, int>> visited;

    for (auto &line : lines) {
        size_t pos = line.find(' ');
        string dir = line.substr(0, pos);
        int cnt = stoi(line.substr(pos + 1));

        for (int i = 0; i < cnt; ++i) {
            switch (dir[0])
            {
            case 'L':
                get<0>(knots[0]) -= 1;
                break;
            case 'R':
                get<0>(knots[0]) += 1;
                break;
            case 'U':
                get<1>(knots[0]) += 1;
                break;
            case 'D':
                get<1>(knots[0]) -= 1;
                break;
            default:
                break;
            }

            for (int k = 1; k < num_knots; ++k) {
                if (abs(get<0>(knots[k - 1]) - get<0>(knots[k])) >= 2 || abs(get<1>(knots[k-1]) - get<1>(knots[k])) >= 2) {
                    get<0>(knots[k]) += (get<0>(knots[k - 1]) - get<0>(knots[k]) > 0)  - (get<0>(knots[k - 1]) - get<0>(knots[k]) < 0);
                    get<1>(knots[k]) += (get<1>(knots[k - 1]) - get<1>(knots[k]) > 0) - (get<1>(knots[k - 1]) - get<1>(knots[k]) < 0);
                }
            }

            visited.insert(knots[num_knots - 1]);
        }
    }

    cout << "Total visited: " << visited.size();
}

string input() {
    return R"(R 5
U 8
L 8
D 3
R 17
D 10
L 25
U 20
)";
}