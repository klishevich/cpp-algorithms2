#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <queue>
#include <map>

using namespace std;

int SIZE = 9;

string input();

class Graph {
private:
    map<int, map<int, int>> g;
    set<int> visited;
    map<int, int> dist;
public:
    Graph(int n, vector<vector<int>>& edges) {
        for (int i=0; i<edges.size(); ++i) {
            this->addEdge(edges[i]);
        } 
    }
    
    void addEdge(vector<int> edge) {
        int from = edge[0];
        int to = edge[1];
        int cost = edge[2];
        if (g.find(from) == g.end()) {
            g.insert({from, map<int, int>() });
        }
        g.find(from)->second.insert({to, cost});
    }
    
    int shortestPath(int node1, int node2) {
        // TODO
    }

    void print() {
        for (const auto &[k, v] : g) {
            cout << k << "=>" << endl;
            for (const auto &[k1, v1] : v)
                cout << " " << k1 << ":" << v1 << endl;
        }
        // for (auto v : g) {
        //     for (auto c : v)
        //         cout << c << " ";
        //     cout << endl;
        // }
        // cout << endl;
    }
};

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

void print_visited(set<int> visited) {
    cout << "visited: ";
    for (int i=0; i<SIZE; i++) {
        string v = visited.count(i)? "+": to_string(i);
        cout << v << " ";
    }
    cout << endl;
}

void print_queue(priority_queue<Vertex> q) {
    cout << "queue: ";
    do {
        Vertex a = q.top();
        cout << a.id << "(" << a.priority << ")" << " ";
        q.pop();
    } while (q.size() > 0);
    cout << endl;
}

int main()
{
    // input
    vector<vector<int>> edges = read_edges();
    print_vec<vector<int>>(edges);

    Graph* obj = new Graph(4, edges);
    obj->print();

    int param_2 = obj->shortestPath(3,2);
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