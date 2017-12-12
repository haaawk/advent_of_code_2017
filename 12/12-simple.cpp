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
    int find(int x) {
        int& xx = _data[x];
        if (xx < 0) {
            return x;
        }
        xx = find(xx);
        return xx;
    }
    int find_or_add(int x) {
        if (_data.count(x) == 0) {
            _data[x] = -1;
            return x;
        }
        return find(x);
    }
    void merge(int a, int b) {
        a = find_or_add(a);
        b = find_or_add(b);
        if (a != b) {
            int& aa = _data[a];
            int& bb = _data[b];
            if (aa < bb) {
                aa += bb;
                bb = a;
            } else {
                bb += aa;
                aa = b;
            }
        }
    }
    size_t size(int x) {
        return -_data[find_or_add(x)];
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
