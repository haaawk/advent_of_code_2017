#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
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

using board_t = vector<string>;

board_t read(int size, const string& s) {
    board_t res;
    res.reserve(size);
    for (int pos = 0; pos < s.size(); pos += size + 1)
        res.emplace_back(s.substr(pos, size));
    return std::move(res);
}

struct pattern {
    int size;
    board_t from;
    board_t to;
    pattern(vector<string>& s)
        : size(s[0].size() == 5 ? 2 : 3)
        , from(read(size, s[0]))
        , to(read(size + 1, s[2]))
    { }
    void flip() {
        for (auto& r : from)
            swap(r[0], r[size - 1]);
    }
    void rotate() {
        if (size == 2) {
            auto tmp = from[0][0];
            from[0][0] = from[1][0];
            from[1][0] = from[1][1];
            from[1][1] = from[0][1];
            from[0][1] = tmp;
        } else {
            auto tmp1 = from[0][1];
            auto tmp2 = from[0][0];
            from[0][1] = from[1][0];
            from[0][0] = from[2][0];
            from[1][0] = from[2][1];
            from[2][0] = from[2][2];
            from[2][1] = from[1][2];
            from[2][2] = from[0][2];
            from[1][2] = tmp1;
            from[0][2] = tmp2;
        }
    }
    bool match(board_t& b, int x, int y) const {
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                if (b[x + i][y + j] != from[i][j])
                    return false;
        return true;
    }

    bool operator<(const pattern& o) const {
        return from < o.from;
    }
};

void add_all_rotations(map<int, set<pattern>>& patterns, pattern p) {
    auto& s = patterns[p.size];
    s.insert(p);
    for (int i = 0; i < 3; ++i) {
        p.rotate();
        s.insert(p);
    }
}

int count_hash(board_t& b) {
    int res = 0;
    for (auto& r : b)
        res += count(begin(r), end(r), '#');
    return res;
}

int main() {
    grid<string> g = read_grid<string>();
    map<int, set<pattern>> patterns;
    for (auto& row : g) {
        pattern p{row};
        add_all_rotations(patterns, p);
        p.flip();
        add_all_rotations(patterns, p);
    }
    vector<string> board = {
        ".#.",
        "..#",
        "###"
    };
    int steps = 18;
    while (steps-- > 0) {
        int size = board.size();
        int step = size % 2 == 0 ? 2 : 3;
        vector<string> new_board(size + size / step);
        int curr_row = 0;
        for (int i = 0; i < size; i += step, curr_row += step + 1)
            for (int j = 0; j < size; j += step)
                for (auto& p : patterns[step])
                    if (p.match(board, i, j)) {
                        for (int x = 0; x <= step; ++x)
                            for (int y = 0; y <= step; ++y)
                                new_board[curr_row + x].push_back(p.to[x][y]);
                        break;
                    }
        board = new_board;
    }
    cout << count_hash(board) << endl;
    return 0;
}
