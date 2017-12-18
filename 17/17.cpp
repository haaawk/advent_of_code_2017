#include <iostream>
#include <vector>

using namespace std;

constexpr int limit = 2017;

int main() {
    vector<int> buffer;
    buffer.push_back(0);
    int curr = 0;
    int step;
    cin >> step;
    for (int i = 0; i < limit; ++i) {
        curr = (curr + step) % (i + 1);
        buffer.insert(begin(buffer) + curr + 1, i + 1);
        ++curr;
    }
    cout << buffer[(curr + 1) % buffer.size()] << endl;
    return 0;
}
