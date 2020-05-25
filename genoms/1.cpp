#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

void add(string &x, string &y, map<string,vector<string>> &graph) {
    if (graph.count(x) == 0) {
        graph[x] = vector<string>(1, y);
    } else {
        graph[x].push_back(y);
    }
}

int main() {
    freopen("C:/C++/CodeForces/out.txt", "w", stdout);
    freopen("C:/C++/CodeForces/in.txt", "r", stdin);
    map<string,vector<string>> graph;
    vector<string> strings;
    string s;
    while (cin >> s) {
        strings.push_back(s);
    }
    for (int i = 0; i < strings.size(); i++) {
        string suffix = strings[i].substr(1, strings[i].size() - 1);
        for (int j = 0; j < strings.size(); j++) {
            if (i != j) {
                string prefix = strings[j].substr(0, strings[j].size() - 1);
                if (suffix == prefix) {
                    add(strings[i], strings[j], graph);
                }
            }
        }
    }
    for (auto &edges : graph) {
        string out = edges.first;
        for (string &in : edges.second) {
            cout << out << " -> " << in << '\n';
        }
    }
}