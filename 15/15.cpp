#include <iostream>

using namespace std;

static constexpr int64_t factor_a = 16807;
static constexpr int64_t factor_b = 48271;
static constexpr int64_t mod = 2147483647;
static constexpr int round_count = 40000000;

bool ok(int64_t x, int64_t y) {
    static constexpr int64_t mask = 0x000000000000FFFF;
    return (x & mask) == (y & mask);
}

int main() {
    int64_t a = 512;
    int64_t b = 191;

    int res = 0;
    for (int step = 0; step < round_count; ++step) {
        a = (a * factor_a) % mod;
        b = (b * factor_b) % mod;
        if (ok(a, b)) {
            ++res;
        }
    }

    cout << res << endl;

    return 0;
}
