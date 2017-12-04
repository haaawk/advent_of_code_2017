#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <set>

using namespace std;

template <typename T>
using grid = vector<vector<T>>;

template <typename T>
vector<T> tokenize(string& line) {
    stringstream tokenizer(line, ios_base::in);
    T value;
    vector<T> result;
    while (tokenizer >> value) {
        result.push_back(std::move(value));
    }
    return std::move(result);
}

template <typename Func>
void do_line_by_line(Func&& f) {
    string line;
    while (getline(cin, line)) {
        f(line);
    }
}

template <typename T>
grid<T> read_grid() {
    grid<T> result;
    do_line_by_line([&result] (string& line) {
        result.push_back(tokenize<T>(line));
    });
    return std::move(result);
}

int main() {
    grid<string> g = read_grid<string>();
    int res = 0;
    for (auto& p : g) {
        set<string> unique;
        for (auto& w : p) {
            sort(w.begin(), w.end());
            unique.emplace(w);
        }
        res += unique.size() == p.size() ? 1 : 0;
    }
    cout << res << endl;
    return 0;
}
