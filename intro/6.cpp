#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <deque>
#include <queue>
#include <cassert>
#include <stack>
using namespace std;





int main() {
    unsigned long long n, k;
    cin >> n >> k;
    unsigned long long previous = 1, current = 1;
    for (int i = 2; i < n; i++) {
        unsigned long long t = current;
        current = current + previous * k;
        previous = t;
    }
    cout << current;

}