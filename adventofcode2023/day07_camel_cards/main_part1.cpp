#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;
string input();

void print_vec(string title, const vector<vector<int>>& v) {
    cout << title << endl;
    for (auto vv:v) cout << vv[0] << "(" << vv[1] << ")" << " ";
    cout << endl;
}

string create_hex_str_from_type_and_hand(char hand_type, const string& str) {
    string hex_str;
    hex_str.push_back(hand_type);
    for (int i=0; i<str.length(); i++) {
        char c = str[i];
        if (c == 'A') {
            hex_str.push_back('f');
        } else if (c == 'K') {
            hex_str.push_back('d');
        } else if (c == 'Q') {
            hex_str.push_back('c');
        } else if (c == 'J') {
            hex_str.push_back('b');
        } else if (c == 'T') {
            hex_str.push_back('a');
        } else {
            hex_str.push_back(c);
        }
    }
    return hex_str;
}

int get_type(const string& str) {
    map<char, int> m;
    
    for (int i=0; i<str.length(); i++) {
        char c = str[i];
        if (m.count(c) == 0) m.insert({c,0});
        m[c] = m[c] + 1;
    }
    vector<int> mv;
    for (const auto &r : m) mv.push_back(r.second);
    sort(mv.begin(), mv.end(), greater<int>());

    if (mv[0] == 5) {
        return '9';
    } else if (mv[0] == 4) {
        return '8';
    } else if (mv[0] == 3 && mv[1] == 2) {
        return '6';
    } else if (mv[0] == 3 && mv[1] == 1) {
        return '5';
    } else if (mv[0] == 2 && mv[1] == 2) {
        return '4';
    } else if (mv[0] == 2 && mv[1] == 1) {
        return '2';
    } else if (mv[0] == 1 && mv[1] == 1) {
        return '1';
    }
    return '0';
}

vector<int> parse_to_priority_bid(const string& str) {
    vector<int> res;
    stringstream ss(str);
    int priority;
    int idx = 0;
    string s;
    while (getline(ss, s, ' ')) {
        if (idx == 0) {
            string hex_string = create_hex_str_from_type_and_hand(get_type(s), s);
            priority = stoi(hex_string, 0, 16);
            // cout << "type " << hand_type << " s " << s << " hex " << hex_string << " priority " << priority << endl;
        }
        if (idx == 1) {
            int bid = stoi(s);
            res = {priority, bid};
        }
        idx++;
    }
    return res;
}

int main()
{
    vector<vector<int>> res;
    string str;
    for (stringstream file(input()); getline(file, str);) {
        vector<int> r = parse_to_priority_bid(str);
        res.push_back(r);
        // cout << "priority " << r[0] << " bid " << r[1] << endl;
    }
    sort(res.begin(), res.end(), [](const vector<int> &f, const vector<int> &s) { return f[0] < s[0]; });
    // print_vec("after sort", res);

    int res2 = 0;
    for (int i=0; i < res.size(); ++i) {
        res2 += (i+1) * res[i][1];
    }
    cout << "res " << res2 << endl;
    return 0;
}

string input()
{
    return R"(32T3K 765
T55J5 684
KK677 28
KTJJT 220
QQQJA 483
)";
}