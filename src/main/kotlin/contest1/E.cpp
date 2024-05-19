#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

pair<int, int> bfs(int start, const vector<vector<int>>& graph) {
    int n = graph.size() - 1;
    vector<int> dist(n + 1, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;

    int farthestNode = start;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int neighbor : graph[node]) {
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[node] + 1;
                q.push(neighbor);
                if (dist[neighbor] > dist[farthestNode]) {
                    farthestNode = neighbor;
                }
            }
        }
    }
    return make_pair(farthestNode, dist[farthestNode]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    auto firstBFS = bfs(1, graph);
    auto secondBFS = bfs(firstBFS.first, graph);
    int diameter = secondBFS.second;

    if (diameter >= m) {
        cout << m + 1 << endl;
    } else {
        cout << min(n, diameter + 1 + (m - diameter) / 2) << endl;
    }

    return 0;
}
