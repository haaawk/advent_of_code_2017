#include <iostream>

using namespace std;

int main() {
    char c;
    int depth = 1;
    int res = 0;
    bool garbage = false;
    bool skip = false;
    while (cin >> c) {
        if (skip) {
            skip = false;
            continue;
        }
        switch (c) {
            case '{': if (!garbage) { res += depth; ++depth; } continue;
            case '}': if (!garbage) --depth; continue;
            case '<': garbage = true; continue;
            case '>': garbage = false; continue;
            case '!': if (garbage) skip = true; continue;
            default: continue;
        }
    }
    cout << res << endl;
    return 0;
}
