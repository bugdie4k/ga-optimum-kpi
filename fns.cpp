#include "fns.h"
#include "config.h"
#include <assert.h>
#include <cmath>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

/*
De Jong
WOLFRAM:
  > maximize
    3905.93 - 100.0 * (pow(x1, 2) - pow(x2, 2)) - pow(1 - x1, 2)
    if -2.048 <= x1 <= 2.048, -2.048 <= x2 <= 2.048
  > {{4324.37, {x1 -> 0.00990099, x2 -> -2.048}}, {4324.37, {x1 -> 0.00990099, x2 -> 2.048}}}
*/
double fn1(vector<double> xs) {
    double x1 = xs[0];
    double x2 = xs[1];
    return 3905.93d - 100.0d * (pow(x1, 2) - pow(x2, 2)) - pow(1 - x1, 2);
}

void test_fn1() {
    vector<double> xs = {1, 1};
    assert(fn1(xs) == 3905.93);
    if (LOG_LEVEL >= 0) cout << "fn1 OK" << endl;
}

/*
Goldstein & Price
WOLFRAM:
  > minimize
    (1.0+pow(x1+x2+1.0,2)*(19.0-14.0*x1+3.0*x1*x2-14.0*x2+6.0*x1*x1+3.0*x2*x2))*
    (30.0+pow(2.0*x1-3.0*x2,2)*(18.0-32.0*x1+12.0*x1*x1+48.0*x2-36.0*x1*x1+27.0*x2*x2))
    if -2<x1<2,-2<x2<2
  > {{-880057., {x1 -> 2., x2 -> -1.27921}}, {30., {x1 -> -0.6, x2 -> -0.4}}}
*/
double fn2(vector<double> xs) {
    double x1 = xs[0];
    double x2 = xs[1];
    double f1 = 1.0d + pow(x1 + x2 + 1.0d, 2) * (19.0d - 14.0d * x1 + 3.0d * pow(x1, 2) - 14.0d * x2 + 6.0d * pow(x1, 2) + 3.0d * pow(x2, 2));
    double f2 = 30.0d + pow(2.0d * x1 - 3.0d * x2, 2) * (18.0d - 32.0d * x1 + 12.0d * pow(x1, 2) + 48.0d * x2 - 36.0d * pow(x1, 2) + 27.0d * pow(x2, 2));
    return f1 * f2;
}

void test_fn2() {
    vector<double> xs = {0, -1};
    assert(fn2(xs) == 3);
    if (LOG_LEVEL >= 0) cout << "fn2 OK" << endl;
}

// Branin
double fn3(vector<double> xs) {
    double x1 = xs[0];
    double x2 = xs[1];
    return pow(x2 - 5.1d / 4.0d * 7.0d * 7.0d / 22.0d / 22.0d * x1 * x1  + 5.0d * 7.0d / 22.0d * x1 - 6.0d, 2) + 10.0d * (1.0d - 7.0d / 8.0d / 22.0d) * cos(x1) + 10.0d;
}

// Martin & Gaddy
double fn4(vector<double> xs) {
    double x1 = xs[0];
    double x2 = xs[1];
    return pow(x1 - x2, 2) + pow((x1 + x2 - 10.0d)/3.0d, 2);
}

// Rosenbrock 1
double fn5(vector<double> xs) {
    double x1 = xs[0];
    double x2 = xs[1];
    return 100.0d * pow(x1 * x1 - x2, 2) + pow(1.0d - x1, 2);
}

// Rosenbrock 2
double fn6(vector<double> xs) {
    double sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += 100.0d * pow(xs[i] * xs[i] - xs[i+1], 2) + pow(1.0d - xs[i], 2);
    }
    return sum;
}

// Hypersphere
double fn7(vector<double> xs) {
    double sum = 0;
    for (int i = 0; i < 6; i++) {
        sum += xs[i] * xs[i];
    }
    return sum;
}

// Griewangk
double fn8(vector<double> xs) {
    // TODO:
    return 0;
}

void test_fns() {
    test_fn1();    
    test_fn2();    
}
