#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;
string input();

void print_vec(string title, const vector<string>& v) {
    cout << title << endl;
    for (auto vv:v) cout << vv << " ";
    cout << endl;
}

vector<string> parse_to_key_left_right(const string& str) {
    vector<string> res;
    stringstream ss(str);
    int idx = 0;
    string s;
    while (getline(ss, s, ' ')) {
        if (idx == 0) res.push_back(s);
        if (idx == 2) res.push_back(s.substr(1,3));
        if (idx == 3) res.push_back(s.substr(0,3));
        idx++;
    }
    return res;
}

int main()
{
    string instructions;
    map<string,vector<string>> btree;
    string str;
    int line_index = 0;
    for (stringstream file(input()); getline(file, str);) {
        if (line_index == 0) {
            instructions = str;
        }
        if (line_index >= 2) {
            vector<string> r = parse_to_key_left_right(str);
            // print_vec("r", r);
            btree.insert({r[0], vector<string> {r[1], r[2]}});
        }
        line_index++;
    }
    string cur = "AAA";
    int i = 0;
    do {
        int inst_index = i % instructions.length();
        char direction = instructions[inst_index];
        cur = direction == 'L' ? btree[cur][0] : btree[cur][1];
        i++;
    } while (cur != "ZZZ");
    cout << "res " << i << endl;
    return 0;
}

string input()
{
    return R"(LLR

AAA = (BBB, BBB)
BBB = (AAA, ZZZ)
ZZZ = (ZZZ, ZZZ)
)";
}