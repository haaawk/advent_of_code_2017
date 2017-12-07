#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

template <typename Func>
void do_line_by_line(Func&& f) {
    string line;
    while (getline(cin, line)) {
        f(line);
    }
}

int main() {
    set<string> children;
    set<string> all;
    do_line_by_line([&all, &children] (const string& s) {
        all.emplace(s.substr(0, s.find_first_of("(") - 1));
        auto pos = s.find_first_of("->");
        if (pos != string::npos) {
            stringstream tokenizer(s.substr(pos + 3));
            string word;
            while (tokenizer >> word) {
                if (word.back() == ',') {
                    children.emplace(word.substr(0, word.size() - 1));
                } else {
                    children.emplace(std::move(word));
                }
            }
        }
    });
    for (auto& name : all) {
        if (children.count(name) == 0) {
            cout << name << endl;
            break;
        }
    }
    return 0;
}
