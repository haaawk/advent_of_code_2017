#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
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

int solve(const string& name, map<string, int>& w, map<string, vector<string>>& g) {
    vector<string>& ch = g[name];
    vector<int> ch_w;
    int sum = 0;
    for (auto& c : ch) {
        ch_w.push_back(solve(c, w, g));
        sum += ch_w.back();
    }
    if (ch.size() < 3) {
        return w[name] + sum;
    }
    auto min_and_max = minmax_element(begin(ch_w), end(ch_w));
    int min = *min_and_max.first;
    int max = *min_and_max.second;
    if (min == max) {
        return w[name] + sum;
    }
    int offset = 0;
    if ((ch.size() - 1) * min + max == sum) {
        offset = min - max;
        cout << w[ch[min_and_max.second - begin(ch_w)]] + offset << endl;
    } else {
        offset = max - min;
        cout << w[ch[min_and_max.first - begin(ch_w)]] + offset << endl;
    }
    return w[name] + sum + offset;
}

int main() {
    map<string, int> weights;
    map<string, vector<string>> g;
    set<string> not_roots;
    grid<string> input = read_grid<string>();
    for (auto& line : input) {
        weights[line[0]] = stoi(line[1].substr(1, line[1].size() - 1));
        if (line.size() > 2) {
            vector<string> children;
            for (int i = 4; i < line.size(); ++i) {
                children.emplace_back(line[i - 1].substr(0, line[i - 1].size() - 1));
            }
            children.emplace_back(line.back());
            not_roots.insert(begin(children), end(children));
            g.emplace(line[0], std::move(children));
        }
    }
    for (auto& it : weights) {
        if (not_roots.count(it.first) == 0) {
            solve(it.first, weights, g);
            break;
        }
    }
    return 0;
}
