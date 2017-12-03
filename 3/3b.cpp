#include <iostream>
#include <map>

using position = std::pair<int, int>;

class walker {
    int side_length = 1;
    int move_direction = 3;
    int steps_to_go = 0;
public:
    void move(position& p) {
        if (steps_to_go == 0) {
            move_direction = (move_direction + 1) % 4;
            if (move_direction == 0) {
                ++p.second;
                side_length += 2;
                steps_to_go = side_length - 2;
                return;
            } else {
                steps_to_go = side_length - 1;
            }
        }
        switch (move_direction) {
            case 0: --p.first; break; // UP
            case 1: --p.second; break; // LEFT
            case 2: ++p.first; break; // DOWN
            case 3: ++p.second; break; // RIGHT
        }
        --steps_to_go;
    }
};

int main() {
    int n;
    std::cin >> n;

    position p{0, 0};
    std::map<position, int> board;
    board[p] = 1;

    walker w;
    while (board[p] <= n) {
        w.move(p);
        board[p] =
            board[{p.first - 1, p.second - 1}] + board[{p.first - 1, p.second}] + board[{p.first - 1, p.second + 1}] +
            board[{p.first, p.second - 1}] + board[{p.first, p.second + 1}] +
            board[{p.first + 1, p.second - 1}] + board[{p.first + 1, p.second}] + board[{p.first + 1, p.second + 1}];
    }

    std::cout << board[p] << std::endl;

    return 0;
}
