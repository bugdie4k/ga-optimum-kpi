#include <random>
#include <chrono>
#include <ctime>
#include <cmath>
#include <iostream>
#include <vector>
#include <iterator>
#include <string>

using std::cout;
using std::endl;
using std::vector;
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
void pprint_v(vector<T> v, string delim = " ") {
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
};

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

     void set(vector<Chromosome*>);
     void randomize(int n, int argn, double from, double to, double (*fn)(vector<double>));
     vector<Chromosome*> select();
     void pprint();
     int size();
};

void Population::set(vector<Chromosome*> pop) {
    this->pop = pop;
}

void Population::randomize(int n, int argn, double from, double to, double (*fn)(vector<double>)) {
    for (int i = 0; i < n; ++i) {
        Chromosome* ch = new Chromosome();
        ch->randomize(argn, from, to, fn);
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

vector<Chromosome*> crossover(vector<Chromosome*> parents) {
    // TODO
}

int main(int argc, char** argv) {
    Population* pop = new Population();
    pop->randomize(N, 2, -2.048, 2.048, fn1);

    cout << "random ini" << endl;
    pop->pprint();

    cout << "selection" << endl;
    vector<Chromosome*> parents = pop->select();
    pprint_v(parents, "");

    return 0;
}
