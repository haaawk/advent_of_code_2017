#include <iostream>
#include <map>

using namespace std;

bool hits_scanner(auto s, int delay) {
    return (delay + s.first) % s.second == 0;
}

int main() {
    int a, b;
    map<int, int> scanners;
    while (cin >> a) {
        cin.ignore();
        cin >> b;
        scanners.emplace(a, 2 * (b - 1));
    }
    for (int delay = 0; true; ++delay) {
        bool fail = false;
        for (auto& s : scanners) {
            if (hits_scanner(s, delay)) {
                fail = true;
                break;
            }
        }
        if (!fail) {
            cout << delay << endl;
            break;
        }
    }

    return 0;
}
