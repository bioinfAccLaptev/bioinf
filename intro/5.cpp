#include <iostream>
#include <algorithm>
#include <vector>


void generate(int n, std::vector<int> &permutation, int size){
    if (n == 0) {
        for (int i : permutation) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
    } else {
        for (int i = size - n; i < size; i++)  {
            std::swap(permutation[size - n], permutation[i]);
            generate(n - 1, permutation, size);
            std::swap(permutation[size - n], permutation[i]);
        }
    }
}


int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = i + 1;
    generate(n, a, n);
;};