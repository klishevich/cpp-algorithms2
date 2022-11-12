// boris_graph_connected_components.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <vector>
#include <map>

using namespace std;

void printGraphRoutes(map<int, vector<int>> &a)
{
    for (auto const& kv : a)
    {
        std::cout << kv.first << " =>";
        for (auto const& i : kv.second)
            std::cout << " " << i;
        std::cout << std::endl;
    }
    cout << "-------------" << endl;
}

void printGraphIsVisited(map<int, bool> &a)
{
    for (auto const& kv : a)
    {
        std::cout << kv.first << " =>" << kv.second;
        std::cout << std::endl;
    }
    cout << "-------------" << endl;
}

map<int, vector<int>> graphMap;
map<int, bool> isVisitedMap;

void dfs(int curV)
{
    if (isVisitedMap.contains(curV)) {
        isVisitedMap.erase(curV);
        for (auto nextV : graphMap.at(curV)) dfs(nextV);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    int res = 0;
    if (m == 0)
        cout << n << endl;
    else
    {
        for (int i = 0; i < m; ++i)
        {
            int s, e;
            cin >> s >> e;

            graphMap.insert(pair<int, vector<int>>(s, vector<int>()));
            graphMap[s].push_back(e);
            graphMap.insert(pair<int, vector<int>>(e, vector<int>()));
            graphMap[e].push_back(s);

            isVisitedMap.insert(pair<int, bool>(s, false));
            isVisitedMap.insert(pair<int, bool>(e, false));
        }
    }
    printGraphIsVisited(isVisitedMap);
    printGraphRoutes(graphMap);
    
    while (isVisitedMap.size() > 0)
    {
        ++res;
        int index = isVisitedMap.begin()->first;
        dfs(index);
        printGraphIsVisited(isVisitedMap);
    }

    cout << "res " << res << endl;
}
