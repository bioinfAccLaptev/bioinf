#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void read(int &n, vector<vector<int>> &matrix) {
    cin >> n;
    matrix.assign(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
}

int limb(vector<vector<int>> &matrix, int i) {
    int ans = INT32_MAX;
    for (int j = 0; j < matrix.size(); j++) {
        for (int k = 0; k < matrix.size(); k++) {
            if (i != k && i != j && k != j) {
                ans = min(ans, (matrix[i][j] + matrix[i][k] - matrix[j][k]) / 2);
            }
        }
    }
    return ans;
}

pair<int,int> find(int &n, vector<vector<int>> &matrix) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (matrix[i][j] == matrix[i][n - 1] + matrix[j][n - 1]) {
                return {i, j};
            }
        }
    }
    //cant be
    return {-1,-1};
}

bool findPath(int v, int end, vector<int> &used, vector<vector<pair<int,int>>> tree, vector<pair<int,int>> &path, int d) {
    used[v] = 1;
    if (v == end) {
        path.emplace_back(v, d);
        return true;
    }
    bool ok = false;
    for (pair<int,int> u : tree[v]) {
        if (!used[u.first]) {
            if (findPath(u.first, end, used, tree, path, u.second)) {
                ok = true;
                break;
            }
        }
    }
    if (ok) {
        path.emplace_back(v, d);
        return true;
    }
    return false;
}


int addVertex(vector<pair<int,int>> &p, int x, vector<vector<pair<int,int>>> &t) {
    int distance = 0;
    int v = -1;
    for (int i = 1; i < p.size(); i++) {
        pair<int,int> current = p[i];
        distance += current.second;
        if (distance > x) {
            pair<int,int> previous = p[i - 1];
            int y =(int) t.size();
            t.emplace_back();
            for (auto &u : t[current.first]) {
                if (u.first == previous.first) {
                    u = {y, distance - x};
                    t[y].push_back({current.first, distance - x});
                }
            }
            for (auto &u : t[previous.first]) {
                if (u.first == current.first) {
                    u = {y, x - distance + current.second};
                    t[y].push_back({p[i - 1].first,  x - distance + current.second});
                }
            }
            v = y;
            break;
        }
        if (distance == x) {
            v = current.first;
            break;
        }
    }
    return v;
}

vector<vector<pair<int,int>>> additivePhylogeny(int n, vector<vector<int>> &matrix, int nfirst) {
    if (n == 2) {
        vector<vector<pair<int,int>>> tree(nfirst, vector<pair<int,int>>(0));
        tree[0].push_back({1, matrix[0][1]});
        tree[1].push_back({0, matrix[0][1]});
        return tree;
    }
    int limbLen = limb(matrix, n - 1);
    for (int i = 0; i < n - 1; i++){
        matrix[i][n - 1] -= limbLen;
        matrix[n - 1][i] = matrix[i][n - 1];
    }
    pair<int,int> ij = find(n, matrix);
    int needDistance = matrix[ij.first][n - 1];
    vector<vector<int>> newMatrix(n - 1, vector<int>(n - 1));
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    auto tree = additivePhylogeny(n - 1, newMatrix, nfirst);
    vector<pair<int,int>> path;
    vector<int> used(tree.size(), 0);
    findPath(ij.first, ij.second, used, tree, path, 0);
    reverse(path.begin(), path.end());
    int v = addVertex(path, needDistance , tree);
    tree[n - 1].push_back({v, limbLen});
    tree[v].push_back({n - 1, limbLen});
    return tree;
}



int main() {
    freopen("C:/C++/CodeForces/out.txt", "w", stdout);
    freopen("C:/C++/CodeForces/in.txt", "r", stdin);
    int n;
    vector<vector<int>> matrix;
    read(n, matrix);
    auto t = additivePhylogeny(n, matrix, n);
    for (int i = 0; i < t.size(); i++) {
        for (auto u : t[i]) {
            cout << i << "->" << u.first << ":" << u.second << '\n';
        }
    }


}