#include <iostream>
#include <map>

using namespace std;

int main() {
    int a, b;
    map<int, int> scanners;
    while (cin >> a) {
        cin.ignore();
        cin >> b;
        scanners.emplace(a, 2 * (b - 1));
    }
    int res = 0;
    for (auto& s : scanners) {
        if (s.first % s.second == 0) {
            res += s.first * (s.second / 2 + 1);
        }
    }
    cout << res << endl;
    return 0;
}
