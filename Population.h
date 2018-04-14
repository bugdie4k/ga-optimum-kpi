#ifndef GA_OPTIMUM_KPI_POPULATION_H_INCLUDED
#define GA_OPTIMUM_KPI_POPULATION_H_INCLUDED

#include "Chromosome.h"
#include <array>

class Population {
    public:
     std::vector<Chromosome*> pop;
     double (*fn)(std::vector<double>);
     double from;
     double to;

     explicit Population(double (*fn)(std::vector<double>), double from, double to);

     void set(std::vector<Chromosome*>);
     void randomize(int n, int argn);
     void iterate();

     void pprint();
     int size();

    private:
     std::vector<Chromosome*> select();
     std::vector<Chromosome*> crossover(std::vector<Chromosome*> selected);
     std::array<Chromosome*, 2> cross2(Chromosome* c1, Chromosome* c2);
     std::vector<Chromosome*> mutate(std::vector<Chromosome*> crossed);
};

std::ostream &operator << (std::ostream &os, Population &obj);
std::ostream &operator << (std::ostream &os, Population *objp);

#endif
