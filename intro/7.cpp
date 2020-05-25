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
    string ans = "";
    double p = 0;
    string s , st;
    in >> st;
    long long sz = 0;
    long long c  = 0;
    while (in >> s) {
        cout << s << '\n';
        if (s[0] == '>') {
            double cp = (double) c / (double) sz;
            if (cp > p) {
                p = cp;
                ans = st;
            }
            c = 0;
            sz = 0;
            st = s;
        } else {
            sz += s.size();
            for (char i : s) {
                if (i =='C' || i == 'G') c++;
            }
        }
    }
    double cp = (double) c / (double) sz;
    if (cp > p) {
        p = cp;
        ans = st;
    }
    cout << ans << '\n';
    cout << p * 100;


}