#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void read(int &n, vector<vector<double>> &matrix) {
    cin >> n;
    matrix.assign(n, vector<double>(n, 0));
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


vector<double> totalDistance( vector<vector<double>> &matrix){
    vector<double> totalDistance(matrix.size(), 0);
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            totalDistance[i] += matrix[i][j];
        }
    }
    return totalDistance;
}


vector<vector<double>> neighborJoiningMatrix(vector<vector<double>> &matrix) {
    vector<double> totalDist = totalDistance(matrix);
    vector<vector<double>> neighborMatrix(matrix.size(), vector<double>(matrix.size()));
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            neighborMatrix[i][j] = (matrix.size() - 2) * matrix[i][j] - totalDist[i] - totalDist[j];
        }
    }
    return neighborMatrix;
}

pair<int,int> neighborMatrixMin(vector<vector<double>> &neighborMatrix) {
    double min = INT32_MAX;
    int first = -1, second = -1;
    for (int i = 0; i < neighborMatrix.size(); i++) {
        for (int j = 0; j < neighborMatrix.size(); j++) {
            if (i == j) continue;
            if (neighborMatrix[i][j] < min) {
                first = i;
                second = j;
                min = neighborMatrix[i][j];
            }
        }
    }
    return {first, second};
}

vector<vector<double>> newMatrix(vector<vector<double>> &matrix, int first, int second) {
    vector<vector<double>> newMatr(0);

    vector<int> indexInMatrix(matrix.size() - 2);
    int next = 0;
    for (int i = 0; i < matrix.size(); i++) {
        if (i == first || i == second) continue;
        newMatr.emplace_back();
        indexInMatrix[next++] = i;
        for (int j = 0; j  < matrix.size(); j++) {
            if (j == first || j == second) continue;
            newMatr[newMatr.size() - 1].push_back(matrix[i][j]);
        }
    }
    for (int i = 0; i < newMatr.size(); i++) {
        newMatr[i].push_back((matrix[first][indexInMatrix[i]] + matrix[second][indexInMatrix[i]] - matrix[first][second]) / 2);
    }
    newMatr.emplace_back();
    for (int i = 0; i < newMatr.size() - 1; i++) {
        newMatr[(int)newMatr.size() - 1].push_back((matrix[first][indexInMatrix[i]] + matrix[second][indexInMatrix[i]] - matrix[first][second]) / 2);
    }
    newMatr[newMatr.size() - 1].push_back(0);
    return newMatr;
}

vector<vector<pair<int,double>>> neighborJoining(int n, vector<vector<double>> &matrix, int nfirst, int next, vector<int> &index) {
    if (n == 2) {
        vector<vector<pair<int, double>>> tree(max(max(index[0] + 1, index[1] + 1), nfirst + 1), vector<pair<int, double>>(0));
        tree[index[0]].push_back({index[1], matrix[0][1]});
        tree[index[1]].push_back({index[0], matrix[0][1]});
        return tree;
    }
    vector<double> totalDist = totalDistance(matrix);
    auto neighborMatrix = neighborJoiningMatrix(matrix);
    pair<int,int> ij  = neighborMatrixMin(neighborMatrix);
    double delta = (totalDist[ij.first] - totalDist[ij.second]) / (n - 2);
    double limbLenI = (matrix[ij.first][ij.second] + delta) / 2;
    double limbLenJ = (matrix[ij.first][ij.second] - delta) / 2;
    auto m = newMatrix(matrix, ij.first, ij.second);
    vector<int> ind;
    for (int i = 0; i < index.size(); i++) {
        if (ij.first == i || ij.second == i) continue;
        ind.push_back(index[i]);
    }
    ind.push_back(next);
    auto tree = neighborJoining(n - 1, m, nfirst, next + 1, ind);
    tree[index[ij.first]].emplace_back(next, limbLenI);
    tree[index[ij.second]].emplace_back(next, limbLenJ);
    tree[next].emplace_back(index[ij.first], limbLenI);
    tree[next].emplace_back(index[ij.second], limbLenJ);
    return tree;
}



int main() {
    freopen("C:/C++/CodeForces/out.txt", "w", stdout);
    freopen("C:/C++/CodeForces/in.txt", "r", stdin);
    int n;
    vector<vector<double>> matrix;
    read(n, matrix);
    vector<int> index(n);
    for (int i = 0; i < n; i++) index[i] = i;
    auto t = neighborJoining(n, matrix, n, n, index);
    for (int i = 0; i < t.size(); i++) {
        for (auto u : t[i]) {
            cout << i << "->" << u.first << ":" << u.second << '\n';
        }
    }
}