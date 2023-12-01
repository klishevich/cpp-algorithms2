#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string input();

bool is_number(char c) {
    return c >='0' && c <= '9';
}

int main()
{
    string str;
    int cnt = 0;
    for (stringstream file(input()); getline(file, str);)
    {
        char first = 0;
        for (int i=0; i<str.length(); ++i) {
            if (is_number(str[i])) {
                first = str[i];
                break;
            }
        }
        char last = 0;
        for (int i=str.length()-1; i>=0; --i) {
            if (is_number(str[i])) {
                last = str[i];
                break;
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
    return R"(1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet
)";
}