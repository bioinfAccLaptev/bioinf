#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int penalty = 5;
const int stop = -100;

int max3(int a, int b, int c) {
    return max(max(a, b), c);
}

void read(vector<vector<int>> &cost,  map<char,int> &charToInt, vector<char> &intToChar) {
    char c;
    for (int i = 0; i < 20; i++) {
        cin >> c;
        intToChar.push_back(c);
        charToInt[c] = i;
    }
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            cin >> cost[i][j];
        }
    }
}


int main() {
    freopen("C:/C++/CodeForces/out.txt", "w", stdout);
    freopen("C:/C++/CodeForces/in.txt", "r", stdin);
    vector<vector<int>> cost(20, vector<int> (20));
    map<char,int> charToInt;
    vector<char> intToChar;
    read(cost,charToInt,intToChar);
    string s1;
    string s2;
    cin >> s1 >> s2;
    int n = (int) s1.size();
    int m = (int) s2.size();
    vector<vector<int>> alignment(n + 1, vector(m + 1, 0));
    vector<vector<pair<int,int>>> previous(n + 1, vector(m + 1, make_pair(0, 0)));
    previous[0][0] = make_pair(stop, stop);
    for (int i = 0; i <= n; i++) {
        alignment[i][0] = -penalty * i;
    }
    for (int i = 0; i <= m; i++) {
        alignment[0][i] = -penalty * i;
    }
    for (int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int lettersBoth = alignment[i - 1][j - 1] + cost[charToInt[s1[i - 1]]][charToInt[s2[j - 1]]];
            int letterFirst = alignment[i - 1][j] - penalty;
            int letterSecond =  alignment[i][j - 1] - penalty;
            int mx = max3(letterFirst, letterSecond, lettersBoth);
            alignment[i][j] = mx;
            if (lettersBoth == mx) {
                previous[i][j] = make_pair(i - 1, j - 1);
            }
            if (letterFirst == mx) {
                previous[i][j] = make_pair(i - 1, j);
            }
            if (letterSecond == mx) {
                previous[i][j] = make_pair(i, j - 1);
            }
        }
    }
    cout << alignment[n][m] << '\n';
    string first, second;
    for (int i = n, j = m;  i != stop && j != stop;) {
        int nexti = previous[i][j].first;
        int nextj = previous[i][j].second;
        if (nexti == i - 1 && nextj == j - 1) {
            first.push_back(s1[i - 1]);
            second.push_back(s2[j - 1]);
        }
        if (nexti == i - 1 && nextj == j) {
            first.push_back(s1[i - 1]);
            second.push_back('-');
        }
        if (nexti == i && nextj == j - 1) {
            first.push_back('-');
            second.push_back(s2[j - 1]);
        }
        j = nextj;
        i = nexti;
    }
    reverse(first.begin(), first.end());
    reverse(second.begin(), second.end());
    cout << first << '\n' << second;

}