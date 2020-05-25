#include <iostream>



int main() {
    std::string s;
    std::cin >> s;
    for (char &ch : s) {
        if (ch == 'T') {
            ch = 'U';
        }
    }
    std::cout << s;
};
