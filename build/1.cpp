#include <iostream>
#include <vector>


using namespace std;

void reverse(vector<int> &a, int l, int r) {
    for (int i = l; i <= (l + r) / 2; i++) {
        a[i] = -a[i];
        if (r + l - i != i) {
            a[r + l - i] = -a[r + l - i];
        }
        swap(a[i], a[r + l - i]);
    }
}

void print(vector<int> &a) {
    cout << '(';
    for (int i = 0; i < a.size(); i++) {
        if (a[i] >= 0) {
            cout << '+';
        }
        cout << a[i];
        if (i != (int) a.size() - 1) {
           cout << ' ';
        } else {
            cout << ")\n";
        }
    }
}

int main() {
    freopen("C:/C++/CodeForces/out.txt", "w", stdout);
    freopen("C:/C++/CodeForces/in.txt", "r", stdin);
    string s;
    getline(cin, s);
    vector<int> permutation;
    for (int i = 1; i < s.size(); i++) {
        string number;
        while (i < s.size() && s[i] != ' ') {
            number.push_back(s[i]);
            i++;
        }
        permutation.push_back(stoi(number));
    }
    for (int number = 1; number <= permutation.size(); number++) {
        for (int i = 0; i < permutation.size(); i++) {
            if (abs(permutation[i]) == number) {
                if (i != number - 1) {
                    reverse(permutation, number - 1, i);
                    print(permutation);
                }
                if (permutation[number - 1] < 0) {
                    reverse(permutation, number - 1, number - 1);
                    print(permutation);
                }
            }
        }
    }
}