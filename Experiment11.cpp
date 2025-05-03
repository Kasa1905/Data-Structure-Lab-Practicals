#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int optimalBST(const vector<double>& p, int n) {
    vector<vector<double>> cost(n, vector<double>(n, 0));
    vector<vector<double>> sum(n, vector<double>(n, 0));

    for (int i = 0; i < n; i++) {
        cost[i][i] = p[i];
        sum[i][i] = p[i];
    }

    for (int length = 2; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            int j = i + length - 1;
            sum[i][j] = sum[i][j-1] + p[j];
            cost[i][j] = numeric_limits<double>::max();
            for (int r = i; r <= j; r++) {
                double c = ((r > i) ? cost[i][r-1] : 0) + ((r < j) ? cost[r+1][j] : 0) + sum[i][j];
                if (c < cost[i][j]) {
                    cost[i][j] = c;
                }
            }
        }
    }
    return cost[0][n-1];
}

int main() {
    int n;
    cin >> n;
    vector<double> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    cout << optimalBST(p, n) << endl;
    return 0;
}
