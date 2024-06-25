#include <bits/stdc++.h>
using namespace std;

int valence(char atom) {
    switch (atom) {
        case 'H': return 1;
        case 'O': return 2;
        case 'N': return 3;
        case 'C': return 4;
        default: return 0;
    }
}

struct Edge {
    int to, cap;
};

struct Graph {
    int h, w, vCnt, fromSource, toSink, maxFlow;
    vector<vector<Edge>> edges;
    vector<bool> visited;

    Graph(int h, int w) : h(h), w(w), fromSource(0), toSink(0), maxFlow(0) {
        vCnt = h * w + 2;
        edges.resize(vCnt);
        visited.resize(vCnt);
    }

    void initWithValences(vector<vector<char>>& paper) {
        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                int val = valence(paper[r][c]);
                if (c % 2 == r % 2) {
                    addEdge(0, getIdx(r, c), val);
                    fromSource += val;
                    if (r + 1 < h) addEdge(getIdx(r, c), getIdx(r + 1, c), 1);
                    if (c + 1 < w) addEdge(getIdx(r, c), getIdx(r, c + 1), 1);
                    if (r - 1 >= 0) addEdge(getIdx(r, c), getIdx(r - 1, c), 1);
                    if (c - 1 >= 0) addEdge(getIdx(r, c), getIdx(r, c - 1), 1);
                } else {
                    addEdge(getIdx(r, c), vCnt - 1, val);
                    toSink += val;
                }
            }
        }
    }

    int getIdx(int r, int c) {
        return r * w + c + 1;
    }

    void addEdge(int from, int to, int capacity) {
        edges[from].push_back({to, capacity});
    }

    int pushFlow(int v, int flow) {
        visited[v] = true;
        if (v == vCnt - 1 || flow == 0) {
            maxFlow += flow;
            return flow;
        }

        for (auto& edge : edges[v]) {
            if (visited[edge.to] || edge.cap == 0) continue;
            int minCapacity = pushFlow(edge.to, min(flow, edge.cap));
            if (minCapacity > 0) {
                edge.cap -= minCapacity;
                bool found = false;
                for (auto& backEdge : edges[edge.to]) {
                    if (backEdge.to == v) {
                        backEdge.cap += minCapacity;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    edges[edge.to].push_back({v, minCapacity});
                }
                return minCapacity;
            }
        }
        return 0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w;
    cin >> h >> w;
    vector<vector<char>> paper(h, vector<char>(w));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cin >> paper[i][j];
        }
    }

    Graph g(h, w);
    g.initWithValences(paper);

    while (g.pushFlow(0, 5) > 0) {
        fill(g.visited.begin(), g.visited.end(), false);
    }

    if (g.fromSource == g.maxFlow && g.toSink == g.maxFlow && g.maxFlow > 0) {
        cout << "Valid\n";
    } else {
        cout << "Invalid\n";
    }

    return 0;
}