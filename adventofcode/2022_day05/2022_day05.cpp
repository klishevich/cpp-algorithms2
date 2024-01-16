// 2022_day05.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <vector>

using namespace std;

string input();

vector<string> split(const string& str, const char& ch) {
    string next;
    vector<string> result;

    for (string::const_iterator it = str.begin(); it != str.end(); it++) {
        if (*it == ch) {
            if (!next.empty()) {
                result.push_back(next);
                next.clear();
            }
        }
        else {
            next += *it;
        }
    }
    if (!next.empty())
        result.push_back(next);
    return result;
}

int main()
{
    set<char> set2;
    set<char> set1;
    string str;
    int res = 0;
    int ii = 0;
    for (stringstream file(input()); getline(file, str); ii++)
    {
        if (str == "")
        {
            cout << "line break" << endl;
        }
        else {
            cout << "str " << str << endl;
        }
    }
    cout << "result " << res << endl;
    return 0;
}

string input()
{
    return R"([D]    
[N] [C]    
[Z] [M] [P]
 1   2   3 

move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2
)";
}
