#include "fns.h"
#include "config.h"
#include <assert.h>
#include <cmath>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

/*
DE JONG

WOLFRAM:
  COMMAND:
    maximize
    3905.93-100.0*(x*x-y*y)-pow(1-x,2)
    if -2.048<=x<=2.048,-2.048<=y<=2.048
  RESULT:
    {{4324.37, {x -> 0.00990099, y -> -2.048}}, {4324.37, {x -> 0.00990099, y -> 2.048}}}

THIS PROGRAM:
  PARAMS:
    POPULATION_SIZE = 10; MAX_ITERATIONS = 100; MUTANTS = 1;
  RESULT:
    Gets very close to exact point in 80 - 100 iterations
 */
double fn1(vector<double> xs) {
    double x1 = xs[0];
    double x2 = xs[1];
    return 3905.93 - 100.0 * (pow(x1, 2) - pow(x2, 2)) - pow(1 - x1, 2);
}

void test_fn1() {
    vector<double> xs = {1, 1};
    assert(fn1(xs) == 3905.93);
    if (LOG_LEVEL >= 0) cout << "fn1 OK" << endl;
}

/*
GOLDSTEIN & PRICE

WOLFRAM:
  COMMAND:
    minimize
    (1.0+pow(x+y+1.0,2)*(19.0-14.0*x+3.0*x*x-14.0*y+6.0*x*x+3.0*y*y))*
    (30.0+pow(2.0*x-3.0*y,2)*(18.0-32.0*x+12.0*x*x+48.0*y-36.0*x*x+27.0*y*y))
    if -2<=x<=2,-2<=y<=2
  RESULT:
    {-1.452142214744747*^6, {x -> 2, y -> -1.21552}}

THIS PROGRAM:
  PARAMS:
    POPULATION_SIZE = 10; MAX_ITERATIONS = 1000; MUTANTS = 1;
  RESULT:
    Finds the exact point.
*/
double fn2(vector<double> xs) {
    double x1 = xs[0];
    double x2 = xs[1];
    double f1 = 1.0 + pow(x1 + x2 + 1.0, 2) * (19.0 - 14.0 * x1 + 3.0 * pow(x1, 2) - 14.0 * x2 + 6.0 * pow(x1, 2) + 3.0 * pow(x2, 2));
    double f2 = 30.0 + pow(2.0 * x1 - 3.0 * x2, 2) * (18.0 - 32.0 * x1 + 12.0 * pow(x1, 2) + 48.0 * x2 - 36.0 * pow(x1, 2) + 27.0 * pow(x2, 2));
    return f1 * f2;
}

void test_fn2() {
    vector<double> xs = {0, -1};
    assert(fn2(xs) == 3);
    if (LOG_LEVEL >= 0) cout << "fn2 OK" << endl;
}

/*
BRANIN

WOLFRAM:
  COMMAND:
     minimize
     pow(y-5.1/4.0*7.0*7.0/22.0/22.0*x*x+5.0*7.0/22.0*x-6.0,2)+10.0*(1.0-7.0/8.0/22.0)*cos(x)+10.0
     if -5<=x<=10,-5<=y<=10
  RESULT:
     {{0.397727, {x -> 3.14159, y -> 2.27599}}, {0.397727, {x -> 9.42478, y -> 2.4718}}}

THIS PROGRAM:
  PARAMS:
    POPULATION_SIZE = 10; MAX_ITERATIONS = 1000; MUTANTS = 1;
  RESULT:
    Finds the exact point.
*/
double fn3(vector<double> xs) {
    double x1 = xs[0];
    double x2 = xs[1];
    return pow(x2 - 5.1 / 4.0 * 7.0 * 7.0 / 22.0 / 22.0 * pow(x1, 2)  + 5.0 * 7.0 / 22.0 * x1 - 6.0, 2) + 10.0 * (1.0 - 7.0 / 8.0 / 22.0) * cos(x1) + 10.0;
}

/*
MARTIN & GADDY

WOLFRAM:
  COMMAND:
  RESULT:

THIS PROGRAM:
TODO
*/
double fn4(vector<double> xs) {
    double x1 = xs[0];
    double x2 = xs[1];
    return pow(x1 - x2, 2) + pow((x1 + x2 - 10.0)/3.0, 2);
}

// ROSENBROCK 1
double fn5(vector<double> xs) {
    double x1 = xs[0];
    double x2 = xs[1];
    return 100.0 * pow(x1 * x1 - x2, 2) + pow(1.0 - x1, 2);
}

// ROSENBROCK 2
double fn6(vector<double> xs) {
    double sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += 100.0 * pow(xs[i] * xs[i] - xs[i+1], 2) + pow(1.0 - xs[i], 2);
    }
    return sum;
}

// HYPERSPHERE
double fn7(vector<double> xs) {
    double sum = 0;
    for (int i = 0; i < 6; i++) {
        sum += xs[i] * xs[i];
    }
    return sum;
}

// GRIEWANGK
double fn8(vector<double> xs) {
    // TODO:
    return 0;
}

void test_fns() {
    test_fn1();
    test_fn2();
}
