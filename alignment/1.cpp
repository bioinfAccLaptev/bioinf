#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;


int main() {
    freopen("C:/C++/CodeForces/out.txt", "w", stdout);
    freopen("C:/C++/CodeForces/in.txt", "r", stdin);

    string s1, s2;
    cin >> s1 >> s2;
    int n = (int)s1.size();
    int m = (int)s2.size();

    vector<vector<int>> maxAtPrefix(n + 1, vector<int>(m + 1, 0));
    vector<vector<pair<int, int>>> previous(n + 1, vector<pair<int,int>>(m + 1, make_pair(0,0)));

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < m + 1; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                maxAtPrefix[i][j] = maxAtPrefix[i - 1][j - 1] + 1;
                previous[i][j] = make_pair(i - 1, j - 1);
            } else {
                maxAtPrefix[i][j] = max(maxAtPrefix[i - 1][j], maxAtPrefix[i][j - 1]);
                previous[i][j] = (maxAtPrefix[i - 1][j] > maxAtPrefix[i][j - 1]) ? make_pair(i - 1, j) : make_pair(i, j - 1);
            }
        }
    }

    string subsequence;
    for (int i = n, j = m; i != 0 && j != 0;) {
        if (previous[i][j].first == i - 1 &&  previous[i][j].second == j - 1) {
            subsequence.push_back(s1[i - 1]);
        }
        int lasti = i, lastj = j;
        i = previous[lasti][lastj].first;
        j = previous[lasti][lastj].second;
    }
    reverse(subsequence.begin(), subsequence.end());
    cout << subsequence;
}