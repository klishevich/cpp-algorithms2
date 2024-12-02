#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

string input();

char is_number(char c) {
    return c >='0' && c <= '9' ? c : 0;
}

char is_string_number(vector <pair<string,char>>& v, string& s, size_t i) {
    for (pair<string,char>& vs : v) {
        if (s.substr(i, vs.first.length()) == vs.first) {
            return vs.second;
        }
    }
    return 0;
}

int main()
{
    unordered_map<int,int> vec2_map;
    vector <int> vec1;
    string str;
    int safe_reports = 0;
    for (stringstream file(input()); getline(file, str);)
    {
        stringstream ss(str);
        string s;
        int prev = 0;
        bool is_asc;
        bool is_first_pair = true;
        bool is_safe = true;
        while (getline(ss, s, ' ')) {
            int cur = stoi(s);
            if (prev != 0) {
                if (is_first_pair) {
                    is_asc = cur > prev ? true : false;
                    is_first_pair = false;
                }
                int diff = cur - prev;
                if (is_asc) {
                    bool is_asc_again = 0 < diff && diff < 4;
                    if (!is_asc_again) {
                        is_safe = false;
                        break;
                    } 
                } else {
                    int is_desc_again = -4 < diff && diff < 0;
                    if (!is_desc_again) {
                        is_safe = false;
                        break;
                    }
                }
            }
            prev = cur;
        }
        if (is_safe) safe_reports++;
    }

    cout << safe_reports << endl;

    return 0;
}

string input()
{
    return R"(7 6 4 2 1
1 2 7 8 9
9 7 6 2 1
1 3 2 4 5
8 6 4 4 1
1 3 6 7 9
)";
}