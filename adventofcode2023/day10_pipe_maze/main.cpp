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
    int j = get<1>(cur);
    char c = maze[i][j];
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

vector<pair<int,int>> start_routes(const vector<string>& maze, int i, int j, char &out_char) {
    vector<pair<int,int>> res;
    char up = 0;
    char down = 0;
    char left = 0;
    char right = 0;

    if (i-1>=0) {
        up = maze[i-1][j];
        if (up == '|' || up == 'F' || up == '7') {
            up = 1;
            pair<int,int> p=make_pair(i-1,j);
            res.push_back(p);
        }
    }
    if (i+1<maze.size()) {
        down = maze[i+1][j];
        if (down == '|' || down == 'L' || down == 'J') {
            down = 1;
            pair<int,int> p=make_pair(i+1,j);
            res.push_back(p);
        }
    }
    if (j-1 >=0) {
        left = maze[i][j-1];
        if (left == '-' || left == 'F' || left == 'L') {
            left = 1;
            pair<int,int> p=make_pair(i,j-1);
            res.push_back(p);
        }
    }
    if (j+1<maze[0].length()) {
        right = maze[i][j+1];
        if (right == '-' || right == '7' || right == 'J') {
            right = 1;
            pair<int,int> p=make_pair(i,j+1);
            res.push_back(p);
        }
    }
    if (res.size() != 2) throw std::invalid_argument( "res.size() != 2" );
    if (down == 1 && right == 1) out_char = 'F';
    if (left == 1 && right == 1) out_char = '-';
    if (left == 1 && down == 1) out_char = '7';
    if (down == 1 && up == 1) out_char = '|';
    if (up == 1 && left == 1) out_char = 'J';
    if (up == 1 && right == 1) out_char = 'L';

    return res;
}

int main()
{
    vector<string> maze;
    map<pair<int,int>, char> pipe;
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
    pair<int,int> start = make_pair(start_i, start_j);
    char start_char = 0;
    vector<pair<int,int>> pr = start_routes(maze, start_i, start_j, start_char);
    pipe.insert({start, start_char});
    maze[start_i][start_j]=start_char;
    
    int step = 1;
    pair<int,int> cur1 = pr[0];
    pair<int,int> prev1 = start;
    pair<int,int> cur2 = pr[1];
    pair<int,int> prev2 = start;
    do {
        pipe.insert({cur1, maze[get<0>(cur1)][get<1>(cur1)]});
        pipe.insert({cur2, maze[get<0>(cur2)][get<1>(cur2)]});
        pair<int,int> next1 = next(maze, cur1, prev1);
        prev1 = cur1;
        cur1 = next1;
        pair<int,int> next2 = next(maze, cur2, prev2);
        prev2 = cur2;
        cur2 = next2;
        step++;
    } while (cur1 != cur2);
    pipe.insert({cur1, maze[get<0>(cur1)][get<1>(cur1)]});
    // cout << "pipe" << endl;
    // for (auto const& [key,val] : pipe) {
    //     cout << get<0>(key) << " " << get<1>(key) << " " << val << endl;
    // }
    vector<char> all_types {'F', '-', '7', '|', 'J', 'L'};
    map<char,pair<int,int>> pipe_type_map {{'F', {-1, -1}}, {'-', {-1,0}}, {'7', {-1,1}},{'|', {0,1}},{'J',{1,1}},{'L',{1,-1}}};
    int res = 0;
    for (int i=0;i<maze.size();++i) {
        // cout << "--- i " << i << endl;
        bool is_even = true;
        bool pipe_segment_started = false;
        pair<int,int> first_segment_type;
        for (int j=0;j<maze[0].length();++j){
            char cur_char = maze[i][j];
            pair<int,int> cur_pair = make_pair(i,j);
            bool is_pipe = pipe.count(cur_pair);
            if (is_pipe) {
                pair<int,int> cur_segment_type = pipe_type_map[cur_char];
                // cout << "cur_segment_type1 " << get<0>(cur_segment_type) << " " <<get<1>(cur_segment_type)<<endl;
                if (!pipe_segment_started) {
                    // cout << "pipe started" <<endl;
                    pipe_segment_started = true;
                    first_segment_type = cur_segment_type;
                }
                int is_last = get<1>(cur_segment_type) == 1;
                if (is_last) {
                    // cout << "first_segment_type " << get<0>(first_segment_type) << " " <<get<1>(first_segment_type)<<endl;
                    // cout << "cur_segment_type2 " << get<0>(cur_segment_type) << " " <<get<1>(cur_segment_type)<<endl;
                    if (get<0>(cur_segment_type) == 0 || get<0>(first_segment_type) != get<0>(cur_segment_type)) {
                        is_even = !is_even;
                    }
                    pipe_segment_started = false;
                }
            } else {
                // cout << "j " << j<< " cur_char "<<cur_char<< " is_even " << is_even<<endl;
                if (!is_even) res++;
            }

        }
    }
     cout << "res " << res << endl;
    return 0;
}

string input()
{
    return R"(FF7FSF7F7F7F7F7F---7
L|LJ||||||||||||F--J
FL-7LJLJ||||||LJL-77
F--JF--7||LJLJ7F7FJ-
L---JF-JLJ.||-FJLJJ7
|F|F-JF---7F7-L7L|7|
|FFJF7L7F-JF7|JL---7
7-L-JL7||F7|L7F-7F7|
L.L7LFJ|||||FJL7||LJ
L7JLJL-JLJLJL--JLJ.L
)";
}