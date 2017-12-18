#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <climits>

using namespace std;

template <typename T>
using grid = vector<vector<T>>;

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

template <typename Func>
void do_line_by_line(Func&& f) {
    string line;
    while (getline(cin, line)) {
        f(line);
    }
}

template <typename T>
grid<T> read_grid() {
    grid<T> result;
    do_line_by_line([&result] (string& line) {
        result.push_back(tokenize<T>(line));
    });
    return std::move(result);
}

class context {
    int64_t _regs[27];
    int _ip;
    int64_t _last_sound;
    int64_t _last_recorded_sound;
public:
    context() : _ip(0) {
        for (char r = 'a'; r <= 'z'; ++r) {
            _regs[r - 'a'] = 0;
        }
    }
    void send_sound(int64_t s) { _last_sound = s; }
    void set_register(char name, int64_t v) { _regs[name - 'a'] = v; }
    int64_t get_register_value(char name) const { return _regs[name - 'a'];}
    void record_sound() { _last_recorded_sound = _last_sound; _ip = INT_MAX - 1; }
    void jump(int x) { _ip += x - 1; }
    int64_t last_sound() const { return _last_recorded_sound; }
    int ip() const { return _ip; }
    void increment_ip() { ++_ip; }
};

class operand {
public:
    virtual int64_t get_value(const context&) const = 0;
    virtual char get_register_name() const = 0;
    virtual ~operand() {}
};

class register_operand : public operand {
    char _name;
public:
    register_operand(char name) : _name(name) { }
    virtual int64_t get_value(const context& ctx) const override {
        return ctx.get_register_value(_name);
    }
    virtual char get_register_name() const override {
        return _name;
    }
};

class value_operand : public operand {
    int64_t _value;
public:
    value_operand(int64_t v) : _value(v) { }
    virtual int64_t get_value(const context&) const override {
        return _value;
    }
    virtual char get_register_name() const override {
        throw std::runtime_error("value operand does not have register name");
    }
};

class instruction {
protected:
    unique_ptr<operand> _op1;
    unique_ptr<operand> _op2;
    explicit instruction(unique_ptr<operand> op1) : _op1(std::move(op1)) { }
    instruction(unique_ptr<operand> op1, unique_ptr<operand> op2)
        : _op1(std::move(op1))
        , _op2(std::move(op2))
    { }
public:
    virtual void execute(context&) const = 0;
};

class snd : public instruction {
public:
    snd(unique_ptr<operand> op1) : instruction(std::move(op1)) { }
    virtual void execute(context& ctx) const {
        ctx.send_sound(_op1->get_value(ctx));
    }
};

class set : public instruction {
public:
    set(unique_ptr<operand> op1, unique_ptr<operand> op2) : instruction(std::move(op1), std::move(op2)) { }
    virtual void execute(context& ctx) const {
        ctx.set_register(_op1->get_register_name(), _op2->get_value(ctx));
    }
};

class add : public instruction {
public:
    add(unique_ptr<operand> op1, unique_ptr<operand> op2) : instruction(std::move(op1), std::move(op2)) { }
    virtual void execute(context& ctx) const {
        ctx.set_register(_op1->get_register_name(), _op1->get_value(ctx) + _op2->get_value(ctx));
    }
};

class mul : public instruction {
public:
    mul(unique_ptr<operand> op1, unique_ptr<operand> op2) : instruction(std::move(op1), std::move(op2)) { }
    virtual void execute(context& ctx) const {
        ctx.set_register(_op1->get_register_name(), _op1->get_value(ctx) * _op2->get_value(ctx));
    }
};

class mod : public instruction {
public:
    mod(unique_ptr<operand> op1, unique_ptr<operand> op2) : instruction(std::move(op1), std::move(op2)) { }
    virtual void execute(context& ctx) const {
        ctx.set_register(_op1->get_register_name(), _op1->get_value(ctx) % _op2->get_value(ctx));
    }
};

class rcv : public instruction {
public:
    rcv(unique_ptr<operand> op1) : instruction(std::move(op1)) { }
    virtual void execute(context& ctx) const {
        if (_op1->get_value(ctx) != 0) {
            ctx.record_sound();
        }
    }
};

class jgz : public instruction {
public:
    jgz(unique_ptr<operand> op1, unique_ptr<operand> op2) : instruction(std::move(op1), std::move(op2)) { }
    virtual void execute(context& ctx) const {
        if (_op1->get_value(ctx) > 0) {
            ctx.jump(_op2->get_value(ctx));
        }
    }
};

unique_ptr<operand> read_operand(string s) {
    if (s[0] >= 'a' && s[0] <= 'z') {
        return make_unique<register_operand>(s[0]);
    } else {
        return make_unique<value_operand>(stoi(s));
    }
}

vector<unique_ptr<instruction>> decode(grid<string>& g) {
    vector<unique_ptr<instruction>> res;
    for (auto& line : g) {
        unique_ptr<operand> op1 = read_operand(line[1]);
        unique_ptr<operand> op2;
        if (line.size() > 2) {
            op2 = read_operand(line[2]);
        }
        if (line[0] == "snd") {
            res.push_back(make_unique<snd>(std::move(op1)));
        } else if (line[0] == "set") {
            res.push_back(make_unique<set>(std::move(op1), std::move(op2)));
        } else if (line[0] == "add") {
            res.push_back(make_unique<add>(std::move(op1), std::move(op2)));
        } else if (line[0] == "mul") {
            res.push_back(make_unique<mul>(std::move(op1), std::move(op2)));
        } else if (line[0] == "mod") {
            res.push_back(make_unique<mod>(std::move(op1), std::move(op2)));
        } else if (line[0] == "rcv") {
            res.push_back(make_unique<rcv>(std::move(op1)));
        } else if (line[0] == "jgz") {
            res.push_back(make_unique<jgz>(std::move(op1), std::move(op2)));
        }
    }
    return std::move(res);
}

int main() {
    grid<string> g = read_grid<string>();
    vector<unique_ptr<instruction>> ins = decode(g);
    context ctx;
    while (ctx.ip() < ins.size() && ctx.ip() > -1) {
        cout << ctx.ip() << endl;
        ins[ctx.ip()]->execute(ctx);
        ctx.increment_ip();
    }
    cout << ctx.last_sound() << endl;
    return 0;
}
