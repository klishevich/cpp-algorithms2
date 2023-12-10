#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;
string input();

template <typename T>
void print_vec(string title, const vector<T>& v) {
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
    vector<string> start_nodes;
    vector<long> cycles;
    string str;
    int line_index = 0;
    for (stringstream file(input()); getline(file, str);) {
        if (line_index == 0) {
            instructions = str;
        }
        if (line_index >= 2) {
            vector<string> r = parse_to_key_left_right(str);
            // print_vec("r", r);
            string node = r[0];
            btree.insert({node, vector<string> {r[1], r[2]}});
            if (node[2] == 'A') {
                start_nodes.push_back(node);
            }
        }
        line_index++;
    }
    print_vec("start nodes", start_nodes);
    int i = 0;
    int cycles_found = 0;
    do {
        int inst_index = i % instructions.length();
        char direction = instructions[inst_index];
        for (int j=0; j<start_nodes.size(); j++) {
            string cur_node = start_nodes[j];
            string new_node = direction == 'L' ? btree[cur_node][0] : btree[cur_node][1];
            if (new_node[2] == 'Z') {
                cycles_found ++;
                cycles.push_back(i+1);
                cout << "i " << i << " j " << j << " new_node " << new_node << endl;
            }
            start_nodes[j] = new_node;
        }
        i++;
    } while (cycles_found != start_nodes.size());
    print_vec<long>("cycles", cycles);
    long res = 1;
    for (long v : cycles) res *= v;
    cout << "res " << res / 263 / 263 / 263 / 263 / 263 << endl;
    return 0;
}

string input()
{
    return R"(LR

11A = (11B, XXX)
11B = (XXX, 11Z)
11Z = (11B, XXX)
22A = (22B, XXX)
22B = (22C, 22C)
22C = (22Z, 22Z)
22Z = (22B, 22B)
XXX = (XXX, XXX)
)";
}