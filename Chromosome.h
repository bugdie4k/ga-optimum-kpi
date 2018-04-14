#ifndef GA_OPTIMUM_KPI_CHROMOSOME_H_INCLUDED
#define GA_OPTIMUM_KPI_CHROMOSOME_H_INCLUDED

#include <vector>
#include <iostream>

class Chromosome {
    public:
     std::vector<double> argv;
     double res;

     void set(std::vector<double> argv, double res);
     void randomize(int argn, double from, double to, double (*fn)(std::vector<double>));

     int size();
     void pprint();
     friend bool operator < (const Chromosome& l, const Chromosome& r);
     friend bool operator > (const Chromosome& l, const Chromosome& r);
     std::vector<double>::iterator begin();
     std::vector<double>::iterator end();
     void push(double arg);
};

std::ostream &operator << (std::ostream &os, Chromosome &obj);

std::ostream &operator << (std::ostream &os, Chromosome* objp);

#endif
