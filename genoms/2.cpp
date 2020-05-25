#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    freopen("C:/C++/CodeForces/out.txt", "w", stdout);
    freopen("C:/C++/CodeForces/in.txt", "r", stdin);
    int k;
    string text;
    cin >> k >> text;

    set<string> substrings;
    for (int i = 0; i < text.size() - k + 2; i++) {
        substrings.insert(text.substr(i, k - 1));
    }
    vector<string> sortedSubstrings(substrings.begin(), substrings.end());
    int next = 0;
    map<string,int> index;
    for (const string &s : sortedSubstrings) {
        index[s] = next++;
    }
    vector<vector<int>> graph(sortedSubstrings.size());

    for (int i = 0; i < text.size() - k + 1; i++) {
        string prefix = text.substr(i, k - 1);
        string suffix = text.substr(i + 1, k - 1);
        graph[index[prefix]].push_back(index[suffix]);
    }
    for (int u = 0; u < graph.size(); u++) {
        if (!graph[u].empty()) {
            cout << sortedSubstrings[u] << " -> ";
        }
        sort(graph[u].begin(), graph[u].end());
        for (int v = 0; v < graph[u].size(); v++) {
            cout << sortedSubstrings[graph[u][v]] << (v == graph[u].size() - 1 ? '\n' : ',');
        }
    }
}