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
    string s, t;
    cin >> s >> t;
    for (int i = 0; i < s.size() - t.size(); i++) {
        bool next = false;
        for (int j = i; j < t.size() + i; j++) {
            if (s[j] != t[j - i]) {
                next = true;
                break;
            }
        }
        if (next) continue;
        cout << i + 1 << ' ';
    }
}