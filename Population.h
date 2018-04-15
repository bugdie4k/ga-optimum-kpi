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
     
     void randomize(int n, int argn);
     void iterate();

     void pprint();
     int size();

    private:
     std::vector<Chromosome*> select();
     std::vector<Chromosome*> crossover(std::vector<Chromosome*> selected);
     int is_in_interval(double);
     Chromosome* cross2(Chromosome* c1, Chromosome* c2);
     std::vector<Chromosome*> mutate(std::vector<Chromosome*> crossed);
};

std::ostream &operator << (std::ostream &os, Population &obj);
std::ostream &operator << (std::ostream &os, Population *objp);

#endif
