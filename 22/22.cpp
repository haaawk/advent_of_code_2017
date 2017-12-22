#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

using point = pair<int, int>;

int main() {
    map<point, bool> g;
    string line;
    int n;
    int x = 0;
    int y = 0;
    while (getline(cin, line)) {
        for (y = 0; y < line.size(); ++y)
            g[make_pair(x, y)] = (line[y] == '#') ? true : false;
        n = y;
        ++x;
    }
    int m = x;

    x = m / 2;
    y = n / 2;
    int dir = 0;

    int res = 0;
    int steps = 10000;
    while (steps-- > 0) {
        bool& cur = g[make_pair(x, y)];
        dir = (dir + (cur ? 1 : 3)) % 4;
        cur = !cur;
        res += cur ? 1 : 0;
        switch(dir) {
            case 0: --x; break;
            case 1: ++y; break;
            case 2: ++x; break;
            case 3: --y; break;
        }
    }

    cout << res << endl;

    return 0;
}
