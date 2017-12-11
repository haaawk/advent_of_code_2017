#include <iostream>
#include <vector>
#include <sstream>
#include <string>

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
    vector<int> list(list_len);
    for (int i = 0; i < list_len; ++i)
        list[i] = i;
    string input;
    getline(cin, input);
    stringstream tokenizer(input);
    int skip_size = 0;
    int curr = 0;
    int len;
    while (tokenizer >> len) {
        reverse(curr, len, list);
        curr = (curr + len + skip_size) % list_len;
        ++skip_size;
        if (tokenizer.peek() == ',')
            tokenizer.ignore();
    }
    cout << list[0] * list[1] << endl;
    return 0;
}
