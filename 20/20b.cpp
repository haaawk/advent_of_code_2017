#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <utility>

using namespace std;

template <int D = 3>
struct coordinates {
    int _data[D];
    int distance() const {
        return accumulate(_data, _data + D, 0, [] (auto& res, auto& item) { return res + abs(item); });
    }
    bool operator<(const coordinates& o) const {
        for (int i = 0; i < D; ++i) {
            if (_data[i] < o._data[i]) {
                return true;
            } else if (_data[i] > o._data[i]) {
                return false;
            }
        }
        return false;
    }
    coordinates& operator+=(const coordinates& o) {
        for (int i = 0; i < D; ++i)
            _data[i] += o._data[i];
    }
};

template <int D>
istream& operator>>(istream& in, coordinates<D>& c) {
    for (int i = 0; i < D; ++i) {
        in.ignore();
        in >> c._data[i];
    }
    in.ignore();
    return in;
}

template <int D>
ostream& operator<<(ostream& out, coordinates<D>& c) {
    out << "<" << c._data[0];
    for (int i = 1; i < D; ++i)
       out << ", " << c._data[i];
    out << ">";
    return out;
}

struct particle {
    coordinates<> _p;
    coordinates<> _v;
    coordinates<> _a;
    void move() {
        _v += _a;
        _p += _v;
    }
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

void remove_crashes(vector<particle>& p) {
    map<coordinates<>, int> count;
    for_each(begin(p), end(p), [&count] (auto& item) { ++count[item._p]; });
    p.erase(remove_if(begin(p), end(p), [&count] (auto& item) { return count[item._p] > 1; }), end(p));
}

int main() {
    vector<particle> particles;
    particle p;
    while (cin >> p) {
        particles.push_back(p);
    }
    remove_crashes(particles);
    for (int i = 0; i < 1500; ++i) {
        for_each(begin(particles), end(particles), [] (auto& p) { p.move(); });
        remove_crashes(particles);
    }

    cout << particles.size() << endl;

    return 0;
}
