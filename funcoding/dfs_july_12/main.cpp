#include <vector>
#include <iostream>

using namespace std;


int main()
{
    int rows = 6;
    int cols = 6;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<pair<int, int>> stack;
    vector<vector<pair<int, int>>> prev(rows, vector<pair<int, int>>(cols, make_pair(-1,-1)));

    vector<vector<char>> maze = {
        {'0', 'S', '0', '0', '0', '0'},
        {'0', '1', '1', '1', '1', '0'},
        {'0', '0', '0', '0', '1', '0'},
        {'0', '1', '1', '0', '1', '1'},
        {'0', '1', '0', '0', '0', '0'},
        {'0', '1', '1', '1', 'E', '0'}
    };

    visited[0][1] = true;
    stack.push_back(make_pair(0, 1));

    pair<int, int> res = make_pair(-1, -1);

    do {
        pair<int, int> cur = stack.back();
        cout << "cur " << cur.first << " " << cur.second << endl;
        stack.pop_back();
        if (maze[cur.first][cur.second] == 'E') {
            res = cur;
            break;
        }
        vector<pair<int, int>> traverse = {
            make_pair(cur.first - 1, cur.second),
            make_pair(cur.first + 1, cur.second),
            make_pair(cur.first, cur.second - 1),
            make_pair(cur.first, cur.second + 1)
        };
        for (const pair<int, int>& el : traverse) {
            cout << "trav0 " << el.first << " " << el.second << endl;
            if (el.first >= 0 && el.first < rows && el.second >=0 && el.second < cols 
                && !visited[el.first][el.second] && maze[el.first][el.second] != '1') {
                cout << "trav " << el.first << " " << el.second << endl;
                visited[el.first][el.second] = true;
                stack.push_back(make_pair(el.first,el.second));
                prev[el.first][el.second] = cur;
            }
        }
    } while (stack.size() > 0);

    vector<vector<bool>> resp(rows, vector<bool>(cols, false));

    cout << "result" << endl;
    do {
        resp[res.first][res.second] = true;
        // cout << res.first << " " << res.second << endl;
        res = prev[res.first][res.second];
    } while (res.first != -1);

    // print out
    for (int i=0;i<rows;i++) {
        for (int j=0;j<cols;j++) {
            if (maze[i][j] == 'S') cout << 'S';
            else if (maze[i][j] == 'E') cout << 'E';
            else cout << (resp[i][j] == true ? '*' : ' ');
        }
        std::cout << "\n";
    }

    return 0;
}
