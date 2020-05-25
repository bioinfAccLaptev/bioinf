#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<int> get(string &s, int &i) {
    int j = i;
    vector<int> a;
    while (s[j] != ')') {
        j++;
        string number;
        if (s[j] == '-') number.push_back('-');
        j++;
        while (s[j] != ' ' && s[j] != ')') {
            number.push_back(s[j]);
            j++;
        }
        a.push_back(stoi(number));
    }
    i = j + 1;
    return a;
}
void add(vector<vector<int>> &graph, vector<int> &a) {
    for (int i = 1; i < a.size(); i++) {
        int x =  (a[i - 1] < 0 ? -2 * a[i - 1]: a[i - 1] * 2  + 1);
        int y =  (a[i] > 0 ? 2 * a[i]: -a[i] * 2  + 1);
        if (graph.size() <= x) {
            for (int j = graph.size(); j <= (x / 2) * 2 + 1; j++) graph.emplace_back();
        }
        if (graph.size() <= y) {
            for (int j = graph.size(); j <= (y / 2) * 2 + 1; j++) graph.emplace_back();
        }
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    int x =  (a[a.size() - 1] < 0 ? -2 * a[a.size() - 1]: a[a.size() - 1] * 2  + 1);
    if (graph.size() <= x) {
        for (int j = graph.size(); j <= (x / 2) * 2 + 1; j++) graph.emplace_back();
    }
    int y =  (a[0] > 0 ? 2 * a[0]: -a[0] * 2  + 1);
    if (graph.size() <= y) {
        for (int j = graph.size(); j <= (y / 2) * 2 + 1; j++) graph.emplace_back();
    }
    graph[x].push_back(y);
    graph[y].push_back(x);
}

void read(vector<vector<int>> &graph) {
    string s;
    getline(cin, s);
    int i = 0;
    while (i < s.size()) {
        vector<int> a = get(s, i);
        add(graph, a);
    }
    getline(cin, s);
    i = 0;
    while (i < s.size()) {
        vector<int> a = get(s, i);
        add(graph, a);
    }
}

void dfs(int v, vector<vector<int>> &graph, vector<int> &used) {
    used[v] = 1;
    for (int u : graph[v]) {
        if (!used[u]) {
            dfs(u,graph,used);
        }
    }
}


int main() {
    freopen("C:/C++/CodeForces/out.txt", "w", stdout);
    freopen("C:/C++/CodeForces/in.txt", "r", stdin);
    vector<vector<int>> graph;
    read(graph);
    vector<int> used(graph.size(), 0);
    int countCycles = 0;
    for (int i = 2; i < graph.size(); i++) {
        if (!used[i]){
            countCycles++;
            dfs(i,graph,used);
        }
    }
    cout << (int)(graph.size() / 2)  - countCycles - 1;

}