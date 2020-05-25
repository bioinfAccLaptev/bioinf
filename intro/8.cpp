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
using namespace std;



int main() {
    ifstream in("C:/C++/CodeForces/a.txt");
    string s;
    map<string,string> mp;
    string s1,s2;
    while (in >> s1 >> s2) {
        mp[s1] = s2;
    }
    cin >> s;
    for (int i = 0; i < s.size(); i+= 3) {
        string t = s.substr(i, 3);
        cout << mp[t];
    }
}