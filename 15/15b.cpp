#include <iostream>

using namespace std;

static constexpr int64_t factor_a = 16807;
static constexpr int64_t factor_b = 48271;
static constexpr int64_t mod = 2147483647;
static constexpr int round_count = 5000000;

bool ok(int64_t x, int64_t y) {
    static constexpr int64_t mask = 0x000000000000FFFF;
    return (x & mask) == (y & mask);
}

int main() {
    int64_t a = 512;
    int64_t b = 191;

    int res = 0;
    for (int step = 0; step < round_count; ++step) {
        do { a = (a * factor_a) % mod; } while (a % 4 > 0);
        do { b = (b * factor_b) % mod; } while (b % 8 > 0);
        if (ok(a, b)) {
            ++res;
        }
    }

    cout << res << endl;

    return 0;
}
