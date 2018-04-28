#ifndef GA_OPTIMUM_KPI_CONFIG_H
#define GA_OPTIMUM_KPI_CONFIG_H

#include <iostream>

// from -1 to infinity
const int LOG_LEVEL = 0;

/// IMPORTANT
const int POPULATION_SIZE = 50;
const int MUTANTS = 15;

const int MAX_ITERATIONS = 100;

const bool SINGLE_MUTATION_STAGE = false;

const double ERROR = 1e-12;
const double REVERSE_ERROR = 1000000000000;

const double DERIVATIVE_DELTA = 1e-12;
const double DERIVATIVE_ERROR = 1e-9;
const bool CALC_DERIVATIVE = false;

#endif
