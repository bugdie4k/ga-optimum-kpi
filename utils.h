#ifndef GA_OPTIMUM_KPI_UTILS_H_INCLUDED
#define GA_OPTIMUM_KPI_UTILS_H_INCLUDED

#include <string>
#include <iostream>
#include <iomanip>

double random_d(double lower_bound, double upper_bound);

int random_i(int lower_bound, int upper_bound);

template <typename T>
void pprint_v(T v, std::string delim = "") {
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << std::setprecision(20) << *it;
        if (it != v.end() - 1)
            std::cout << delim;
    }
}

#endif
