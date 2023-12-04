#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

using namespace std;
string input();

int main()
{
    int res = 0;
    string str;
    int MAX_WIN_SIZE = 11;
    vector<int> card_copies(MAX_WIN_SIZE, 0);
    for (stringstream file(input()); getline(file, str);) {
        cout << str << endl;
        int win_cnt = -1;
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
                    win_cnt += 1;
                    pos->second = pos->second + 1;
                }
            }
        }
        for (auto cc : card_copies) {
            cout << cc << " ";
        }
        cout << endl;
        cout << "win_cnt " << win_cnt+1 << endl;
        int cards_cnt = 1 + card_copies[0];
        cout << "cards_cnt " << cards_cnt << endl;
        res += cards_cnt;
        for (int i=0;i<MAX_WIN_SIZE;++i) {
            int is_add_win = i <= win_cnt ? 1 : 0;
            card_copies[i] = card_copies[i+1] + is_add_win * cards_cnt;
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