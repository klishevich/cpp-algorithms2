#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <limits.h>
#include <algorithm>

using namespace std;
string input();

void print_vec(string title, const vector<vector<long>>& v) {
    cout << title << endl;
    for (auto vv:v) {
        for (auto vvv:vv) cout << vvv << " ";
        cout << endl;
    }
}

bool is_odd(int n) { return (n % 2 != 0); }

// min, max
vector<vector<long>> get_seeds(string& str) {
    vector<vector<long>> res;
    vector<long> r_cur;
    stringstream ss(str);
    string s;
    int idx = 0;
    while (getline(ss, s, ' ')) {
        if (idx > 0) {
            if (is_odd(idx)) {
                r_cur.clear();
                r_cur.push_back(stol(s));
            } else {
                r_cur.push_back(r_cur[0] + stol(s) - 1);
                res.push_back(r_cur);
            }
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
    while (getline(ss, s, ' ')) tmp.push_back(stol(s));
    if (tmp.size() != 3) throw invalid_argument("tmp.size() != 3");
    vector<long> res {tmp[1], tmp[1] + tmp[2] - 1, tmp[0] - tmp[1]};
    return res;
}
 
void process_rule_for_interval(const vector<long>& rule, const vector<long>& interv,
    vector<vector<long>>& processed, vector<vector<long>>& rest) {
    long min1 = rule[0];
    long max1 = rule[1];
    long offset1 = rule[2];
    long intersec_min = max(min1, interv[0]);
    long intersec_max = min(max1, interv[1]);
    if (intersec_min <= intersec_max) {
        vector<long> new_interv { intersec_min + offset1, intersec_max + offset1};
        processed.push_back(new_interv);
        if (interv[0] < intersec_min) {
            vector<long> new_interv_left = { interv[0], intersec_min - 1};
            rest.push_back(new_interv_left);
        }
        if (intersec_max < interv[1]) {
            vector<long> new_interv_right = { intersec_max + 1, interv[1]};
            rest.push_back(new_interv_right);
        }
    } else {
        rest.push_back(interv);
    }
}

vector<vector<long>> process_map(const vector<vector<long>>& m, const vector<vector<long>>& intervs) {
    vector<vector<long>> rest = intervs;
    vector<vector<long>> processed;

    vector<vector<long>> res;
    for (vector<long> rule : m) {
        vector<vector<long>> new_rest;
        for (vector<long> interv : rest) {
            process_rule_for_interval(rule, interv, processed, new_rest);
        }
        rest = new_rest;
    }
    rest.insert(rest.end(), processed.begin(), processed.end());
    return rest;
}

int main()
{
    long res = LONG_MAX;
    vector<vector<long>> seeds;
    vector<vector<vector<long>>> all_maps;
    vector<vector<long>> cur_map;
    int cur_map_idx = 0;
    string str;
    int line_idx = 0;
    for (stringstream file(input()); getline(file, str);) {
        if (line_idx == 0) {
            seeds = get_seeds(str);
        } else {
            bool is_new_map_start = str == "";
            if (is_new_map_start) {
                if (cur_map.size() > 0) all_maps.push_back(cur_map);
                cur_map.clear();
                cur_map_idx = 0;
            } else {
                if (cur_map_idx > 0) {
                    vector<long> cur_rule = get_map_rule(str);
                    cur_map.push_back(cur_rule);
                }
                cur_map_idx++;
            }
        }
        line_idx++;
    }

    vector<vector<long>> r = seeds;
    print_vec("r", r);
    for (vector<vector<long>>& cm : all_maps) {
        print_vec("cm", cm);
        r = process_map(cm, r);
    }
    for (vector<long> rr : r) {
        cout << "min " << rr[0] << " max " << rr[1] << endl;
        if (rr[0] < res) {
            res = rr[0];
        }
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