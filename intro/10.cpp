#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <deque>
#include <queue>
#include <cassert>
#include <fstream>
#include <stack>
#include <iomanip>

using namespace std;



int main() {
    ifstream in("C:/C++/CodeForces/a.txt");
    map<char,double> mp;
    char c; double d;
    while (in >> c >> d) {
        mp[c] = d;
    }
    string s;
    cin >> s;
    double ans = 0;
    for (char i : s) {
        ans += mp[i];
    }
    cout << fixed << setprecision(4) << ans;
}