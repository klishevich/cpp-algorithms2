#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <tuple>
#include <map>

using namespace std;

typedef pair<int,int> row_col_pair;

typedef struct {
	int row;
	int col;
	int step;
} row_col_step_struct;

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

int main() {
	int ROWS = 19;
	int COLS = 21;
	vector<vector<bool>> maze_matrix;
	string str;
	for (int i=0; i<ROWS; i++) {
		vector<bool> maze_line;
		cin >> str;
		for (int j=0; j<COLS; j++) {
			maze_line.push_back(str[(size_t)j] == '0' ? false : true);
		}
		maze_matrix.push_back(maze_line);
	}

	// print_vec<vector<bool>>(maze_matrix);

	map<row_col_pair,row_col_pair> visited_prev_map;
	deque<row_col_step_struct> bfs_queue;

	row_col_step_struct start_pos = {1, 15, 0};
	row_col_step_struct end_pos1 = {9, 0, 0};
	row_col_step_struct end_pos2 = {9, 20, 0};
	bfs_queue.push_back(start_pos);
	size_t queue_index = 0;

	vector<pair<int,int>> adj_cells = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

	do {
		row_col_step_struct s = bfs_queue[queue_index];
		if ((s.row == end_pos1.row && s.col == end_pos1.col)
			|| (s.row == end_pos2.row && s.col == end_pos2.col)) break;

		for (auto p : adj_cells) {
			int row = s.row + p.first;
			int col = s.col + p.second;
			if (row>=0 && row<ROWS && col>=0 && col<COLS
				&& maze_matrix[(size_t)row][(size_t)col]==0 && !visited_prev_map.count({row, col})) {
				visited_prev_map.insert({{row,col}, {s.row, s.col}});
				row_col_step_struct new_element = { row, col, s.step + 1};
				bfs_queue.push_back(new_element);
			}
		}
		queue_index++;
	}
	while (queue_index < bfs_queue.size());

	row_col_step_struct e = bfs_queue[queue_index];
	cout << "(" << e.row << "," << e.col << ")" << endl;
	row_col_pair r = { e.row, e.col };
	do {
		r = visited_prev_map.find(r)->second;
		cout << "(" << r.first << "," << r.second << ")" << endl;
	}
	while (r.first != start_pos.row || r.second != start_pos.col );

	cout << "End" << endl;
}





