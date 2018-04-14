#include "Population.h"
#include "utils.h"

#include <assert.h>
#include <iostream>
#include <algorithm>

using std::vector;
using std::array;
using std::cout;
using std::endl;

std::ostream &operator << (std::ostream &os, Population &obj) {
    for (auto it = obj.pop.begin(); it != obj.pop.end(); ++it)
        os << *it;
    return os;
}

std::ostream &operator << (std::ostream &os, Population *objp) {
    os << *objp;
    return os;
}

Population::Population(double (*fn)(vector<double>), double from, double to) {
    this->fn = fn;
    this->from = from;
    this->to = to;
}

void Population::set(vector<Chromosome*> pop) {
    this->pop = pop;
}

void Population::randomize(int n, int argn) {
    for (int i = 0; i < n; ++i) {
        Chromosome* ch = new Chromosome();
        ch->randomize(argn, this->from, this->to, this->fn);
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

void Population::pprint() {
    cout << this;
}

array<Chromosome*, 2> Population::cross2(Chromosome* c1, Chromosome* c2) {
    cout << "  - crossing 2" << endl;
    cout << "  " << c1 << "  " << c2;

    int argn1 = c1->size();
    int argn2 = c2->size();
    assert(argn1 == argn2);
    array<Chromosome*, 3> crossed;
    for (auto c = crossed.begin(); c != crossed.end(); ++c)
        (*c) = new Chromosome();

    for (int i = 0; i < argn1; ++i) {
        double x1 = c1->argv[i];
        double x2 = c2->argv[i];
        double crossed_arg1 = (x1 + x2) / 2;
        double crossed_arg2 = (3 * x1 - x2) / 2;
        double crossed_arg3 = (- x1 + 3 * x2) / 2;

        cout << "    - crossing arguments " << i + 1 << ": " << x1 << ", " << x2 << " -> "
             << crossed_arg1 << ", " << crossed_arg2 << ", " << crossed_arg3 << endl;

        crossed[0]->push(crossed_arg1);
        crossed[1]->push(crossed_arg2);
        crossed[2]->push(crossed_arg3);
    }
    // fill the "res" field
    for (auto c = crossed.begin(); c != crossed.end(); ++c)
        (*c)->res = this->fn((*c)->argv);

    cout << "  - 3 children of 2 crossed:" << endl;
    for (auto c = crossed.begin(); c != crossed.end(); ++c)
        cout << "  " << *c;

    std::sort(crossed.begin(), crossed.end(),
              [](Chromosome* c1, Chromosome* c2) -> bool {
                  return *c1 > *c2;
              });

    // cout << "  3 sorted children of 2 crossed:" << endl;
    // for (auto c = crossed.begin(); c != crossed.end(); ++c)
    //     cout << "  " << *c;

    array<Chromosome*, 2> selected_crossed = { crossed[0], crossed[1] };

    cout << "  - leaving:" << endl << "  " << selected_crossed[0] << "  " << selected_crossed[1] << endl;

    return selected_crossed;
}

vector<Chromosome*> Population::crossover(vector<Chromosome*> parents) {
    cout << "- selected" << endl;
    pprint_v(parents);
    vector<Chromosome*> new_pop_v;
    int size = parents.size();
    for (int i = 0; i < size; ++i) {
        Chromosome* c1 = parents[random_i(0, size - 1)];
        Chromosome* c2 = parents[random_i(0, size - 1)];
        array<Chromosome*, 2> crossed = cross2(c1, c2);
        new_pop_v.push_back(crossed[0]);
        new_pop_v.push_back(crossed[1]);
    }
    cout << "- new_population" << endl;
    pprint_v(new_pop_v);
    return new_pop_v;
}

vector<Chromosome*> Population::mutate(vector<Chromosome*> pop) {
    return pop;
}

void Population::iterate() {
    vector<Chromosome*> new_pop_v = this->mutate(this->crossover(this->select()));
    this->pop = new_pop_v;
}

