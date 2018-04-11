#include <random>
#include <chrono>
#include <ctime>
#include <cmath>
#include <iostream>
#include <vector>
// #include <array>
#include <iterator>

using std::cout;
using std::endl;
using std::vector;
// using std::array;

static const int N = 10;
static const int T = 5;
static const int ITERS = 100;

// struct Point {
//      vector<double> X;
//      double res;
// };

double d_random(double lower_bound, double upper_bound) {
   std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
   std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
   return unif(re);
}

class Chromosome {
    public:
     vector<double> argv;
     double res;

     void set(vector<double> argv, double res);
     void randomize(int argn, double from, double to, double (*fn)(vector<double>));
     int size();
     void pprint();
};

void Chromosome::set(vector<double> argv, double res) {
    this->argv = argv;
    this->res = res;
}

void Chromosome::randomize(int argn, double from, double to, double (*fn)(vector<double>)) {
    for (int i = 0; i < argn; ++i)
        argv.push_back(d_random(from, to));
    res = (*fn)(argv);
}

void Chromosome::pprint() {
    cout << "fn(";
    for (auto it = argv.begin(); it != argv.end(); ++it)
        cout << *it << ", ";
    cout << ") = " << res << endl;
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
    // TODO
}

int Population::size() {
    return pop.size();
}

void Population::pprint() {
    for (vector<Chromosome*>::iterator chr = pop.begin(); chr != pop.end(); ++chr)
        (*chr)->pprint();
}

double fn1(vector<double> argv) {
    double x1 = argv[0];
    double x2 = argv[1];
    return 3905.93 - 100 * (pow(x1, 2) - pow(x2, 2)) - pow(1 - x1, 2);
}

int main(int argc, char** argv) {
    Population* pop = new Population();
    pop->randomize(10, 2, -2.048, 2.048, fn1);
    pop->pprint();
    return 0;
}
