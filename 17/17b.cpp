#include <iostream>

using namespace std;

constexpr int limit = 50000000;

int main() {
    int curr = 0;
    int step;
    cin >> step;
    int zero = 0;
    int res = 0;
    for (int i = 0; i < limit; ++i) {
        curr = (curr + step) % (i + 1);
        if (curr == zero) {
            res = (i + 1);
        } else if (curr < zero) {
            ++zero;
        }
        ++curr;
    }
    cout << res << endl;
    return 0;
}
