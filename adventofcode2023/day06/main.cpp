#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
string input();

void print_vec(string title, const vector<long>& v) {
    cout << title << endl;
    for (auto vv:v) {
        cout << vv << " ";
    }
    cout << endl;
}

vector<long> parse_string(const string& str) {
    vector<long> res;
    stringstream ss(str);
    string s;
    int idx = 0;
    while (getline(ss, s, ' ')) {
        if (idx > 0 && s != "") res.push_back(stol(s));
        idx++;
    }
    return res;
}

long calc_win_cases(long time, long record) {
    long res = 0;
    for (long btn_sec=1; btn_sec < time; btn_sec++) {
        long speed = btn_sec;
        long time_left = time - btn_sec;
        long distance = speed * time_left;
        if (distance > record) res++;
    }
    return res;
}

int main()
{
    long res = 1;
    vector<long> times;
    vector<long> distances;
    string str;
    int line_idx = 0;
    for (stringstream file(input()); getline(file, str);) {
        if (line_idx == 0) {
            times = parse_string(str);
        } 
        if (line_idx == 1) {
            distances = parse_string(str);
        }
        line_idx++;
    }

    print_vec("times", times);
    print_vec("distances", distances);
    for (long i=0; i<times.size(); i++) {
        res = res * calc_win_cases(times[i], distances[i]);
    }
    cout << "res " << res << endl;
    return 0;
}

string input()
{
    return R"(Time:      7  15   30
Distance:  9  40  200
)";
}