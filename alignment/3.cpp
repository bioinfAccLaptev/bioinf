#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int penaltyStart = 11;
const int penalty = 1;
const int INF = 10000000;

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
struct go {
    int i;
    int j;
    int which;
};


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
    vector<vector<int>> bothLetter(n + 1, vector(m + 1, 0));
    vector<vector<int>> firstLetter(n + 1, vector(m + 1, 0));
    vector<vector<int>> secondLetter(n + 1, vector(m + 1, 0));
    vector<vector<go>> previousBoth(n + 1, vector<go>(m + 1));
    vector<vector<go>> previousFirst(n + 1, vector<go>(m + 1));
    vector<vector<go>> previousSecond(n + 1, vector<go>(m + 1));
    for (int i = 1; i <= n; i++){
        firstLetter[i][0] = -penaltyStart + (i - 1) * penalty;
        secondLetter[i][0] = -penaltyStart + (i - 1) * penalty;
        bothLetter[i][0] = -INF;
        previousFirst[i][0] = {0,0,0};
        previousSecond[i][0] = {0,0,0};
    }
    for (int i = 1; i <= m; i++) {
        firstLetter[0][i] = -penaltyStart - (i - 1) * penalty;
        secondLetter[0][i] = -penaltyStart - (i - 1) * penalty;
        bothLetter[0][i] = -INF;
        previousFirst[0][i] = {0,0,0};
        previousSecond[0][i] = {0,0,0};
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            bothLetter[i][j] = max3(firstLetter[i - 1][j - 1], secondLetter[i - 1][j - 1], bothLetter[i - 1][j - 1]);
            if (bothLetter[i][j] == firstLetter[i - 1][j - 1]) {
                previousBoth[i][j] = {i - 1, j - 1, 1};
            }
            if (bothLetter[i][j] == secondLetter[i - 1][j - 1]) {
                previousBoth[i][j] = {i - 1, j - 1, 2};
            }
            if (bothLetter[i][j] == bothLetter[i - 1][j - 1]) {
                previousBoth[i][j] = {i - 1, j - 1, 0};
            }
            bothLetter[i][j] += cost[charToInt[s1[i - 1]]][charToInt[s2[j - 1]]];

            firstLetter[i][j] = max3(bothLetter[i - 1][j] - penaltyStart, firstLetter[i - 1][j] - penalty, secondLetter[i - 1][j] - penaltyStart);
            if (firstLetter[i][j] == bothLetter[i - 1][j] - penaltyStart) {
                previousFirst[i][j] = {i - 1, j, 0};
            }
            if (firstLetter[i][j] == firstLetter[i - 1][j] - penalty) {
                previousFirst[i][j] = {i - 1, j, 1};
            }
            if (firstLetter[i][j] == secondLetter[i - 1][j] - penaltyStart) {
                previousFirst[i][j] = {i - 1, j , 2};
            }

            secondLetter[i][j] = max3(bothLetter[i][j - 1] - penaltyStart, firstLetter[i][j - 1] - penaltyStart, secondLetter[i][j - 1] - penalty);
            if (secondLetter[i][j] == bothLetter[i][j - 1] - penaltyStart) {
                previousSecond[i][j] = {i, j - 1 , 0};
            }
            if (secondLetter[i][j] == firstLetter[i][j - 1] - penaltyStart) {
                previousSecond[i][j] = {i, j - 1 , 1};
            }
            if (secondLetter[i][j] == secondLetter[i][j - 1] - penalty) {
                previousSecond[i][j] = {i, j - 1 , 2};
            }
        }
    }
    cout << max3(bothLetter[n][m], firstLetter[n][m], secondLetter[n][m]) << '\n';
    int start = -1;
    if (max3(bothLetter[n][m], firstLetter[n][m], secondLetter[n][m]) == bothLetter[n][m])  {
        start = 0;
    }
    if (max3(bothLetter[n][m], firstLetter[n][m], secondLetter[n][m]) == firstLetter[n][m])  {
        start = 1;
    }
    if (max3(bothLetter[n][m], firstLetter[n][m], secondLetter[n][m]) == secondLetter[n][m])  {
        start = 2;
    }
    string first;
    string second;
    for (int i = n, j = m, which = start; i != 0 && j != 0 && m != 0;) {
        int nexti;
        int nextj;
        int nextWhich;
        if (which == 0) {
            nexti = previousBoth[i][j].i;
            nextj = previousBoth[i][j].j;
            nextWhich = previousBoth[i][j].which;
            first.push_back(s1[i - 1]);
            second.push_back(s2[j - 1]);
        }
        if (which == 1) {
            nexti = previousFirst[i][j].i;
            nextj = previousFirst[i][j].j;
            nextWhich = previousFirst[i][j].which;
            first.push_back(s1[i - 1]);
            second.push_back('-');

        }
        if (which == 2) {
            nexti = previousSecond[i][j].i;
            nextj = previousSecond[i][j].j;
            nextWhich = previousSecond[i][j].which;
            first.push_back('-');
            second.push_back(s2[j - 1]);
        }
        which = nextWhich;
        i = nexti;
        j = nextj;
    }
    reverse(first.begin(), first.end());
    reverse(second.begin(), second.end());
    cout << first << '\n' << second;
}