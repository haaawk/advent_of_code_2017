#include <iostream>
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

int main() {
    vector<int> lens;
    char c;
    while (cin >> c)
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
    for (int i = 0; i < 16; ++i) {
        int dense = list[16 * i];
        for (int j = 1; j < 16; ++j)
            dense ^= list[16 * i + j];
        cout << setfill('0') << setw(2) << hex << dense;
    }
    cout << endl;
    return 0;
}
