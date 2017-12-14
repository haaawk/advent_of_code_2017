#include <iostream>
#include <string>
#include <sstream>
#include <vector>

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

int count(char c) {
    switch (c) {
        case '0': return 0; // 0000
        case '1': return 1; // 0001
        case '2': return 1; // 0010
        case '3': return 2; // 0011
        case '4': return 1; // 0100
        case '5': return 2; // 0101
        case '6': return 2; // 0110
        case '7': return 3; // 0111
        case '8': return 1; // 1000
        case '9': return 2; // 1001
        case 'a': return 2; // 1010
        case 'b': return 3; // 1011
        case 'c': return 2; // 1100
        case 'd': return 3; // 1101
        case 'e': return 3; // 1110
        case 'f': return 4; // 1111
    }
}

int main() {
    vector<int> input;
    char c;
    while (cin >> c)
        input.push_back(c);
    input.push_back('-');
    int res = 0;
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
            hash_builder << hex << dense;
        }
        string hash = hash_builder.str();
        for (char c : hash) {
            res += count(c);
        }
    }
    cout << res << endl;
    return 0;
}
