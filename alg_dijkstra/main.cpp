#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

string input();

class Vertex {
public:
    int id;
    int priority;

    Vertex(int id, int priority)
        : id(id)
        , priority(priority)
    {
    }

    bool operator<(const Vertex& v) const
    {
        // this will return true when second vertex
        // has lower priority. Suppose we have v1.priority=6
        // and v2.priority=5 then the object which
        // has min priority will be at the top
        return this->priority > v.priority;
    }
};

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

vector<vector<int>> read_graph()
{
    vector<vector<int>> graph;
    string str;
    for (stringstream file(input()); getline(file, str);)
    {
        if (str.size() > 0)
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
    }  

    return graph;
}

int main()
{
    // input
    int SIZE = 9;
    vector<vector<int>> graph = read_graph();
    print_vec<vector<int>>(graph);

    set<int> visited;
    priority_queue<Vertex> vertices_queue;

    // output
    vector<int> dist(SIZE, INT_MAX);

    // start from vertex 0
    vertices_queue.push(Vertex(0, 0));
    dist[0] = 0;

    do {
        Vertex u = vertices_queue.top();
        vertices_queue.pop();

        if (visited.count(u.id)) continue;

        visited.insert(u.id);
        int u_dist = dist[u.id];
        for (int v_id=0; v_id<SIZE; ++v_id) {
            bool u_v_has_route = graph[u.id][v_id] > 0;
            if (!visited.count(v_id) && u_v_has_route) {
                int v_cur_dist = dist[v_id];
                int u_v_dist = graph[u.id][v_id];
                if (v_cur_dist == INT_MAX || v_cur_dist > u_dist + u_v_dist) {
                    dist[v_id] = u_dist + u_v_dist;
                    vertices_queue.push(Vertex(v_id, dist[v_id]));
                }
            }
        }

    } while (visited.size() < SIZE || vertices_queue.size() > 0);

    for (auto c : dist)
        cout << c << " ";
    cout << endl;
    return 0;
}

string input()
{
    return R"(
0 4 0 0 0 0 0 8 0
4 0 8 0 0 0 0 11 0
0 8 0 7 0 4 0 0 2
0 0 7 0 9 14 0 0 0
0 0 0 9 0 10 0 0 0
0 0 4 14 10 0 2 0 0
0 0 0 0 0 2 0 1 6
8 11 0 0 0 0 1 0 7
0 0 2 0 0 0 6 7 0
)";
}