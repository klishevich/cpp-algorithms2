#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <utility>

using namespace std;
string input();

void print_vec(string title, const vector<pair<int,int>>& v) {
    cout << title << endl;
    for (pair<int,int> p:v) {
        cout << get<0>(p) << " " << get<1>(p) << endl;
    }
    cout << endl;
}

int find_s(const string& str) {
    for (int i=0; i<str.length(); i++) {
        if (str[i] == 'S') return i;
    }
    return -1;
}

pair<int,int> next(const vector<string>& maze, pair<int,int> &cur, pair<int,int> &prev) {
    int i = get<0>(cur);
    // cout << "i " << i << endl;
    int j = get<1>(cur);
    // cout << "j " << j << endl;
    char c = maze[i][j];
    // cout << "c " << c << endl;
    vector<pair<int,int>> r;

    if (c == 'F') {
        r = vector<pair<int,int>> {{i, j+1}, {i+1, j}};
    } else if (c == '-') {
        r = vector<pair<int,int>> {{i, j-1}, {i, j+1}};
    } else if (c == '7') {
        r =  vector<pair<int,int>> {{i, j-1}, {i+1, j}};
    } else if (c == '|') {
        r = vector<pair<int,int>> {{i-1, j}, {i+1, j}};
    } else if (c == 'J') {
        r = vector<pair<int,int>> {{i-1, j}, {i, j-1}};
    } else if (c == 'L') {
        r = vector<pair<int,int>> {{i-1, j}, {i, j+1}};
    }
    // print_vec("r vec", r);
    vector<pair<int,int>> res;
    for (const pair<int,int> &a : r) {
        if (a != prev) res.push_back(a);
    }
    if (res.size() != 1) throw std::invalid_argument( "res.size() != 1" );
    return res[0];
}

vector<pair<int,int>> start_routes(const vector<string>& maze, int i, int j) {
    vector<pair<int,int>> res;

    if (i-1>=0) {
        char up = maze[i-1][j];
        // cout << "up " << up << endl;
        if (up == '|' || up == 'F' || up == '7') {
            pair<int,int> p=make_pair(i-1,j);
            res.push_back(p);
        }
    }
    if (i+1<maze.size()) {
        char down = maze[i+1][j];
        // cout << "down " << down << endl;
        if (down == '|' || down == 'L' || down == 'J') {
            pair<int,int> p=make_pair(i+1,j);
            res.push_back(p);
        }
    }
    if (j-1 >=0) {
        char left = maze[i][j-1];
        // cout << "left " << left << endl;
        if (left == '-' || left == 'F' || left == 'L') {
            pair<int,int> p=make_pair(i,j-1);
            res.push_back(p);
        }
    }
    if (j+1<maze[0].length()) {
        char right = maze[i][j+1];
        // cout << "right " << right << endl;
        if (right == '-' || right == '7' || right == 'J') {
            pair<int,int> p=make_pair(i,j+1);
            res.push_back(p);
        }
    }
    if (res.size() != 2) throw std::invalid_argument( "res.size() != 2" );
    return res;
}

int main()
{
    vector<string> maze;
    string str;
    // int res = 0;
    int idx = 0;
    int start_i = -1;
    int start_j = -1;
    for (stringstream file(input()); getline(file, str);) {
        if (start_i == -1) {
            int s_idx = find_s(str);
            if (s_idx != -1) {
                start_i = idx;
                start_j = s_idx;
            }
        }
        maze.push_back(str);
        idx++;
    }
    // cout << "start_i " << start_i << " start_j " << start_j << endl;
    pair<int,int> start = make_pair(start_i, start_j);
    vector<pair<int,int>> pr = start_routes(maze, start_i, start_j);
    // print_vec("pr", pr);
    
    int step = 1;
    pair<int,int> cur1 = pr[0];
    pair<int,int> prev1 = start;
    pair<int,int> cur2 = pr[1];
    pair<int,int> prev2 = start;
    do {
        // cout << "====== " << step << " =====" << endl;
        pair<int,int> next1 = next(maze, cur1, prev1);
        prev1 = cur1;
        cur1 = next1;
        pair<int,int> next2 = next(maze, cur2, prev2);
        prev2 = cur2;
        cur2 = next2;
        step++;
    } while (cur1 != cur2);
    cout << "step " << step << endl;
    return 0;
}

string input()
{
    return R"(..F7.
.FJ|.
SJ.L7
|F--J
LJ...
)";
}