#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

void read(vector<vector<int>> &graph) {
    string s;
    while (getline(cin, s)) {
        int i = 0;
        string from;
        while (s[i] != ' ') {
            from.push_back(s[i]);
            i++;
        }
        int v = stoi(from);
        if (graph.size() <= v) {
            for (int k = graph.size(); k <= v; k++){
                graph.emplace_back();
            }
        }
        i += 4;
        string number;
        for (int j = i; j < s.size(); j++) {
            if (s[j] == ',') {
                int u = stoi(number);
                graph[v].push_back(u);
                number.clear();
            } else {
                number.push_back(s[j]);
            }
            if (j == s.size() - 1) {
                graph[v].push_back(stoi(number));
            }
        }
    }
}


int main() {
    freopen("C:/C++/CodeForces/out.txt", "w", stdout);
    freopen("C:/C++/CodeForces/in.txt", "r", stdin);
    string s;
    vector<vector<int>> graph;
    read(graph);
    vector<int> in(graph.size(), 0);
    vector<int>out(graph.size(), 0);
    for (int v = 0; v < graph.size(); v++) {
        out[v] = graph[v].size();
        for (int u : graph[v]) {
            in[u]++;
        }
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
            if (i != 0) {
                cout << " -> ";
            }
            cout << path[i] ;
        }
        cout << '\n';
    }


}