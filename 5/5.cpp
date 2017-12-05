#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

int main() {
    vector<int> ins;
    int x;
    while (cin >> x)
        ins.emplace_back(x);
    int p = 0;
    int res = 0;
    while (p < ins.size() && p >= 0) {
        ++res;
        p += ins[p]++;
    }
    cout << res << endl;
    return 0;
}
