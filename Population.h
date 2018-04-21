#ifndef GA_OPTIMUM_KPI_POPULATION_H_INCLUDED
#define GA_OPTIMUM_KPI_POPULATION_H_INCLUDED

#include "Chromosome.h"
#include <array>

class Population {
    public:
     std::vector<Chromosome*> pop;
     double (*fn)(std::vector<double>);
     int fn_arity;
     bool (*left_is_better)(Chromosome*, Chromosome*);
     double from;
     double to;
     Chromosome* best_ever = nullptr;
     int iter = 0;
     int same_best_ever = 0;
     int mutation_stage = 0;
     int iters_on_stage = 0;

     explicit Population(double (*fn)(std::vector<double>), int fn_arity, double from, double to, bool (*left_is_better)(Chromosome*, Chromosome*));

     void randomize(int n);
     void set_best_ever();
     void iterate();

     std::vector<Chromosome*>::iterator begin() { return this->pop.begin(); };
     std::vector<Chromosome*>::iterator end() { return this->pop.end(); };
     void pprint();
     int size();

    private:
     std::vector<Chromosome*> select();
     std::vector<Chromosome*> crossover(std::vector<Chromosome*> selected);
     int is_in_interval(double);
     Chromosome* cross2(Chromosome* c1, Chromosome* c2);
     std::vector<Chromosome*> fix_errors(std::vector<Chromosome*> pop);
     std::vector<Chromosome*> mutate(std::vector<Chromosome*> crossed);
};

std::ostream &operator << (std::ostream &os, Population &obj);
std::ostream &operator << (std::ostream &os, Population *objp);

#endif
