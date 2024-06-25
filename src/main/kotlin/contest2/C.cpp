#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>
#include <utility>

using namespace std;

class ParityDsu {
public:
    ParityDsu(int size);
    pair<int, int> find(int n);
    bool unite(int n, int m);

private:
    vector<int> parent;
    vector<int> parity;
};

ParityDsu::ParityDsu(int size) : parent(size), parity(size) {
    for (int i = 0; i < size; ++i) {
        parent[i] = i;
    }
}

pair<int, int> ParityDsu::find(int n) {
    if (parent[n] != n) {
        int p = parity[n];
        auto result = find(parent[n]);
        parent[n] = result.first;
        parity[n] = result.second ^ p;
    }
    return {parent[n], parity[n]};
}

bool ParityDsu::unite(int n, int m) {
    int pn, pm;
    tie(n, pn) = find(n);
    tie(m, pm) = find(m);
    if (n == m) {
        return pn != pm;
    }
    if (rand() % 2 == 0) {
        swap(n, m);
    }
    parent[n] = m;
    parity[n] = pn ^ pm ^ 1;
    return true;
}

int main() {
    string input;
    getline(cin, input);
    istringstream iss(input);
    int vCnt, eCnt;
    iss >> vCnt >> eCnt;

    int maxBipartite = 0;
    ParityDsu cdsu(vCnt);
    for (int i = 0; i < eCnt; ++i) {
        getline(cin, input);
        istringstream edgeStream(input);
        int v1, v2;
        edgeStream >> v1 >> v2;
        bool isBipartite = cdsu.unite(v1 - 1, v2 - 1);
        if (!isBipartite) {
            break;
        }
        maxBipartite++;
    }

    cout << string(maxBipartite, '1') + string(eCnt - maxBipartite, '0') << endl;

    return 0;
}
