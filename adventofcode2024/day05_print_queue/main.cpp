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
string input2();

vector<int> split(const string& s, const string& delimiter) {
    vector<int> tokens;
    size_t start_pos = 0;
    size_t pos = 0;
    string token;
    do {
        pos = s.find(delimiter, start_pos);
        token = s.substr(start_pos, pos - start_pos);
        tokens.push_back(stoi(token));
        start_pos = pos + delimiter.size();
    } 
    while (pos != string::npos);

    return tokens;
}

int validate2(const vector<pair<int,int>>& rules, vector<int>& numbers) {
    bool res = true;
    vector<pair<int,int>> subRules;
    for (int i=0; i<rules.size(); ++i) {
        pair<int,int> rule = rules[i];
        int firstIndex = -1;
        int secondIndex = -1;
        for (int j=0;j<numbers.size();++j){
            int number = numbers[j];
            if (number == rule.first) firstIndex = j;
            if (number == rule.second) secondIndex = j;
        }
        if (firstIndex >= 0 && secondIndex >=0) {
            subRules.push_back(rule);
            if (firstIndex > secondIndex) res = false;
        }
    }
    if (res == false) {
        unordered_map<int,int> occurenceMap; 
        cout << "-- numbers --" << endl;
        for (int k : numbers) {
            cout << k << " ";
        }
        cout << endl;
        for (int k=0;k<subRules.size();++k) {
            pair<int,int> sr = subRules[k];
            occurenceMap[sr.first] = occurenceMap[sr.first] - 1;
            occurenceMap[sr.second] = occurenceMap[sr.second] + 1;
            // cout << sr.first << " " << sr.second << endl;
        }
        for (auto const& el : occurenceMap) {
            // cout << el.first << " " << el.second << endl;
            if (el.second == 0) {
                return el.first;
            }
        }
        throw std::invalid_argument("el.second == 0 not found");
    }
    return 0;
}

int main()
{
    string str;
    vector<pair<int,int>> rulesVec;
    for (stringstream file(input1()); getline(file, str);)
    {
        size_t pos = str.find('|');
        if (pos == string::npos) continue;
        int first = stoi(str.substr(0, pos));
        int second = stoi(str.substr(pos + 1));
        rulesVec.push_back(make_pair(first,second));
    }

    int res = 0;
    for (stringstream file(input2()); getline(file, str);)
    {
        vector<int> numbers = split(str, ",");
        res += validate2(rulesVec, numbers);
    }
    cout << res << endl;


    return 0;
}

string input1()
{
    return R"(47|53
97|13
97|61
97|47
75|29
61|13
75|53
29|13
97|29
53|29
61|53
97|53
61|29
47|13
75|47
97|75
47|61
75|61
47|29
75|13
53|13
    )";
}

string input2()
{
    return R"(75,47,61,53,29
97,61,53,29,13
75,29,13
75,97,47,61,53
61,13,29
97,13,75,29,47
)";
}