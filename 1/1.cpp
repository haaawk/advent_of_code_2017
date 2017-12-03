#include<iostream>

unsigned char_to_int(char c) {
    return c - '0';
}

int main() {
    uint64_t sum = 0;
    char next;
    if (std::cin >> next) {
        unsigned first = char_to_int(next);
        unsigned last = first;
        unsigned count = 1;
        while (std::cin >> next) {
            ++count;
            unsigned x = char_to_int(next);
            if (last == x) {
                sum += x;
            }
            last = x;
        }
        if (count > 1 && last == first) {
            sum += first;
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
