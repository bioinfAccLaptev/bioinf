#include <iostream>
#include <algorithm>


int main() {
    std::string s;
    std::cin >> s;
    int a = 0, c = 0, g = 0, t = 0;
    for (char &ch : s) {
        switch (ch) {
            case 'A':
                ch = 'T';
                break;
            case 'C':
                ch = 'G';
                break;
            case 'G':
                ch = 'C';
                break;
            case 'T':
                ch = 'A';
                break;
            default:
                break;
        }
    }
    reverse(s.begin(), s.end());
    std::cout << s;
};