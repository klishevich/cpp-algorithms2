#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <limits.h>

using namespace std;
string input();

void print_vec(string title, vector<long>& v) {
    cout << title << endl;
    for (auto s:v) cout << s << " ";
    cout << endl;
}

vector<long> get_seeds(string& str) {
    vector<long> res;
    stringstream ss(str);
    string s;
    int idx = 0;
    while (getline(ss, s, ' ')) {
        if (idx > 0) {
            res.push_back(stol(s));
        }
        idx++;
    }
    return res;
}

// min, max, offset
vector<long> get_map_rule(string& str) {
    vector<long> tmp;
    stringstream ss(str);
    string s;
    while (getline(ss, s, ' ')) {
        tmp.push_back(stol(s));
    }
    if (tmp.size() != 3) {
        throw invalid_argument("tmp.size() != 3");
    }
    vector<long> res {tmp[1], tmp[1] + tmp[2] - 1, tmp[0] - tmp[1]};
    return res;
}

long process_map(vector<vector<long>>& m, long val) {
    for (vector<long> mm : m) {
        if (mm[0] <= val && val <= mm[1]) return val + mm[2];
    }
    return val;
}

int main()
{
    long res = LONG_MAX;
    vector<long> seeds;
    vector<vector<vector<long>>> all_maps;
    vector<vector<long>> cur_map;
    int cur_map_idx = 0;
    string str;
    int line_idx = 0;
    for (stringstream file(input()); getline(file, str);) {
        // cout << str << endl;
        if (line_idx == 0) {
            seeds = get_seeds(str);
        } else {
            bool is_new_map_start = str == "";
            if (is_new_map_start) {
                all_maps.push_back(cur_map);
                cur_map.clear();
                cur_map_idx = 0;
            } else {
                if (cur_map_idx > 0) {
                    vector<long> cur_rule = get_map_rule(str);
                    // print_vec("cur_rule", cur_rule);
                    cur_map.push_back(cur_rule);
                }
                cur_map_idx++;
            }
        }
        line_idx++;
    }

    for (long seed : seeds) {
        long r = seed;
        for (vector<vector<long>>& cm : all_maps) {
            r = process_map(cm, r);
        }
        if (r < res) res = r;
    }
    
    cout << "res " << res << endl;
    return 0;
}

string input()
{
    return R"(seeds: 79 14 55 13

seed-to-soil map:
50 98 2
52 50 48

soil-to-fertilizer map:
0 15 37
37 52 2
39 0 15

fertilizer-to-water map:
49 53 8
0 11 42
42 0 7
57 7 4

water-to-light map:
88 18 7
18 25 70

light-to-temperature map:
45 77 23
81 45 19
68 64 13

temperature-to-humidity map:
0 69 1
1 0 69

humidity-to-location map:
60 56 37
56 93 4

)";
}