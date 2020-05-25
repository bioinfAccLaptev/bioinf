#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;


int max(vector<int> &a) {
    int mx = INT32_MIN;
    for (int i : a) {
        mx = max(mx, i);
    }
    return mx;
}



int main() {
    freopen("C:/C++/CodeForces/out.txt", "w", stdout);
    freopen("C:/C++/CodeForces/in.txt", "r", stdin);
    string s1;
    string s2;
    string s3;
    cin >> s1 >> s2 >> s3;
    int n1 = (int) s1.size();
    int n2 = (int) s2.size();
    int n3 = (int) s3.size();
    vector<vector<vector<int>>> alignment(n1 + 1, vector<vector<int>>(n2 + 1, vector<int>(n3 + 1, 0)));
    vector<vector<vector<int>>> previous(n1 + 1, vector<vector<int>>(n2 + 1, vector<int>(n3 + 1, 0)));


    for (int i = 1; i <= n1; i++) {
        for (int j = 1; j <= n2; j++) {
            for (int k = 1; k <= n3; k++){
                int add = (s1[i - 1] == s2[j - 1] && s1[i - 1] == s3[k - 1]);
                int mx = max({alignment[i - 1][j - 1][k - 1] + add, alignment[i - 1][j - 1][k], alignment[i - 1][j][k - 1], alignment[i][j - 1][k - 1],
                              alignment[i - 1][j][k], alignment[i][j - 1][k], alignment[i][j][k - 1]});
                alignment[i][j][k] = mx;
            }
        }
    }
    cout << alignment[n1][n2][n3] << '\n';
    string first, second, third;
    for (int i = n1, j = n2, k = n3; k != 0 || j != 0 || i != 0;) {
        int current = alignment[i][j][k];
        int add =(s1[i - 1] == s2[j - 1] && s1[i - 1] == s3[k - 1]);
        if (i > 0 && j > 0 && k > 0 && current == alignment[i - 1][j - 1][k - 1] + add) {
            first.push_back(s1[i - 1]);
            second.push_back(s2[j - 1]);
            third.push_back(s3[k - 1]);
            i--; j--; k--;
            continue;
        }
        if (i > 0 && j > 0 && current == alignment[i - 1][j - 1][k]) {
            first.push_back(s1[i - 1]);
            second.push_back(s2[j - 1]);
            third.push_back('-');
            i--; j--;
            continue;
        }
        if (i > 0 && k > 0 && current == alignment[i - 1][j][k - 1]) {
            first.push_back(s1[i - 1]);
            second.push_back('-');
            third.push_back(s3[k - 1]);
            i--; k--;
            continue;
        }
        if (j > 0 && k > 0 && current == alignment[i][j - 1][k - 1]) {
            first.push_back('-');
            second.push_back(s2[j - 1]);
            third.push_back(s3[k - 1]);
            k--; j--;
            continue;
        }
        if (i > 0 && current == alignment[i - 1][j][k]) {
            first.push_back(s1[i - 1]);
            second.push_back('-');
            third.push_back('-');
            i--;
            continue;
        }
        if (j > 0 && current == alignment[i][j - 1][k]) {
            first.push_back('-');
            second.push_back(s2[j - 1]);
            third.push_back('-');
            j--;
            continue;
        }
        if (k > 0 && current == alignment[i][j][k - 1]) {
            first.push_back('-');
            second.push_back('-');
            third.push_back(s3[k - 1]);
            k--;
            continue;
        }
    }
    reverse(first.begin(), first.end());
    reverse(second.begin(), second.end());
    reverse(third.begin(), third.end());
    cout << first << '\n' << second << '\n' << third;
}