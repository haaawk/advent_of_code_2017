#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int main() {
    uint64_t sum = 0;
    std::string line;
    while (getline(std::cin, line)) {
        std::stringstream tokenizer(line);
        int val = 0;
        std::vector<int> nums;
        while (tokenizer >> val) {
            nums.push_back(val);
        }
        for (int i = 0; i < nums.size(); ++i)
            for (int j = i + 1; j < nums.size(); ++j) {
                int a = std::max(nums[i], nums[j]);
                int b = std::min(nums[i], nums[j]);
                if (a % b == 0) {
                    sum += a / b;
                    break;
                }
            }
    }
    std::cout << sum << std::endl;
    return 0;
}
