#include <iostream>



int main() {
    std::string s;
    std::cin >> s;
    int a = 0, c = 0, g = 0, t = 0;
    for (char ch : s) {
        switch (ch) {
            case 'A':
                a++;
                break;
            case 'C':
                c++;
                break;
            case 'G':
                g++;
                break;
            case 'T':
                t++;
                break;
            default:
                break;
        }
    }
    std::cout << a << ' ' << c << ' ' << g << ' ' << t << '\n';
};
