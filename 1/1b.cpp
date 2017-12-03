#include<iostream>
#include<vector>

unsigned char_to_int(char c) {
    return c - '0';
}

int main() {
    uint64_t sum = 0;
    char next;
    std::vector<unsigned> numbers;
    while (std::cin >> next) {
        numbers.push_back(char_to_int(next));
    }
    size_t offset = numbers.size() / 2;
    for (size_t i = 0; i < numbers.size(); ++i) {
        if (numbers[i] == numbers[(i + offset) % numbers.size()]) {
            sum += numbers[i];
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
