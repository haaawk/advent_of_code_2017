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

vector<char> run(int x, int y, int dir, vector<string>& g) {
    vector<char> res;
    do {
        char& curr = g[x][y];
        if (curr >= 'A' && curr <= 'Z') {
            res.push_back(curr);
        }
    } while (walk(g, x, y, dir, 0) || walk(g, x, y, dir, 1) || walk(g, x, y, dir, 3));
    return std::move(res);
}

int main() {
    vector<string> g;
    string line;
    while (getline(cin, line)) {
        g.push_back(line);
    }
    vector<char> res = run(0, g[0].find("|"), 2, g);
    for (char x : res)
        cout << x;
    cout << endl;
    return 0;
}
