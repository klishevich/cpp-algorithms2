#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <tuple>
#include <map>

using namespace std;

typedef pair<size_t,size_t> row_col_type;

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
	size_t ROWS = 19;
	size_t COLS = 21;
	vector<vector<bool>> maze_matrix;
	string str;
	for (size_t i=0; i<ROWS; i++) {
		vector<bool> maze_line;
		cin >> str;
		for (size_t j=0; j<COLS; j++) {
			maze_line.push_back(str[j] == '0' ? false : true);
		}
		maze_matrix.push_back(maze_line);
	}

	// print_vec<vector<bool>>(maze_matrix);

	map<row_col_type,row_col_type> visited_prev_map;
	deque<row_col_type> bfs_queue;

	row_col_type start_position = {1, 15};
	row_col_type end_position1 = {9, 0};
	row_col_type end_position2 = {9, 20};
	bfs_queue.push_back(start_position);

	do {
		row_col_type cur = bfs_queue.front();
		if (cur == end_position1 || cur == end_position2) break;
		bfs_queue.pop_front();
		size_t row = cur.first;
		size_t col = cur.second;
		if (row>0 && maze_matrix[row-1][col]==0 && !visited_prev_map.count({row-1, col})) {
			visited_prev_map.insert({{row-1, col}, cur});
			bfs_queue.push_back({row-1, col});
		}
		if (row<ROWS-1 && maze_matrix[row+1][col]==0 && !visited_prev_map.count({row+1,col})) {
			visited_prev_map.insert({{row+1, col}, cur});
			bfs_queue.push_back({row+1, col});
		}
		if (col>0 && maze_matrix[row][col-1]==0 && !visited_prev_map.count({row,col-1})) {
			visited_prev_map.insert({{row, col-1}, cur});
			bfs_queue.push_back({row, col-1});
		}
		if (col<COLS-1 && maze_matrix[row][col+1]==0 && !visited_prev_map.count({row,col+1})) {
			visited_prev_map.insert({{row, col+1}, cur});
			bfs_queue.push_back({row, col+1});
		}
	}
	while (bfs_queue.size() > 0);

	row_col_type r = bfs_queue.front();
	cout << "(" << r.first << "," << r.second << ")" << endl;
	do {
		r = visited_prev_map.find(r)->second;
		cout << "(" << r.first << "," << r.second << ")" << endl;
	}
	while (r != start_position);

	cout << "End" << endl;
}





