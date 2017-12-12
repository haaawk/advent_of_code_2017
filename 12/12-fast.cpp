#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

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

class find_and_union {
    map<int, int> _data;
public:
    using iter = map<int, int>::iterator;
private:
    iter  do_find(iter it) {
        if (it->second < 0) {
            return it;
        }
        auto p_it = find(it->second);
        it->second = p_it->first;
        return p_it;
    }
public:
    iter find(int x) {
        auto it = _data.find(x);
        return do_find(it);
    }
    iter find_or_add(int x) {
        auto it = _data.lower_bound(x);
        if (it == end(_data) || it->first != x) {
            return _data.emplace_hint(it, x, -1);
        }
        return do_find(it);
    }
    void merge(int a, int b) {
        auto a_it = find_or_add(a);
        auto b_it = find_or_add(b);
        if (a_it != b_it) {
            if (a_it->second < b_it->second) {
                a_it->second += b_it->second;
                b_it->second = a_it->first;
            } else {
                b_it->second += a_it->second;
                a_it->second = b_it->first;
            }
        }
    }
    size_t size(int x) {
        return -find_or_add(x)->second;
    }
    size_t group_count() {
        return count_if(begin(_data), end(_data), [] (auto&& x) { return x.second < 0; });
    }
};

int main() {
    grid<string> g = read_grid<string>();
    find_and_union fu;
    for (auto& line : g) {
        int node_id = stoi(line[0]);
        for (int i = 2; i < line.size(); ++i) {
            fu.merge(node_id, stoi(line[i]));
        }
    }
    cout << fu.size(0) << endl;
    return 0;
}
