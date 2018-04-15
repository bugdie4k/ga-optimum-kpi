#include "Chromosome.h"
#include "utils.h"
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

std::ostream &operator << (std::ostream &os, Chromosome &obj) {
    os << "fn(";
    pprint_v(obj.argv, ", ");
    os << ") = " << obj.res << endl;
    return os;
}

std::ostream &operator << (std::ostream &os, Chromosome* objp) {
    os << *objp;
    return os;
}

void Chromosome::push(double arg) {    
    this->argv.push_back(arg);
}

bool operator < (const Chromosome& l, const Chromosome& r) {
    return l.res < r.res;
}

bool operator > (const Chromosome& l, const Chromosome& r) {
    return l.res > r.res;
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

void Chromosome::pprint() {
    cout << *this;
}

int Chromosome::size() {
    return argv.size();
}
