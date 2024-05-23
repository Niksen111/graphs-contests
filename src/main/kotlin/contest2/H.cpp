#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

class DSU {
public:
    DSU(int n) : parent(n), rank(n, 1) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void unite(int u, int v) {
        int root_u = find(u);
        int root_v = find(v);
        if (root_u != root_v) {
            if (rank[root_u] < rank[root_v]) {
                swap(root_u, root_v);
            }
            parent[root_v] = root_u;
            if (rank[root_u] == rank[root_v]) {
                rank[root_u]++;
            }
        }
    }

private:
    vector<int> parent;
    vector<int> rank;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].first >> edges[i].second;
        edges[i].first--;
        edges[i].second--;
    }

    vector<pair<string, pair<int, int>>> operations(k);
    for (int i = 0; i < k; ++i) {
        string type;
        int u, v;
        cin >> type >> u >> v;
        u--; v--;
        operations[i] = {type, {u, v}};
    }

    DSU dsu(n);
    vector<string> results;
    unordered_map<int, unordered_map<int, bool>> edge_cut;

    for (const auto& edge : edges) {
        edge_cut[edge.first][edge.second] = false;
        edge_cut[edge.second][edge.first] = false;
    }

    for (int i = k - 1; i >= 0; --i) {
        const auto& [type, uv] = operations[i];
        int u = uv.first, v = uv.second;
        if (type == "ask") {
            if (dsu.find(u) == dsu.find(v)) {
                results.push_back("YES");
            } else {
                results.push_back("NO");
            }
        } else if (type == "cut") {
            dsu.unite(u, v);
        }
    }

    reverse(results.begin(), results.end());
    for (const auto& result : results) {
        cout << result << '\n';
    }

    return 0;
}