#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

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
    map<string, int> r;
    int res = 0;
    for (auto& line : g) {
        if (line.size() < 6) {
            continue;
        }
        int val = r[line[4]];
        int cond = stoi(line[6]);
        if ((line[5] == "<" && val >= cond)
            || (line[5] == ">" && val <= cond)
            || (line[5] == "==" && val != cond)
            || (line[5] == "!=" && val == cond)
            || (line[5] == "<=" && val > cond)
            || (line[5] == ">=" && val < cond)) {
            continue;
        }
        int arg = stoi(line[2]);
        if (line[1] == "inc") {
            r[line[0]] += arg;
        } else {
            r[line[0]] -= arg;
        }
        res = max(res, r[line[0]]);
    }
    cout << res << endl;
    return 0;
}
