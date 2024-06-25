#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

class Parity {
public:
    Parity() = default;
    bool add(int a, int b, bool c);

private:
    std::unordered_map<int, bool> exist;
    std::unordered_map<int, bool> odd;
    std::unordered_map<int, int> prev;
};

bool Parity::add(int a, int b, bool c) {
    if (!exist[b]) {
        exist[b] = true;
        odd[b] = c;
        prev[b] = a;
        return true;
    }
    int i = prev[b];
    if (i == a) {
        return odd[b] == c;
    } else if (i < a) {
        return add(i, a - 1, c != odd[b]);
    }
    return add(a, i - 1, c != odd[b]);
}

int main() {
    std::vector<int> results;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line == "-1") break;

        std::getline(std::cin, line);
        int qCnt = std::stoi(line);

        int lastGood = 0;
        Parity pdsu;

        for (int i = 0; i < qCnt; ++i) {
            std::getline(std::cin, line);
            std::istringstream iss(line);
            int l, r;
            std::string t;
            iss >> l >> r >> t;

            bool ok;
            if (t == "even") {
                ok = pdsu.add(l, r, false);
            } else {
                ok = pdsu.add(l, r, true);
            }

            if (!ok) break;
            lastGood++;
        }

        for (int i = 0; i < qCnt - lastGood - 1; ++i) {
            std::getline(std::cin, line);
        }

        results.push_back(lastGood);
    }

    for (int r : results) {
        std::cout << r << std::endl;
    }

    return 0;
}
