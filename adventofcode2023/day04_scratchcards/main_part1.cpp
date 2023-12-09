#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <math.h>

using namespace std;
string input();

int main()
{
    int res = 0;
    string str;

    for (stringstream file(input()); getline(file, str);) {
        int cnt = -1;
        map<int,int> win_num_map;
        stringstream ss(str);
        string s;
        bool start_win_num = false;
        bool start_my_num = false;
        while (getline(ss, s, ' ')) {
            if (!start_win_num) {
                if (s.back() == ':') start_win_num = true;
                continue;
            }
            if (start_win_num && !start_my_num) {
                if (s[0] == '|') {
                    start_my_num = true;
                    continue;
                } else if (s != "") {
                    int num = stoi(s);
                    win_num_map.insert({num, 0});
                }
            }
            if (start_my_num && s != "") {
                int num = stoi(s);
                map<int,int>::iterator pos = win_num_map.find(num);
                if (pos != win_num_map.end() && pos->second == 0) {
                    cnt += 1;
                    pos->second = pos->second + 1;
                }
            }
        }
        if (cnt >= 0) {
            res += pow(2, cnt);
        }
    }

    cout << "res " << res << endl;
    return 0;
}

string input()
{
    return R"(Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19
Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1
Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83
Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36
Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11
)";
}