#include <iostream>
#include <string>

using namespace std;

string input();

int main(int argc, char const *argv[])
{
	string line;
	for (stringstream file(input()); getline(file, line);)
    {
        stringstream ss(line);
        string str;
        while (getline(ss, str, ' ')) {
            if (str != "") {
                int num = stoi(str);
                cout << num << endl;
            }
        }
    }
	// string inputString = input();
	// istringstream iss(inputString);
	// string s;
	// while ( getline(iss, s, ' ')) {
	// 	cout << s << endl;
	// }

	// cout << "test " << endl;
	// cout << inputString << endl;
	return 0;
}

string input()
{
	return R"(3   4
4   3
2   5
1   3
3   9
3   3)";
}