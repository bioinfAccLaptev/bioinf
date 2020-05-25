#include <iostream>
#include <algorithm>


int main() {
    std::string s;
    std::string t;
    std::cin >> s >> t;
    int ans = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != t[i]) {
            ans++;
        }
    }
    std::cout << ans;
};