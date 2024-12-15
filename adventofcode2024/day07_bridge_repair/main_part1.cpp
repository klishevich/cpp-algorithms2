// https://adventofcode.com/2024/day/7

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

vector<long long> split(const string& s, const string& delimiter) {
    vector<long long> tokens;
    size_t start_pos = 0;
    size_t pos = 0;
    string token;
    do {
        pos = s.find(delimiter, start_pos);
        token = start_pos == 0 ? s.substr(start_pos, pos - start_pos - 1) : s.substr(start_pos, pos - start_pos);
        // cout << token << endl;
        tokens.push_back(stoll(token));
        start_pos = pos + delimiter.size();
    } 
    while (pos != string::npos);

    return tokens;
}

void all_combinations(const int &total_depth, const int cur_depth, const string cur_str, vector<string> &res_out) {
    if (cur_depth == total_depth) {
        res_out.push_back(cur_str);
        return;
    }
    all_combinations(total_depth, cur_depth + 1, cur_str + "0", res_out);
    all_combinations(total_depth, cur_depth + 1, cur_str + "1", res_out);
}

int main()
{
    string str;
    long long res = 0;
    vector<vector<int>> data;
    for (stringstream file(input1()); getline(file, str);) {
        // string::difference_type n = count(str.begin(), str.end(), ' ');
        vector<long long> data_line = split(str, " ");
        vector<string> combinations;
        all_combinations(data_line.size()-2, 0, "", combinations);
        for (int i=0;i<combinations.size();i++) {
            string cur_combi = combinations[i];
            
            long long operation_res = 0;
            vector<long long> for_plus_vec;
            long long last_val = data_line[1];
            for (int j=0;j<cur_combi.size();j++) {
                long long cur_val = data_line[2+j];
                bool is_multipy = cur_combi[j] == '0'; // '0' multipy, '1' add
                last_val = is_multipy ? last_val * cur_val : last_val + cur_val;
                // if (!is_multipy){
                //     for_plus_vec.push_back(last_val);
                //     last_val = cur_val;
                // } else {
                //     last_val = last_val * cur_val;
                // }
            }
            // for_plus_vec.push_back(last_val);

            operation_res = last_val;
            // for (const auto& p : for_plus_vec) operation_res += p;
            if (operation_res == data_line[0]) {
                res += operation_res;
                break;
            }
        }

    }

    cout << " max_numbers " << " res " << res << endl;

    return 0;
}

string input1()
{
    return R"(190: 10 19
3267: 81 40 27
83: 17 5
156: 15 6
7290: 6 8 6 15
161011: 16 10 13
192: 17 8 14
21037: 9 7 18 13
292: 11 6 16 20
)";
}
