#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
string input();

template <typename T>
void print_vec(string title, const vector<T>& v) {
    cout << title << endl;
    for (auto vv:v) cout << vv << " ";
    cout << endl;
}

vector<int> parse_string(const string& str) {
    vector<int> res;
    stringstream ss(str);
    string s;
    while (getline(ss, s, ' ')) res.push_back(stoi(s));
    return res;
}

int get_prediction(const vector<int>& v) {
    vector<vector<int>> pp;
    bool all_zeroes = false;
    pp.push_back(v);
    do {
        vector<int> p;
        int pp_last_idx = pp.size()-1;
        int last_p_size = pp[pp_last_idx].size();
        all_zeroes = true;
        for (int i=1;i<last_p_size;i++) {
            int diff = pp[pp_last_idx][i]-pp[pp_last_idx][i-1];
            if (diff != 0) all_zeroes = false;
            p.push_back(diff);
        }
        // print_vec("p", p);
        pp.push_back(p);
    } while (!all_zeroes);
    int res = 0;
    for (int i = pp.size()-1; i>= 0; --i) {
        int p_size = pp[i].size();
        res += pp[i][p_size-1];
    }
    return res;
}

int main()
{
    string str;
    int res = 0;
    for (stringstream file(input()); getline(file, str);) {
        // cout << str << endl;
        vector<int> r = parse_string(str);
        int p = get_prediction(r);
        // cout << "p " << p << endl;
        res += p;
    }
    cout << "res " << res << endl;
    return 0;
}

string input()
{
    return R"(0 3 6 9 12 15
1 3 6 10 15 21
10 13 16 21 30 45
)";
}