#include "Chromosome.h"
#include "utils.h"

#include <iostream>
#include <iomanip>

using std::vector;
using std::cout;
using std::endl;

void Chromosome::push(double arg) {
    this->argv.push_back(arg);
}

void Chromosome::set(vector<double> argv, double res) {
    this->argv = argv;
    this->res = res;
}

void Chromosome::randomize(int argn, double from, double to, double (*fn)(vector<double>)) {
    for (int i = 0; i < argn; ++i)
        argv.push_back(random_d(from, to));
    res = (*fn)(argv);
}

std::ostream &operator << (std::ostream &os, Chromosome &obj) {
    os << "fn(";
    pprint_v(obj.argv, ", ");
    os << ") = " << std::setprecision(20) << obj.res << endl;
    return os;
}

std::ostream &operator << (std::ostream &os, Chromosome* objp) {
    os << *objp;
    return os;
}

void Chromosome::pprint() {
    cout << *this;
}

int Chromosome::size() const {
    return argv.size();
}


bool operator < (const Chromosome& l, const Chromosome& r) {
    return l.res < r.res;
}

bool operator > (const Chromosome& l, const Chromosome& r) {
    return l.res > r.res;
}

bool operator == (const Chromosome& l, const Chromosome& r) {
    if (l.size() != r.size())
        return false;
    for (int i = 0; i < l.size(); ++i) {
        if (l.argv[i] != r.argv[i])
            return false;
    }
    return l.res == r.res;
}
