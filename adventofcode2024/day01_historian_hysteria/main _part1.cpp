#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

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
    vector <int> vec1;
    vector <int> vec2;
    string str;
    int cnt = 0;
    for (stringstream file(input()); getline(file, str);)
    {
        stringstream ss(str);
        string s;
        bool bFirst = true;
        while (getline(ss, s, ' ')) {
            if (s != "") {
                int num = stoi(s);
                if (bFirst) {
                    vec1.push_back(num);
                    bFirst = false;
                } else {
                    vec2.push_back(num);
                }
            }
        }
    }
    sort(vec1.begin(), vec1.end());
    for (int i = 0; i < vec1.size(); i++)
        cout << vec1[i] << " ";
    cout << endl;
    sort(vec2.begin(), vec2.end());
    for (int i = 0; i < vec2.size(); i++)
        cout << vec2[i] << " ";
    cout << endl;

    int res = 0;
    for (int i = 0; i < vec1.size(); i++)
        res += abs(vec1[i]-vec2[i]);

    cout << res << endl;

    return 0;
}

string input()
{
    return R"(3   4
4   3
2   5
1   3
3   9
3   3
)";
}