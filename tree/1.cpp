#include <iostream>
#include <vector>
#include <map>

using namespace std;

int readNumber(int &i, string &s) {
    string number;
    while (i < s.size() && '0' <= s[i] && s[i] <= '9') {
        number.push_back(s[i]);
        i++;
    }
    return stoi(number);
}

void read(int &n, vector<vector<pair<int,int>>> &graph) {
    cin >> n;
    string s;
    while (cin >> s){
        int i = 0;
        int from = readNumber(i, s);
        i += 2;
        int to = readNumber(i, s);
        i += 1;
        int w = readNumber(i, s);
        if (graph.size() <= from) {
            for (int j = 0; j <= from - (int)graph.size(); j++) {
                graph.emplace_back();
            }
        }
        graph[from].push_back({to,w});
    }
}

void dfs(int v, vector<int> &used, vector<vector<pair<int,int>>> &graph, vector<int> &d, int dist) {
    used[v] = 1;
    for (pair<int,int> u : graph[v]) {
        if (!used[u.first]) {
            d[u.first] = dist + u.second;
            dfs(u.first, used, graph, d, d[u.first]);
        }
    }
}


int main() {
    freopen("C:/C++/CodeForces/out.txt", "w", stdout);
    freopen("C:/C++/CodeForces/in.txt", "r", stdin);
    int n;
    vector<vector<pair<int,int>>> graph;
    read(n, graph);
    vector<int> used;
    for (int i = 0; i < n; i++) {
        used.assign(graph.size(), 0);
        vector<int> d(graph.size(), 0);
        dfs(i, used, graph, d, 0);
        for (int j = 0; j < n; j++) cout << d[j] << ' ';
        cout << '\n';
    }

}