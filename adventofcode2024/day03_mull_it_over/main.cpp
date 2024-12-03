#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

string input();

bool is_number(const string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

vector<string> split(string& s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        res.push_back(token);
        pos_start = pos_end + delim_len;
    }
    token = s.substr(pos_start);
    res.push_back(token);

    return res;
}

long calc(string& s) {
    // cout << "s: " << s << endl;
    vector<string> vec1 = split(s, "mul(");

    string delimiter2 = ",";
    string delimiter3 = ")";

    long res = 0;

    for (int i=0; i<vec1.size(); i++) {
        string token1 = vec1[i];
        size_t pos_end2 = token1.find(delimiter2, 0);
        if (pos_end2 !=string::npos) {
            string token2 = token1.substr(0, pos_end2);
            if (is_number(token2)) {
                size_t pos_end3 = token1.find(delimiter3, pos_end2 + 1);
                if (pos_end3 !=string::npos) {
                    string token3 = token1.substr(pos_end2 + 1, pos_end3 - pos_end2 -1);
                    // cout << " " << endl;
                    if (is_number(token3)) {
                        cout << token2 << " " << token3 << endl;
                        res+= stoi(token2)*stoi(token3);
                    }
                }
            }
        }
    }

    return res;
}

int main()
{
    string str;
    long res = 0;
    vector<string> vec1;
    for (stringstream file(input()); getline(file, str);)
    {
        res += calc(str);
    }

    cout << "res " << res << endl;

    return 0;
}

string input()
{
    return R"(xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))
    )";
}