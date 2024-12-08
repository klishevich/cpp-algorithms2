// https://adventofcode.com/2024/day/4

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

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
        cout << token << " ";
        tokens.push_back(stoi(token));
        start_pos = pos + delimiter.size();
    } 
    while (pos != string::npos);
    cout << endl;

    return tokens;
}

bool validate(const vector<pair<int,int>>& rules, vector<int>& numbers) {
    for (int i=0; i<rules.size(); ++i) {
        pair<int,int> rule = rules[i];
        int firstIndex = -1;
        int secondIndex = -1;
        for (int j=0;j<numbers.size();j++){
            int number = numbers[j];
            if (number == rule.first) firstIndex = j;
            if (number == rule.second) secondIndex = j;
        }
        if (firstIndex >= 0 && secondIndex >=0 && firstIndex > secondIndex) return false;
    }
    return true;
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
        if (validate(rulesVec, numbers)) {
            res += numbers[numbers.size() / 2];
        }
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