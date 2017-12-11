#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

int distance(int x, int y) {
    x = abs(x);
    y = abs(y);
    int z = min(x, y);
    return z + (max(x, y) - z) / 2;
}

int main() {
    char c1, c2;
    int x = 0;
    int y = 0;
    while (cin >> c1) {
        if (cin >> c2 && c2 != ',') {
            x += c1 == 'n' ? 1 : -1;
            y += c2 == 'e' ? 1 : -1;
            cin.ignore();
            continue;
        }
        x += c1 == 'n' ? 2 : -2;
    }

    cout << distance(x, y) << endl;

    return 0;
}
