#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
string input();

void print_vec(string title, const vector<string>& v) {
    cout << title << endl;
    for (auto vv:v) {
        cout << vv << endl;
    }
}

int tilt_string(string &str) {
    vector<int> rounded_rock_positions;
    int rounded_rock_cnt = 0;
    int last_cube_rock_idx = -1;
    for(int i=0;i<str.length();i++) {
        char c = str[i];
        if (c == '#') {
            for (int j=0;j<rounded_rock_cnt;j++) {
                rounded_rock_positions.push_back(last_cube_rock_idx+1+j);
            }
            last_cube_rock_idx = i;
            rounded_rock_cnt = 0;
        } else if (c == 'O') {
            rounded_rock_cnt++;
        }
    }
    int original_size = str.length() - 1;
    int res = 0;
    for (int pos : rounded_rock_positions) {
        res+=(original_size-pos);
    }
    return res;
}

vector<string> transpose(vector<string> &data) {
    int rows = data.size();
    int cols = data[0].length();
    vector<string> data_t;
    string column;
    for (int j=0;j<cols;j++) {
        for (int i=0;i<rows;i++) {
            int c = data[i][j];
            column+=c;
        }
        column+='#';
        data_t.push_back(column);
        column.clear();
    }
    return data_t;
}

int main()
{
    vector<string> data;
    string str;

    for (stringstream file(input()); getline(file, str);) {
        data.push_back(str);
    }
    int rows = data.size();
    int cols = data[0].length();

    cout << "rows " << rows << " cols " << cols << endl;

    vector<string> data_t = transpose(data);
    print_vec("transpose", data_t);
    int res = 0;
    for (string &s : data_t) {
        int r = tilt_string(s);
        cout << "r " << r << endl;
        res += r;
    }
    cout << "res " << res << endl;

    return 0;
}

string input()
{
    return R"(O....#....
O.OO#....#
.....##...
OO.#O....O
.O.....O#.
O.#..O.#.#
..O..#O..O
.......O..
#....###..
#OO..#....
)";
}