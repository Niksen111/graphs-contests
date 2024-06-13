#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

struct Edge {
    int from, to, capacity, cost, flow;
    Edge(int f, int t, int c, int co) : from(f), to(t), capacity(c), cost(co), flow(0) {}
};

class MinCostMaxFlow {
    int n;
    vector<vector<int>> adj;
    vector<Edge> edges;
    vector<int> dist, parent, parentEdge;
    vector<bool> inQueue;

public:
    MinCostMaxFlow(int n) : n(n), adj(n), dist(n), parent(n), parentEdge(n), inQueue(n) {}

    void addEdge(int from, int to, int capacity, int cost) {
        adj[from].push_back(edges.size());
        edges.emplace_back(from, to, capacity, cost);
        adj[to].push_back(edges.size());
        edges.emplace_back(to, from, 0, -cost);
    }

private:
    bool spfa(int s, int t) {
        fill(dist.begin(), dist.end(), numeric_limits<int>::max());
        fill(inQueue.begin(), inQueue.end(), false);
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        inQueue[s] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inQueue[u] = false;

            for (int i : adj[u]) {
                Edge &e = edges[i];
                if (e.flow < e.capacity && dist[u] + e.cost < dist[e.to]) {
                    dist[e.to] = dist[u] + e.cost;
                    parent[e.to] = u;
                    parentEdge[e.to] = i;
                    if (!inQueue[e.to]) {
                        q.push(e.to);
                        inQueue[e.to] = true;
                    }
                }
            }
        }

        return dist[t] != numeric_limits<int>::max();
    }

public:
    long long minCostMaxFlow(int s, int t) {
        long long flow = 0, cost = 0;

        while (spfa(s, t)) {
            int pathFlow = numeric_limits<int>::max();
            for (int v = t; v != s; v = parent[v]) {
                int i = parentEdge[v];
                pathFlow = min(pathFlow, edges[i].capacity - edges[i].flow);
            }

            for (int v = t; v != s; v = parent[v]) {
                int i = parentEdge[v];
                edges[i].flow += pathFlow;
                edges[i ^ 1].flow -= pathFlow;
                cost += static_cast<long long>(pathFlow) * edges[i].cost;
            }

            flow += pathFlow;
        }

        return cost;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    MinCostMaxFlow minCostMaxFlow(n);

    for (int i = 0; i < m; ++i) {
        int from, to, capacity, cost;
        cin >> from >> to >> capacity >> cost;
        minCostMaxFlow.addEdge(from - 1, to - 1, capacity, cost);
    }

    int s = 0, t = n - 1;
    long long minCost = minCostMaxFlow.minCostMaxFlow(s, t);

    cout << minCost << endl;

    return 0;
}
