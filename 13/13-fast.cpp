#include <iostream>
#include <map>
#include <vector>
#include <numeric>
#include<climits>

using namespace std;

using result = pair<int64_t, int64_t>;

tuple<int64_t, int64_t, int64_t> extended_euclid_algorithm(int64_t a, int64_t b) {
    int64_t a0 = a;
    int64_t b0 = b;
    int64_t p = 1;
    int64_t q = 0;
    int64_t r = 0;
    int64_t s = 1;
    while (b != 0) {
        int64_t c = a % b;
        int64_t quot = a / b;
        a = b;
        b = c;
        int64_t r_tmp = r;
        int64_t s_tmp = s;
        r = p - quot * r;
        s = q - quot * s;
        p = r_tmp;
        q = s_tmp;
    }
    return make_tuple(a, p, q);
}

template <typename Func>
void for_each_starting_point(int64_t position, int64_t period, Func f) {
    for (int64_t offset = 1, start = (1 + period - position % period) % period;
         offset < period;
         ++offset, start = (start + 1) % period) {
        f(start);
    }
}

vector<result> results_from_first(auto& s) {
    vector<result> results;
    for_each_starting_point(s.first, s.second, [&results, period = s.second] (auto&& start) {
        results.emplace_back(start, period);
    });
    return std::move(results);
}

optional<int64_t> solve(int64_t a, int64_t b, int64_t n) {
    auto [d, p, q] = extended_euclid_algorithm(a, n);
    if (d == 1) {
        int64_t res = (b * p) % n;
        if (res < 0)
            res += n * (res / n + (res % n != 0));
        return res;
    } else if (b % d == 0) {
        return solve(a / d, b / d, n / d);
    } else {
        return nullopt;
    }
    return nullopt;
}

optional<int64_t> find_new_start(int64_t s1, int64_t s2, int64_t p1, int64_t p2) {
    optional<int64_t> x = solve(p1, s2 - s1, p2);
    if (!x) {
        return nullopt;
    }
    // p1 * x + s1 == p2 * y + s2
    return s1 + p1 * (*x);
}

vector<result> advance_results(auto& s, vector<result> old) {
    vector<result> results;
    for_each_starting_point(s.first, s.second, [&results, &old, period = s.second] (auto&& start) {
        for (result& r : old) {
            int64_t period2 = r.second;
            int64_t start2 = r.first;
            if (start == start2) {
                results.emplace_back(start, lcm(period, period2));
            } else {
                optional<int64_t> new_start = find_new_start(start, start2, period, period2);
                if (new_start) {
                    results.emplace_back(*new_start, lcm(period, period2));
                }
            }
        }
    });
    return std::move(results);
}

int main() {
    int a, b;
    map<int, int> scanners;
    while (cin >> a) {
        cin.ignore();
        cin >> b;
        scanners.emplace(a, 2 * (b - 1));
    }
    vector<result> results;
    bool first = true;
    for (auto& s : scanners) {
        if (first) {
            first = false;
            results = results_from_first(s);
        } else {
            results = advance_results(s, std::move(results));
        }
    }
    int64_t res = INT_MAX;
    for (auto& r : results) {
        res = min(res, r.first);
    }
    cout << res << endl;
    return 0;
}
