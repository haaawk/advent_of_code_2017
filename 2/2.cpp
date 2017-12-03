#include <iostream>
#include <string>
#include <sstream>
#include <climits>

int main() {
    uint64_t sum = 0;
    std::string line;
    while (getline(std::cin, line)) {
        std::stringstream tokenizer(line);
        int val = 0;
        int largest = INT_MIN;
        int smallest = INT_MAX;
        while (tokenizer >> val) {
            largest = std::max(largest, val);
            smallest = std::min(smallest, val);
        }
        sum += largest - smallest;
    }
    std::cout << sum << std::endl;
    return 0;
}
