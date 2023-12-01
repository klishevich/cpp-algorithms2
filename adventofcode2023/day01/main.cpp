#include <iostream>
#include <string>
#include <sstream>
#include <vector>

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
    vector <pair<string,char>> vec = {
        {"one", '1'},
        {"two", '2'},
        {"three", '3'},
        {"four", '4'},
        {"five", '5'},
        {"six", '6'},
        {"seven", '7'},
        {"eight", '8'},
        {"nine", '9'}
    };
    string str;
    int cnt = 0;
    for (stringstream file(input()); getline(file, str);)
    {
        char first = 0;
        char last = 0;
        for (int i=0; i<str.length(); ++i) {
            char c1 = is_number(str[i]);
            if (c1 != 0) {
                if (first == 0) {
                    first = c1;
                }
                last = c1;
            } else {
                char c2 = is_string_number(vec, str, i);
                if (c2 != 0) {
                    if (first == 0) {
                        first = c2;
                    }
                    last = c2;
                }
            }
        }

        if (first == 0 || last == 0) {
            throw std::invalid_argument( "first or last not found!" );
        }
        string calib_value = string() + first + last;
        cnt += stoi(calib_value);
    }
    cout << "res " << cnt << endl;
    return 0;
}

string input()
{
    return R"(two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen
)";
}