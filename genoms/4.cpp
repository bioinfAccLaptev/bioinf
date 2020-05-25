#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;


int getIndex(string &s, map<string, int> &index, vector<string> &nodes, int &next, vector<vector<int>> &graph, vector<int> &in, vector<int> &out) {
    if (index.count(s) != 0) {
        return index[s];
    }
    in.push_back(0);
    out.push_back(0);
    nodes.push_back(s);
    index[s] = next;
    graph.emplace_back();
    return next++;
}


int main() {
    freopen("C:/C++/CodeForces/out.txt", "w", stdout);
    freopen("C:/C++/CodeForces/in.txt", "r", stdin);

    string s;
    map<string, int> index;
    vector<string> nodes;
    vector<int> in;
    vector<int> out;
    int next = 0;
    vector<vector<int>> graph;

    while (cin >> s) {
        string suffix = s.substr(1, s.size() - 1);
        string prefix = s.substr(0, s.size() - 1);
        int indexSuffix = getIndex(suffix, index, nodes, next, graph, in, out);
        int indexPrefix = getIndex(prefix, index, nodes, next, graph, in, out);
        out[indexPrefix]++;
        in[indexSuffix]++;
        graph[indexPrefix].push_back(indexSuffix);
    }

    vector<vector<int>> paths;
    vector<int> used(graph.size(), 0);
    for (int v = 0; v < graph.size(); v++) {
        if (in[v] != 1 || out[v] != 1){
            used[v] = 1;
            for (int u : graph[v]) {
                vector<int> path;
                path.push_back(v);
                path.push_back(u);
                used[u] = 1;
                while (in[u] == 1 && out[u] == 1) {
                    path.push_back(graph[u][0]);
                    u = graph[u][0];
                    used[u] = 1;
                }
                paths.push_back(path);
            }
        }
    }
    for (int v = 0; v < graph.size(); v++){
        if (!used[v]) {
            vector<int> path;
            used[v] = 1;
            path.push_back(v);
            for (int u : graph[v]) {
                while (u != v && !used[u]) {
                    used[u] = 1;
                    path.push_back(u);
                    u = graph[u][0];
                }
            }
            path.push_back(v);
            paths.push_back(path);
        }
    }
    for (const vector<int> &path : paths) {
        for (int i = 0; i < path.size(); i++) {
            if (i == 0) {
                cout << nodes[path[i]];
            } else {
                cout << nodes[path[i]].back();
            }
        }
        cout << ' ';
    }


}