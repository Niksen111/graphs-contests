#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <iomanip>
#include <limits>

struct City {
    int x, y;
};

double distance(const City& city1, const City& city2) {
    double dx = city1.x - city2.x;
    double dy = city1.y - city2.y;
    return dx * dx + dy * dy;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<City> cities(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> cities[i].x >> cities[i].y;
    }

    std::vector<double> minDist(n, std::numeric_limits<double>::infinity());
    std::vector<bool> visited(n, false);
    minDist[0] = 0.0;

    auto compare = [](const std::pair<double, int>& a, const std::pair<double, int>& b) {
        return a.first > b.first;
    };
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, decltype(compare)> minHeap(compare);
    minHeap.emplace(0.0, 0);

    double mstCost = 0.0;
    int usedNodes = 0;

    while (usedNodes < n) {
        auto [curDist, u] = minHeap.top();
        minHeap.pop();

        if (visited[u]) continue;
        visited[u] = true;
        mstCost += std::sqrt(curDist);
        usedNodes++;

        for (int v = 1; v < n; ++v) {
            if (!visited[v]) {
                double dist = distance(cities[u], cities[v]);
                if (dist < minDist[v]) {
                    minDist[v] = dist;
                    minHeap.emplace(dist, v);
                }
            }
        }
    }

    std::cout << std::fixed << std::setprecision(10) << mstCost << '\n';

    return 0;
}