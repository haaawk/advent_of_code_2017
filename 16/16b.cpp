#include <iostream>
#include <vector>
#include <map>

using namespace std;

static constexpr int prog_count = 16;
static constexpr int step_count = 1000000000;

struct step {
    bool swap;
    int a, b;
    int order[prog_count];
    step(int _a, int _b) : swap(true), a(_a), b(_b) {}
    step(int _order[prog_count]) : swap(false) {
        for (int i = 0; i < prog_count; ++i)
            order[i] = _order[i];
    }
    step() : swap(false) {
        for (int i = 0; i < prog_count; ++i)
            order[i] = i;
    }
};

int main() {
    int order[prog_count];
    int position[prog_count];
    for (int i = 0; i < prog_count; ++i) {
        order[i] = i;
        position[i] = i;
    }
    vector<step> steps;
    char c;
    while (cin >> c) {
        switch (c) {
            case 's':
            {
                int d;
                cin >> d;
                if (steps.empty() || steps.back().swap)
                    steps.push_back(step());
                int new_order[prog_count];
                for (int i = 0; i < prog_count; ++i)
                    new_order[i] = steps.back().order[(i - d + prog_count) % prog_count];
                for (int i = 0; i < prog_count; ++i)
                    steps.back().order[i] = new_order[i];
                break;
            }
            case 'p':
            {
                char prog1, prog2;
                cin >> prog1;
                cin.ignore();
                cin >> prog2;
                int pro1 = prog1 - 'a';
                int pro2 = prog2 - 'a';
                steps.push_back(step(pro1, pro2));
                break;
            }
            case 'x':
            {
                int pos1, pos2;
                cin >> pos1;
                cin.ignore();
                cin >> pos2;
                if (steps.empty() || steps.back().swap)
                    steps.push_back(step());
                swap(steps.back().order[pos1], steps.back().order[pos2]);
                break;
            }
        }
        cin.ignore();
    }
    vector<int> res(prog_count);
    for (int i = 0; i < prog_count; ++i) {
        res[i] = i;
        position[i] = i;
    }
    map<vector<int>, int> cache;
    for (int step = 0; step < step_count; ++step) {
        for (auto& m : steps) {
            if (m.swap) {
                swap(res[position[m.a]], res[position[m.b]]);
                swap(position[m.a], position[m.b]);
            } else {
                int new_res[prog_count];
                for (int i = 0; i < prog_count; ++i)
                    new_res[i] = res[m.order[i]];
                for (int i = 0; i < prog_count; ++i) {
                    res[i] = new_res[i];
                    position[res[i]] = i;
                }
            }
        }
        int& cached = cache[res];
        if (cached != 0) {
            int diff = step + 1 - cached;
            while (step + diff < step_count)
                step += diff;
        } else {
            cached = step + 1;
        }
    }
    for (int x : res)
        cout << (char)('a' + x);
    cout << endl;
    return 0;
}
