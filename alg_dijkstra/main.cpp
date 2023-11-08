#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <deque>

using namespace std;

string input();

template <typename T>
void print_vec(vector<T> &vec)
{
    for (auto v : vec) {
        for (auto c : v)
            cout << c << " ";
        cout << endl;
    }
    cout << endl;
}

int main()
{
    vector<vector<int>> graph;

    int i = 0;
    string str;
    for (stringstream file(input()); getline(file, str); i++)
    {
        istringstream iss(str);
        string s;
        vector<int> row;
        while (getline(iss, s, ' '))
        {
            row.push_back(stoi(s));
        }
        graph.push_back(row);
    }

    print_vec<vector<int>>(graph);

    return 0;
}

string input()
{
    return R"(
0 4 0 0 0 0 0 8 0
0 0 8 0 0 0 0 11 0
0 0 0 7 0 4 0 0 2
0 0 0 0 9 14 0 0 0
0 0 0 0 0 10 0 0 0
0 0 0 0 0 0 2 0 0
0 0 0 0 0 0 0 1 6
0 0 0 0 0 0 0 0 7
)";
}