#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    long long weight;
    Edge(int t, long long w) : to(t), weight(w) {}
};

vector<long long> dijkstra(int start, int n, const vector<vector<Edge>>& adj, vector<int>& parent) {
    vector<long long> dist(n, numeric_limits<long long>::max());
    dist[start] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (const Edge& edge : adj[u]) {
            int v = edge.to;
            long long weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
                parent[v] = u;
            }
        }
    }

    return dist;
}

vector<int> getPath(int start, int end, const vector<int>& parent) {
    vector<int> path;
    for (int v = end; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    if (path[0] != start) {
        return {}; // path does not exist
    }
    return path;
}

int main() {
    int n, m;
    cin >> n >> m;
    int s, f;
    cin >> s >> f;
    s--; f--;

    vector<vector<Edge>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    vector<int> parent(n, -1);
    vector<long long> dist = dijkstra(s, n, adj, parent);

    if (dist[f] == numeric_limits<long long>::max()) {
        cout << -1 << endl;
    } else {
        cout << dist[f] << endl;
        vector<int> path = getPath(s, f, parent);
        for (int v : path) {
            cout << (v + 1) << " ";
        }
        cout << endl;
    }

    return 0;
}