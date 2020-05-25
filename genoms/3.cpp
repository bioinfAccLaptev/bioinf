#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

int getIndex(string &s, map<string, int> &index, vector<string> &nodes, int &next, vector<vector<int>> &graph, vector<pair<int,int>> &inAndOut) {
    if (index.count(s) != 0) {
        return index[s];
    }
    inAndOut.emplace_back(0,0);
    nodes.push_back(s);
    index[s] = next;
    graph.emplace_back();
    return next++;
}


void euler(vector<vector<int>> &graph, vector<string> &nodes, int v, vector<int> &path) {
    while (!graph[v].empty()) {
        int u = graph[v][graph[v].size() - 1];
        graph[v].pop_back();
        euler(graph, nodes, u, path);
    }
    path.push_back(v);
}

int main() {
    freopen("C:/C++/CodeForces/out.txt", "w", stdout);
    freopen("C:/C++/CodeForces/in.txt", "r", stdin);

    uint64_t k;
    cin >> k;

    string s;
    map<string, int> index;
    vector<string> nodes;
    int next = 0;
    vector<vector<int>> graph;
    vector<pair<int,int>> inAndOut;
    while (cin >> s) {
        string suffix = s.substr(1, k - 1);
        string prefix = s.substr(0, k - 1);
        int indexSuffix = getIndex(suffix, index, nodes, next, graph, inAndOut);
        int indexPrefix = getIndex(prefix, index, nodes, next, graph, inAndOut);
        inAndOut[indexPrefix].second++;
        inAndOut[indexSuffix].first++;
        graph[indexPrefix].push_back(indexSuffix);
    }
    vector<int> path;
    for (int i = 0; i < graph.size(); i++){
        if (inAndOut[i].second - inAndOut[i].first == 1){
            euler(graph, nodes, i, path);
            break;
        }
    }
    reverse(path.begin(), path.end());
    for (int i = 0; i < path.size(); i++) {
        if (i == 0) {
            cout << nodes[path[i]];
        } else {
            cout << nodes[path[i]].back();
        }
    }
}