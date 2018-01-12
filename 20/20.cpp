#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class particle;

class coordinates {
    int _x;
    int _y;
    int _z;
    friend  istream& operator>>(istream& in, coordinates& c);
    friend ostream& operator<<(ostream& out, coordinates& c);
    friend class particle;
public:
    int distance() const {
        return abs(_x) + abs(_y) + abs(_z);
    }
};

istream& operator>>(istream& in, coordinates& c) {
    in.ignore();
    in >> c._x;
    in.ignore();
    in >> c._y;
    in.ignore();
    in >> c._z;
    in.ignore();
    return in;
}

ostream& operator<<(ostream& out, coordinates& c) {
    out << "<" << c._x << ", " << c._y << ", " << c._z << ">";
    return out;
}

class particle {
    coordinates _p;
    coordinates _v;
    coordinates _a;
    friend istream& operator>>(istream& in, particle& p);
    friend ostream& operator<<(ostream& out, particle& p);
public:
    int sum() const {
        return abs(_a._x) + abs(_a._y) + abs(_a._z);
    }
    const coordinates& start() const { return _p; }
};

istream& operator>>(istream& in, particle& p) {
    char c;
    if (in >> c) {
        in.ignore();
        in >> p._p;
        in.ignore();
        in.ignore();
        in.ignore();
        in.ignore();
        in >> p._v;
        in.ignore();
        in.ignore();
        in.ignore();
        in.ignore();
        in >> p._a;
    }
    return in;
}

ostream& operator<<(ostream& out, particle& p) {
    out << "p=" << p._p << ", v=" << p._v << ", a=" << p._a;
    return out;
}

int main() {
    vector<particle> particles;
    particle p;
    while (cin >> p) {
        particles.push_back(p);
    }

    int res = 0;
    int sum = p.sum();
    for (int i = 1; i < particles.size(); ++i) {
        auto& p = particles[i];
        int p_sum = p.sum();
        if (p_sum < sum || (p_sum == sum && p.start().distance() < particles[res].start().distance())) {
            sum = p_sum;
            res = i;
            continue;
        }
        if (p_sum == 0 && sum != 0) {
            sum = p_sum;
            res = i;
            continue;
        }
    }

    cout << res << endl;

    return 0;
}
