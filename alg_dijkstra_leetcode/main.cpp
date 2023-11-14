#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <limits.h>

using namespace std;

int SIZE = 9;

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
        // has min priority will be at the top
        return this->priority > v.priority;
    }
};

class Graph {
private:
    map<int, map<int, int>> g;
    int n;
public:
    Graph(int n, vector<vector<int>>& edges) {
        this->n = n;
        for (int i=0; i<edges.size(); ++i) {
            this->add_edge(edges[i]);
        } 
    }
    
    void add_edge(vector<int> edge) {
        int from = edge[0];
        int to = edge[1];
        int cost = edge[2];
        if (g.find(from) == g.end()) {
            g.insert({from, map<int, int>() });
        }
        g.find(from)->second.insert({to, cost});
    }
    
    int shortest_path(int node1, int node2) {
        set<int> visited;
        priority_queue<Vertex> vertices_queue;
        map<int, int> distances;

        vertices_queue.push(Vertex(node1, 0));
        distances.insert({node1, 0});

        do {
            Vertex u = vertices_queue.top();
            vertices_queue.pop();

            if (visited.count(u.id)) continue;

            visited.insert(u.id);
            int u_dist = distances.at(u.id);

            if (u.id == node2) return u_dist;

            if (g.find(u.id) == g.end()) continue;
            map<int, int> routes_to = g.find(u.id)->second;
             
            for (auto const& [v_id, u_v_dist] : routes_to) {
                if (visited.count(v_id)) continue;

                int v_cur_dist = distances.find(v_id) == distances.end() ? INT_MAX : distances.find(v_id) -> second;
                int v_new_dist = u_dist + u_v_dist;
                if (v_new_dist < v_cur_dist) {
                    distances[v_id] = v_new_dist;
                    vertices_queue.push(Vertex(v_id, v_new_dist));
                }
            }

        } while (vertices_queue.size() > 0);

        return -1;
    }

    void print() {
        cout << "n " << n << endl;
        for (const auto &[k, v] : g) {
            cout << k << "=>" << endl;
            for (const auto &[k1, v1] : v)
                cout << " " << k1 << ":" << v1 << endl;
        }
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

vector<vector<int>> read_edges()
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
    vector<vector<int>> edges = read_edges();
    print_vec<vector<int>>(edges);

    Graph* graph = new Graph(4, edges);
    graph->print();

    cout << "shortest 3 -> 2 (6): " << graph->shortest_path(3,2) << endl;
    cout << "shortest 0 -> 3 (-1): " << graph->shortest_path(0,3) << endl;
    graph->add_edge(vector<int>({1, 3, 4}));
    // graph->print();
    cout << "shortest 0 -> 3 (6): " << graph->shortest_path(0,3) << endl;
    return 0;
}

string input()
{
    return R"(
0 2 5
0 1 2
1 2 1
3 0 3
)";
}