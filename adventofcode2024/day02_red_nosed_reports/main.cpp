#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

string input();

bool check_is_safe(vector<int> &v, int skip_id) {
    int prev = 0;
    bool is_asc;
    bool is_first_pair = true;
    bool is_safe = true;
    for (int i=0; i<v.size(); ++i) {
        if (i == skip_id) continue;
        int cur = v[i];
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
    return is_safe;
}

int main()
{
    string str;
    int safe_reports = 0;
    for (stringstream file(input()); getline(file, str);)
    {
        vector <int> vec1;
        stringstream ss(str);
        string s;
        while (getline(ss, s, ' ')) {
            vec1.push_back(stoi(s));
        }
        for (int i=0; i< vec1.size(); i++) {
            if (check_is_safe(vec1, i)) {
                safe_reports++;
                break;
            }
        }
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