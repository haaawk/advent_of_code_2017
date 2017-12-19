#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

bool inside(vector<string>& g, int x, int y) {
    return x > -1 && y > -1 && x < g.size() && y < g[0].size();
}

bool ok(vector<string>& g, int x, int y) {
    return inside(g, x, y) && g[x][y] != ' ';
}

pair<int, int> step(int x, int y, int dir) {
    switch (dir) {
        case 0:
            return make_pair(x - 1, y);
        case 1:
            return make_pair(x, y + 1);
        case 2:
            return make_pair(x + 1, y);
        case 3:
            return make_pair(x, y - 1);
    }
}

bool walk(vector<string>& g, int& x, int& y, int& dir, int turn) {
    int new_dir = (dir + turn) % 4;
    auto [a, b] = step(x, y, new_dir);
    if (ok(g, a, b)) {
        x = a;
        y = b;
        dir = new_dir;
        return true;
    }
    return false;
}

int run(int x, int y, int dir, vector<string>& g) {
    int res = 1;
    while (walk(g, x, y, dir, 0) || walk(g, x, y, dir, 1) || walk(g, x, y, dir, 3))
        ++res;
    return res;
}

int main() {
    vector<string> g;
    string line;
    while (getline(cin, line)) {
        g.push_back(line);
    }
    cout << run(0, g[0].find("|"), 2, g) << endl;
    return 0;
}
