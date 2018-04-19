#ifndef GA_OPTIMUM_KPI_FNS_H_INCLUDED
#define GA_OPTIMUM_KPI_FNS_H_INCLUDED

#include <vector>

double fn1(std::vector<double>);
double fn2(std::vector<double>);
double fn3(std::vector<double>);
double fn4(std::vector<double>);
double fn5(std::vector<double>);
double fn6(std::vector<double>);
double fn7(std::vector<double>);
double fn8(std::vector<double>);

std::vector<double> derivatives(double (*fn)(std::vector<double>), int arity, std::vector<double> xs);

void test_fns();

#endif
