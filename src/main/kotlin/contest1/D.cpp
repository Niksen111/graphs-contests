#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const tuple<char, char, char> moves[] = {
        {'R', 0, 1},
        {'U', -1, 0},
        {'D', 1, 0},
        {'L', 0, -1}
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, k; cin >> n >> m >> k;
    int bound = 2 * (n * m - k);

    vector<tuple<char, char, char, char, char, char, char>> movingWalls;
    movingWalls.reserve(k);
    vector<vector<int>> stableWalls(n + 1, vector<int>(m + 1, 0));
    vector<vector<int>> turtle(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i < k; ++i) {
        int sx, sy, fx, fy, t;
        cin >> sx >> sy >> fx >> fy >> t;

        if (t == 0 || sx == fx && sy == fy) {
            for (int x = min(sx, fx); x <= max(sx, fx); ++x) {
                for (int y = min(sy, fy); y <= max(sy, fy); ++y) {
                    stableWalls[x][y] += 1;
                }
            }
            continue;
        }

        stableWalls[sx][sy] += 1;
        movingWalls.emplace_back(sx, sy, sx, sy, fx, fy, t);
    }

    turtle[1][1] = 1;
    ll time = 1;

    queue<pair<char, char>> bfs({{1, 1}});
    vector<vector<vector<pair<char, char>>>> ans(n + 1, vector<vector<pair<char, char>>>(m + 1,vector<pair<char, char>>(bound + 1)));

    while (time < bound) {
        for (auto& [cx, cy, sx, sy, fx, fy, t] : movingWalls) {
            if (time % t) continue;

            if (cx == fx && cy == fy) {
                swap(sx, fx);
                swap(sy, fy);
            }

            stableWalls[cx][cy] -= 1;
            if (sx == fx) cy += (fy - cy) / abs(fy - cy);
            else cx += (fx - cx) / abs(fx - cx);
            stableWalls[cx][cy] += 1;
        }

        int cnt = bfs.size();
        while (cnt--) {
            auto [x, y] = bfs.front();
            bfs.pop();

            if (x == n && y == m) {
                string result;
                result.reserve(time);
                char a = x, b = y;
                while (time > 1) {
                    char next = 'W';
                    auto [nx, ny] = ans[a][b][time - 1];
                    for (const auto &[name, dx, dy]: moves) {
                        if (nx + dx == a && ny + dy == b) {
                            next = name;
                            a = nx;
                            b = ny;
                            break;
                        }
                    }
                    --time;
                    result.push_back(next);
                }
                reverse(result.begin(), result.end());
                cout << result << '\n';
                return 0;
            }

            for (const auto &[name, dx, dy]: moves) {
                if (x + dx <= 0 || x + dx > n || y + dy <= 0 || y + dy > m || stableWalls[x + dx][y + dy] || turtle[x + dx][y + dy]) continue;
                turtle[x + dx][y + dy] = 1;
                ans[x + dx][y + dy][time] = {x, y};
                bfs.emplace(x + dx, y + dy);
            }

            if (stableWalls[x][y] != 0 || turtle[x][y] != 1) {
                ans[x][y].clear();
                --turtle[x][y];
            } else {
                ans[x][y][time] = {x, y};
                bfs.emplace(x, y);
            }
        }
        ++time;
    }

    cout << "N\n";

    return 0;
}