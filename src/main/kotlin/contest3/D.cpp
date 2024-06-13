#include <iostream>
#include <vector>
#include <tuple>
#include <limits>
#include <queue>

using namespace std;

struct Edge {
    int from, to, weight;
};

const int INF = 1e9;

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].from >> edges[i].to >> edges[i].weight;
    }

    vector<int> dist(n + 1, -INF);
    dist[1] = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (const auto& edge : edges) {
            if (dist[edge.from] != -INF && dist[edge.from] + edge.weight > dist[edge.to]) {
                dist[edge.to] = dist[edge.from] + edge.weight;
            }
        }
    }

    vector<bool> inQueue(n + 1, false);
    queue<int> q;
    for (int i = 0; i < m; ++i) {
        if (dist[edges[i].from] != -INF && dist[edges[i].from] + edges[i].weight > dist[edges[i].to]) {
            q.push(edges[i].to);
            inQueue[edges[i].to] = true;
        }
    }

    vector<bool> reachable(n + 1, false);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        reachable[u] = true;
        for (const auto& edge : edges) {
            if (edge.from == u && !inQueue[edge.to]) {
                q.push(edge.to);
                inQueue[edge.to] = true;
            }
        }
    }

    if (reachable[n]) {
        cout << ":)" << endl;
    } else if (dist[n] == -INF) {
        cout << ":(" << endl;
    } else {
        cout << dist[n] << endl;
    }

    return 0;
}