#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

using point = pair<int, int>;

int main() {
    map<point, int> g;
    string line;
    int n;
    int x = 0;
    int y = 0;
    while (getline(cin, line)) {
        for (y = 0; y < line.size(); ++y)
            g[make_pair(x, y)] = (line[y] == '#') ? 2 : 0;
        n = y;
        ++x;
    }
    int m = x;

    x = m / 2;
    y = n / 2;
    int dir = 0;

    int res = 0;
    int steps = 10000000;
    while (steps-- > 0) {
        int& cur = g[make_pair(x, y)];
        dir = (dir + 3 + cur) % 4;
        cur = (cur + 1) % 4;
        res += cur == 2 ? 1 : 0;
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
