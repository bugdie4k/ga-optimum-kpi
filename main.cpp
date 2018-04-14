#include <random>
#include <chrono>
#include <ctime>
#include <cmath>
#include <iostream>
#include <vector>
#include <array>
#include <iterator>
#include <string>
#include <assert.h>
#include <algorithm>
#include <functional>

using std::cout;
using std::endl;
using std::vector;
using std::array;
using std::string;

static const int N = 10;
static const int ITERS = 100;

// #define DOTIMES(N) for(int i = 0; i < N; ++i)

double random_d(double lower_bound, double upper_bound) {
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> uni(lower_bound, upper_bound);
    return uni(re);
}

int random_i(int lower_bound, int upper_bound) {
    std::random_device rd;   // only used once to initialise (seed) engine
    std::mt19937 rng(rd());  // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(lower_bound, upper_bound);
    return uni(rng);
}

template <typename T>
void pprint_v(T v, string delim = "") {
    for (auto it = v.begin(); it != v.end(); ++it) {
        cout << *it;
        if (it != v.end() - 1)
            cout << delim;
    }
}

class Chromosome {
    public:
     vector<double> argv;
     double res;

     void set(vector<double> argv, double res);
     void randomize(int argn, double from, double to, double (*fn)(vector<double>));

     int size();
     void pprint();
     bool operator < (const Chromosome &other);
     bool operator > (const Chromosome &other);
     vector<double>::iterator begin();
     vector<double>::iterator end();
     void push(double arg);
};

void Chromosome::push(double arg) {
    this->argv.push_back(arg);
}

vector<double>::iterator Chromosome::begin() {
    return this->argv.begin();
}

vector<double>::iterator Chromosome::end() {
    return this->argv.end();
}

bool Chromosome::operator < (const Chromosome &other) {
    return this->res < other.res;
}

bool Chromosome::operator > (const Chromosome &other) {
    return this->res > other.res;
}

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

class Population {
    public:
     vector<Chromosome*> pop;
     double (*fn)(vector<double>);

     explicit Population(double (*fn)(vector<double>));

     void set(vector<Chromosome*>);
     void randomize(int n, int argn, double from, double to);
     void iterate();

     void pprint();
     int size();

    private:
     vector<Chromosome*> select();
     vector<Chromosome*> crossover(vector<Chromosome*> selected);
     array<Chromosome*, 2> cross2(Chromosome* c1, Chromosome* c2);
     vector<Chromosome*> mutate(vector<Chromosome*> crossed);
};

Population::Population(double (*fn)(vector<double>)) {
    this->fn = fn;
}

void Population::set(vector<Chromosome*> pop) {
    this->pop = pop;
}

void Population::randomize(int n, int argn, double from, double to) {
    for (int i = 0; i < n; ++i) {
        Chromosome* ch = new Chromosome();
        ch->randomize(argn, from, to, this->fn);
        pop.push_back(ch);
    }
}

vector<Chromosome*> Population::select() {
    int size = this->size();
    vector<Chromosome*> parents;
    for (int i = 0; i < size; ++i) {
        Chromosome* c1 = this->pop[random_i(0, size - 1)];
        Chromosome* c2 = this->pop[random_i(0, size - 1)];
        if (c1 < c2)
            parents.push_back(c2);
        else
            parents.push_back(c1);
    }
    return parents;
}

int Population::size() {
    return pop.size();
}

std::ostream &operator << (std::ostream &os, Population &obj) {
    for (auto it = obj.pop.begin(); it != obj.pop.end(); ++it)
        os << *it;
    return os;
}

std::ostream &operator << (std::ostream &os, Population* objp) {
    os << *objp;
    return os;
}


void Population::pprint() {
    cout << this;
}

double fn1(vector<double> argv) {
    double x1 = argv[0];
    double x2 = argv[1];
    return 3905.93 - 100 * (pow(x1, 2) - pow(x2, 2)) - pow(1 - x1, 2);
}

array<Chromosome*, 2> Population::cross2(Chromosome* c1, Chromosome* c2) {
    int argn1 = c1->size();
    int argn2 = c2->size();
    assert(argn1 == argn2);
    array<Chromosome*, 3> crossed;
    auto it1 = c1->begin();
    auto it2 = c2->begin();
    for ( ; it1 != c1->end() && it2 != c2->end(); ++it1, ++it2) {
        double x1 = *it1;
        double x2 = *it2;
        crossed[0]->push((x1 + x2) / 2);
        crossed[1]->push((3 * x1 - x2) / 2);
        crossed[2]->push((- x1 + 3 * x2) / 2);
    }
    // assert(crossed[0].size() == argn1)
    for (auto c = crossed.begin(); c != crossed.end(); ++c)
        (*c)->res = this->fn((*c)->argv);
    std::sort(crossed.begin(), crossed.end());
    array<Chromosome*, 2> selected_crossed = { crossed[2], crossed[1] };
    return selected_crossed;
}

vector<Chromosome*> Population::crossover(vector<Chromosome*> parents) {
    cout << "selected" << endl;
    pprint_v(parents);
    vector<Chromosome*> new_pop;
    int size = parents.size();
    for (int i = 0; i < size; ++i) {
        Chromosome* c1 = parents[random_i(0, size - 1)];
        Chromosome* c2 = parents[random_i(0, size - 1)];
        array<Chromosome*, 2> crossed = cross2(c1, c2);
        new_pop.push_back(crossed[0]);
        new_pop.push_back(crossed[1]);
    }
    cout << "new_population" << endl;
    pprint_v(new_pop);
    return new_pop;
}

vector<Chromosome*> Population::mutate(vector<Chromosome*> pop) {
    return pop;
}

void Population::iterate() {
    vector<Chromosome*> new_pop = this->mutate(this->crossover(this->select()));
    this->pop = new_pop;
}

int main(int argc, char** argv) {
    Population* pop = new Population(fn1);
    pop->randomize(N, 2, -2.048, 2.048);

    cout << "random ini" << endl;
    pop->pprint();

    pop->iterate();
    // for (int i = 0; i < ITERS; ++i) {
    //     pop->iterate();
    // }

    return 0;
}
