#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

template <typename T>
vector<T> tokenize(string& line) {
    stringstream tokenizer(line, ios_base::in);
    T value;
    vector<T> result;
    while (tokenizer >> value) {
        result.push_back(std::move(value));
    }
    return std::move(result);
}

template <typename T>
vector<T> read_sequence() {
   string line;
   if (getline(cin, line)) {
       return tokenize<T>(line);
   } else {
       return vector<T>();
   }
}

int find_biggest(const vector<int>& banks) {
    int res = banks.size();
    int res_value = -1;
    for (int i = 0; i < banks.size(); ++i) {
        if (res_value < banks[i]) {
            res_value = banks[i];
            res = i;
        }
    }
    return res;
}

void update(vector<int>& banks, int p) {
    int to_distribute = banks[p];
    banks[p] = 0;
    int big_share = to_distribute / banks.size() + (to_distribute % banks.size() > 0 ? 1 : 0);
    int small_share = to_distribute / banks.size();
    int big_count = to_distribute % banks.size();

    while (to_distribute > 0) {
        p = (p + 1) % banks.size();
        int share = big_count > 0 ? big_share : small_share;
        banks[p] += share;
        --big_count;
        to_distribute -= share;
    }
}

int main() {
    vector<int> banks = read_sequence<int>();
    set<vector<int>> seen;
    int step = 0;
    while (seen.insert(banks).second) {
        ++step;
        update(banks, find_biggest(banks));
    }
    cout << step << endl;
    return 0;
}
