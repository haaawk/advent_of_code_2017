#include <iostream>

using namespace std;

static constexpr int prog_count = 5;
static constexpr int step_count = 2;//1000000000;

int main() {
    int order[prog_count];
    int position[prog_count];
    for (int i = 0; i < prog_count; ++i) {
        order[i] = i;
        position[i] = i;
    }
    char c;
    while (cin >> c) {
        switch (c) {
            case 's':
            {
                int d;
                cin >> d;
                int new_order[prog_count];
                for (int i = 0; i < prog_count; ++i)
                    new_order[i] = order[(i - d + prog_count) % prog_count];
                for (int i = 0; i < prog_count; ++i) {
                    order[i] = new_order[i];
                    position[order[i]] = i;
                }
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
                swap(order[position[pro1]], order[position[pro2]]);
                swap(position[pro1], position[pro2]);
                break;
            }
            case 'x':
            {
                int pos1, pos2;
                cin >> pos1;
                cin.ignore();
                cin >> pos2;
                swap(order[pos1], order[pos2]);
                swap(position[order[pos1]], position[order[pos2]]);
                break;
            }
        }
        cin.ignore();
    }
    int res[prog_count];
    for (int i = 0; i < prog_count; ++i)
        res[i] = i;
    for (int step = 0; step < step_count; ++step) {
        int new_res[prog_count];
        for (int i = 0; i < prog_count; ++i)
            new_res[i] = res[order[i]];
        for (int i = 0; i < prog_count; ++i)
            res[i] = new_res[i];
    for (int x : res)
        cout << (char)('a' + x);
    cout << endl;
    }
    for (int x : res)
        cout << (char)('a' + x);
    cout << endl;
    return 0;
}
