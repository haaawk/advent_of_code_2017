#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
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
    cout << count_if(begin(g), end(g), [] (auto&& p) {
        sort(begin(p), end(p));
        return adjacent_find(begin(p), end(p)) == end(p);
    });
    cout << endl;
    cout << count_if(begin(g), end(g), [] (auto&& p) {
        return count_if(begin(p), end(p), [all = set<string>()] (auto&& w) mutable { return all.insert(w).second; }) == p.size();
    });
    cout << endl;
    return 0;
}
