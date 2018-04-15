#include "Population.h"
#include "utils.h"

#include <assert.h>
#include <iostream>
#include <algorithm>

using std::vector;
using std::array;
using std::ostream;
using std::cout;
using std::endl;

ostream &operator << (ostream &os, Population &obj) {
    for (auto it = obj.pop.begin(); it != obj.pop.end(); ++it)
        os << *it;
    return os;
}

ostream &operator << (ostream &os, Population *objp) {
    os << *objp;
    return os;
}

Population::Population(double (*fn)(vector<double>), double from, double to) {
    this->fn = fn;
    this->from = from;
    this->to = to;
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

int Population::is_in_interval(double x) {
    if (x <= this->from)
        return -1;
    else if (x >= this->to)
        return 1;
    return 0;
}

Chromosome* Population::cross2(Chromosome* c1, Chromosome* c2) {
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
        double crossed_arg3 = (3 * x2 - x1) / 2;

        cout << "    - crossing arguments " << i + 1 << ": " << x1 << ", " << x2 << " -> "
             << crossed_arg1 << ", " << crossed_arg2 << ", " << crossed_arg3 << endl;

        int is_in_interval1 = this->is_in_interval(crossed_arg1);
        if (is_in_interval1 != 0) {
            cout << "      - arg exceeds: " << crossed_arg1 << endl;
            if (is_in_interval1 == 1)
                crossed_arg1 = this->to;
            if (is_in_interval1 == -1)
                crossed_arg1 = this->from;
            cout << "      - set to interval bound: " << crossed_arg1 << endl;
        }

        int is_in_interval2 = this->is_in_interval(crossed_arg2);
        if (is_in_interval2 != 0) {
            cout << "      - arg exceeds: " << crossed_arg2 << endl;
            if (is_in_interval2 == 1)
                crossed_arg2 = this->to;
            if (is_in_interval2 == -1)
                crossed_arg2 = this->from;
            cout << "      - set to interval bound: " << crossed_arg2 << endl;
        }

        int is_in_interval3 = this->is_in_interval(crossed_arg3);
        if (is_in_interval3 != 0) {
            cout << "      - arg exceeds: " << crossed_arg3 << endl;
            if (is_in_interval3 == 1)
                crossed_arg3 = this->to;
            if (is_in_interval3 == -1)
                crossed_arg3 = this->from;
            cout << "      - set to interval bound: " << crossed_arg3 << endl;
        }        

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

    cout << "  - leaving among 3 chromosomes:" << endl << "  " << crossed[0] << endl;

    return crossed[0];
}

vector<Chromosome*> Population::crossover(vector<Chromosome*> parents) {
    cout << "- selected" << endl;
    pprint_v(parents);
    vector<Chromosome*> new_pop_v;
    int size = parents.size();
    for (int i = 0; i < size; ++i) {
        Chromosome* c1 = parents[random_i(0, size - 1)];
        Chromosome* c2 = parents[random_i(0, size - 1)];
        Chromosome* child = cross2(c1, c2);
        new_pop_v.push_back(child);
        // new_pop_v.push_back(crossed[1]);
    }
    cout << "- new_population" << endl;
    pprint_v(new_pop_v);
    return new_pop_v;
}

vector<Chromosome*> Population::mutate(vector<Chromosome*> pop) {
    // TODO: continue here
    return pop;
}

void Population::iterate() {
    vector<Chromosome*> new_pop_v = this->mutate(this->crossover(this->select()));
    this->pop = new_pop_v;
}
