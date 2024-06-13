#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

struct Edge {
    int from, to;
    long long capacity, flow;
    Edge(int f, int t, long long c) : from(f), to(t), capacity(c), flow(0) {}
};

class MaxFlow {
    int n;
    vector<vector<int>> adj;
    vector<Edge> edges;
    vector<int> level, ptr;

public:
    MaxFlow(int n) : n(n), adj(n), level(n), ptr(n) {}

    void addEdge(int from, int to, long long capacity) {
        adj[from].push_back(edges.size());
        edges.emplace_back(from, to, capacity);
        adj[to].push_back(edges.size());
        edges.emplace_back(to, from, 0);
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                Edge& e = edges[id];
                if (e.flow < e.capacity && level[e.to] == -1) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, int t, long long flow) {
        if (!flow) return 0;
        if (v == t) return flow;

        for (int& i = ptr[v]; i < adj[v].size(); ++i) {
            int id = adj[v][i];
            Edge& e = edges[id];
            if (level[e.to] != level[v] + 1 || e.flow == e.capacity)
                continue;
            long long pushed = dfs(e.to, t, min(flow, e.capacity - e.flow));
            if (pushed) {
                e.flow += pushed;
                edges[id ^ 1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    long long maxFlow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, t, numeric_limits<long long>::max())) {
                flow += pushed;
            }
        }
        return flow;
    }

    void printFlows() {
        for (const Edge& e : edges) {
            if (e.capacity > 0) {
                cout << e.flow << endl;
            }
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    MaxFlow maxFlow(n);

    for (int i = 0; i < m; ++i) {
        int from, to;
        long long capacity;
        cin >> from >> to >> capacity;
        maxFlow.addEdge(from - 1, to - 1, capacity);
    }

    long long max_flow = maxFlow.maxFlow(0, n - 1);
    cout << max_flow << endl;
    maxFlow.printFlows();

    return 0;
}
