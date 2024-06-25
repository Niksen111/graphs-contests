#include <bits/stdc++.h>
using namespace std;

void dfs(int v, bool left, vector<bool>& visitedLeft, vector<bool>& visitedRight, const vector<vector<int>>& edgesLeft, const vector<vector<int>>& edgesRight) {
    if (left) {
        visitedLeft[v] = true;
        for (int u : edgesLeft[v]) {
            if (!visitedRight[u]) {
                dfs(u, !left, visitedLeft, visitedRight, edgesLeft, edgesRight);
            }
        }
    } else {
        visitedRight[v] = true;
        for (int u : edgesRight[v]) {
            if (!visitedLeft[u]) {
                dfs(u, !left, visitedLeft, visitedRight, edgesLeft, edgesRight);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int vCntLeft, vCntRight;
    cin >> vCntLeft >> vCntRight;
    cin.ignore();

    vector<vector<int>> edgesLeft(vCntLeft);
    for (int vLeft = 0; vLeft < vCntLeft; ++vLeft) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        int dummy, vRight;
        ss >> dummy;
        while (ss >> vRight) {
            edgesLeft[vLeft].push_back(vRight - 1);
        }
    }

    vector<int> matching(vCntLeft);
    vector<vector<int>> edgesRight(vCntRight);
    for (int vLeft = 0; vLeft < vCntLeft; ++vLeft) {
        int vRight;
        cin >> vRight;
        matching[vLeft] = vRight - 1;
        if (vRight - 1 >= 0) {
            edgesRight[vRight - 1].push_back(vLeft);
            auto& edges = edgesLeft[vLeft];
            edges.erase(remove(edges.begin(), edges.end(), vRight - 1), edges.end());
        }
    }

    vector<bool> visitedLeft(vCntLeft, false), visitedRight(vCntRight, false);
    for (int v = 0; v < vCntLeft; ++v) {
        if (matching[v] == -1 && !visitedLeft[v]) {
            dfs(v, true, visitedLeft, visitedRight, edgesLeft, edgesRight);
        }
    }

    vector<int> minLeft, minRight;
    for (int v = 0; v < vCntLeft; ++v) {
        if (!visitedLeft[v]) {
            minLeft.push_back(v + 1);
        }
    }
    for (int v = 0; v < vCntRight; ++v) {
        if (visitedRight[v]) {
            minRight.push_back(v + 1);
        }
    }

    cout << minLeft.size() + minRight.size() << '\n';
    cout << minLeft.size() << ' ';
    for (int v : minLeft) cout << v << ' ';
    cout << '\n';
    cout << minRight.size() << ' ';
    for (int v : minRight) cout << v << ' ';
    cout << '\n';

    return 0;
}