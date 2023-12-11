#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
string input();

int calc_dist(int i1, int j1, int i2, int j2, const vector<int> &empty_rows, const vector<int> &empty_cols) {
    int min_i=min(i1,i2);
    int max_i=max(i1,i2);
    int min_j=min(j1,j2);
    int max_j=max(j1,j2);
    int i_exp_cnt = 0;
    for (int row : empty_rows) if (min_i<row&&row<max_i) i_exp_cnt++;
    int j_exp_cnt =0;
    for (int col : empty_cols) if (min_j<col&&col<max_j) j_exp_cnt++;
    return max_i - min_i + i_exp_cnt + max_j - min_j + j_exp_cnt;
}

int main()
{
    vector<string> data;
    string str;
    int idx = 0;
    for (stringstream file(input()); getline(file, str);) {
        // cout << str << endl;
        data.push_back(str);
        idx++;
    }
    int ROWS=data.size();
    int COLS=data[0].length();

    vector<int> empty_rows;
    for (int i=0;i<ROWS;i++){
        bool is_empty_row=true;
        for (int j=0;j<COLS;j++) {
            if (data[i][j]=='#') {
                is_empty_row=false;
                break;
            }
        }
        if (is_empty_row) empty_rows.push_back(i);
    }

    vector<int> empty_cols;
    for (int j=0;j<COLS;j++){
        bool is_empty_col=true;
        for(int i=0;i<ROWS;i++){
            if(data[i][j]=='#') {
                is_empty_col=false;
            }
        }
        if (is_empty_col) empty_cols.push_back(j);
    }

    vector<vector<int>> galaxies;
    for (int i=0;i<ROWS;i++){
        for(int j=0;j<COLS;j++){
            char c = data[i][j];
            if (c=='#') galaxies.push_back({i,j});
        }
    }
    cout << "galaxies size " << galaxies.size() << endl;
    int res=0;
    for (int i=0;i<galaxies.size();i++){
        vector<int> g1=galaxies[i];
        for (int j=0;j<i;j++) {
            vector<int> g2 = galaxies[j];
            int dist = calc_dist(g1[0],g1[1],g2[0],g2[1],empty_rows,empty_cols);
            res += dist;
        }
    }
    cout << "res " << res<< endl;

    return 0;
}

string input()
{
    return R"(...#......
.......#..
#.........
..........
......#...
.#........
.........#
..........
.......#..
#...#.....
)";
}