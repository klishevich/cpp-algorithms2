// https://adventofcode.com/2024/day/4

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stdexcept>

using namespace std;

string input1();

int main()
{
    string str;
    vector<string> map_matrix;
    int row = 0;
    for (stringstream file(input1()); getline(file, str);)
    {
        map_matrix.push_back(str);
        row++;
    }

    size_t height = map_matrix.size();
    size_t width = map_matrix[0].size();
    
    int p_i, p_j;
    pair<int,int> p_k;
    vector<char> guard_chars {'^','>','v','<'}; // directions 0, 1, 2, 3
    auto get_pair_for_char = [](char c) {
        switch (c)
        {
            case '^':
                return make_pair(-1,0);
            case '>':
                return make_pair(0,1);
            case 'v':
                return make_pair(1,0);
            case '<':
                return make_pair(0,-1);
        }
    };

    for (int i = 0; i<height; ++i) {
        const string& line = map_matrix[i];
        for (int j = 0; j<width; ++j) {
            const char& line_char = line[j];
            for (int k =0; k<guard_chars.size(); ++k) {
                if (line_char == guard_chars[k]) {
                    p_i = i;
                    p_j = j;
                    p_k = get_pair_for_char(line_char);
                };
            }
        }
    }
    // cout << "p_i " << p_i << " p_j " << p_j << endl;

    // cout << "width " << width << " height " << height << endl;

    vector<vector<bool>> visited(height, vector<bool> (width, false));
    auto is_in_bounds = [&height, &width](int i, int j) {
        return i >= 0 && i < height && j >=0 && j < width;
    };
    auto get_traverse_vector = [](pair<int,int> k) {
        if (k == make_pair(-1,0)) {
            vector<pair<int,int>> traverse { make_pair(-1,0), make_pair(0,1), make_pair(1,0), make_pair(0,-1) };
            return traverse;
        } else if ( k==make_pair(0,1)) {
            vector<pair<int,int>> traverse { make_pair(0,1), make_pair(1,0), make_pair(0,-1), make_pair(-1,0) };
            return traverse;
        } else if ( k==make_pair(1,0)) {
            vector<pair<int,int>> traverse { make_pair(1,0), make_pair(0,-1), make_pair(-1,0), make_pair(0,1) };
            return traverse;
        } else if ( k==make_pair(0,-1)) {
            vector<pair<int,int>> traverse { make_pair(0,-1), make_pair(-1,0), make_pair(0,1), make_pair(1,0) };
            return traverse;
        } else {
            throw std::invalid_argument("get_traverse_vector");
        }
    };

    int res = 0;

    // cout << "Testing0" <<endl;

    while (is_in_bounds(p_i, p_j)) {
        // cout << "Testing1" <<endl;
        // cout << "p_i " << p_i << " p_j " << p_j << endl;
        visited[p_i][p_j] = true;
        vector<pair<int,int>> traverse = get_traverse_vector(p_k);
        for (int i = 0; i<traverse.size(); ++i) {
            pair<int,int> p = traverse[i];
            int new_i = p_i + p.first;
            int new_j = p_j + p.second;
            // cout << "new_i " << new_i << " new_j " << new_j << endl;
            if (!is_in_bounds(new_i, new_j) || map_matrix[new_i][new_j] != '#') {
                p_i = new_i;
                p_j = new_j;
                p_k = p;
                break;
            }
        }
        // cout << "Testing2" <<endl;
    }

    // cout << "Testing3" <<endl;

    for (auto const &vec : visited)
        for (auto const &el : vec) if (el) res++;

    cout << "The end " << res << endl;

    return 0;
}

string input1()
{
    return R"(....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
........#.
#.........
......#...
)";
}
