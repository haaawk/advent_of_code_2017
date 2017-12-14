#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

static constexpr int list_len = 256;

void reverse(int start, int len, vector<int>& list) {
    int end = (start + len - 1) % list_len;
    while (start != end && (end + 1) % list_len != start) {
        swap(list[start], list[end]);
        start = (start + 1) % list_len;
        end = (end + list_len - 1) % list_len;
    }
}

void fill(vector<bool>& row, char c) {
    switch (c) {
        case '0': row.push_back(false); row.push_back(false); row.push_back(false); row.push_back(false); break; // 0000
        case '1': row.push_back(false); row.push_back(false); row.push_back(false); row.push_back(true); break; // 0001
        case '2': row.push_back(false); row.push_back(false); row.push_back(true); row.push_back(false); break; // 0010
        case '3': row.push_back(false); row.push_back(false); row.push_back(true); row.push_back(true); break; // 0011
        case '4': row.push_back(false); row.push_back(true); row.push_back(false); row.push_back(false); break; // 0100
        case '5': row.push_back(false); row.push_back(true); row.push_back(false); row.push_back(true); break; // 0101
        case '6': row.push_back(false); row.push_back(true); row.push_back(true); row.push_back(false); break; // 0110
        case '7': row.push_back(false); row.push_back(true); row.push_back(true); row.push_back(true); break; // 0111
        case '8': row.push_back(true); row.push_back(false); row.push_back(false); row.push_back(false); break; // 1000
        case '9': row.push_back(true); row.push_back(false); row.push_back(false); row.push_back(true); break; // 1001
        case 'a': row.push_back(true); row.push_back(false); row.push_back(true); row.push_back(false); break; // 1010
        case 'b': row.push_back(true); row.push_back(false); row.push_back(true); row.push_back(true); break; // 1011
        case 'c': row.push_back(true); row.push_back(true); row.push_back(false); row.push_back(false); break; // 1100
        case 'd': row.push_back(true); row.push_back(true); row.push_back(false); row.push_back(true); break; // 1101
        case 'e': row.push_back(true); row.push_back(true); row.push_back(true); row.push_back(false); break; // 1110
        case 'f': row.push_back(true); row.push_back(true); row.push_back(true); row.push_back(true); break; // 1111
    }
}

void clear(vector<vector<bool>>& grid, int x, int y) {
    if (x > -1 && x < 128 && y > -1 && y < 128 && grid[x][y]) {
        grid[x][y] = false;
        clear(grid, x - 1, y);
        clear(grid, x + 1, y);
        clear(grid, x, y - 1);
        clear(grid, x, y + 1);
    }
}

int main() {
    vector<int> input;
    char c;
    while (cin >> c)
        input.push_back(c);
    input.push_back('-');
    vector<vector<bool>> grid(128);
    for (int row_no = 0; row_no < 128; ++row_no) {
        vector<int> lens = input;
        for (char c : to_string(row_no))
            lens.push_back(c);
        lens.push_back(17);
        lens.push_back(31);
        lens.push_back(73);
        lens.push_back(47);
        lens.push_back(23);
        vector<int> list(list_len);
        for (int i = 0; i < list_len; ++i)
            list[i] = i;
        int skip_size = 0;
        int curr = 0;
        for (int i = 0; i < 64; ++i) {
            for (int len : lens) {
                reverse(curr, len, list);
                curr = (curr + len + skip_size) % list_len;
                ++skip_size;
            }
        }
        stringstream hash_builder;
        for (int i = 0; i < 16; ++i) {
            int dense = list[16 * i];
            for (int j = 1; j < 16; ++j)
                dense ^= list[16 * i + j];
            hash_builder << setfill('0') << setw(2) << hex << dense;
        }
        string hash = hash_builder.str();
        for (char c : hash) {
            fill(grid[row_no], c);
        }
    }
    int res = 0;
    for (int x = 0; x < 128; ++x)
        for (int y  = 0; y < 128; ++y)
            if (grid[x][y]) {
                ++res;
                clear(grid, x, y);
            }
    cout << res << endl;
    return 0;
}
