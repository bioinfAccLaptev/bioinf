#include <iostream>
#include <vector>


using namespace std;

int main() {
    freopen("C:/C++/CodeForces/out.txt", "w", stdout);
    freopen("C:/C++/CodeForces/in.txt", "r", stdin);
    string s;
    getline(cin, s);
    vector<int> permutation(1, 0);
    for (int i = 1; i < s.size(); i++) {
        string number;
        while (i < s.size() && s[i] != ' ') {
            number.push_back(s[i]);
            i++;
        }
        permutation.push_back(stoi(number));
    }
    int numberOfBreakpoints = 0;
    for (int i = 1; i < permutation.size(); i++) {
        if (permutation[i] - permutation[i - 1] != 1) {
            numberOfBreakpoints++;
        }
    }
    cout << numberOfBreakpoints;
}