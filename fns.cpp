#include "fns.h"
#include "config.h"
#include <assert.h>
#include <cmath>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

// DE JONG, max
// 1, 1 -> 3905.93
double fn1(vector<double> xs) {
    double x1 = xs[0];
    double x2 = xs[1];
    return 3905.93 - 100.0 * pow(x1 * x1 - x2, 2) - pow(1 - x1, 2);
}

void test_fn1() {
    vector<double> xs = {1, 1};
    assert(fn1(xs) == 3905.93);
    if (LOG_LEVEL >= 0) cout << "fn1 OK" << endl;
}

// GOLDSTEIN & PRICE, min
// 0, -1 -> 3
double fn2(vector<double> xs) {
    double x1 = xs[0];
    double x2 = xs[1];
    double f1 = 1.0 + pow(x1 + x2 + 1.0, 2) * (19.0 - 14.0 * x1 + 3.0 * x1 * x1 - 14.0 * x2 + 6.0 * x1 * x2 + 3.0 * x2 * x2);
    double f2 = 30.0 + pow(2.0 * x1 - 3.0 * x2, 2) * (18.0 - 32.0 * x1 + 12.0 * x1 * x1 + 48.0 * x2 - 36.0 * x1 * x2 + 27.0 * x2 * x2);
    return f1 * f2;
}

void test_fn2() {
    vector<double> xs = {0, -1};
    assert(fn2(xs) == 3);
    if (LOG_LEVEL >= 0) cout << "fn2 OK" << endl;
}

// BRANIN, min
double fn3(vector<double> xs) {
    double x1 = xs[0];
    double x2 = xs[1];
    return pow(x2 - 5.1 / 4.0 * 7.0 * 7.0 / 22.0 / 22.0 * x1 * x1  + 5.0 * 7.0 / 22.0 * x1 - 6.0, 2) + 10.0 * (1.0 - 7.0 / 8.0 / 22.0) * cos(x1) + 10.0;
}

// MARTIN & GADDY, min
double fn4(vector<double> xs) {
    double x1 = xs[0];
    double x2 = xs[1];
    return pow(x1 - x2, 2) + pow((x1 + x2 - 10.0)/3.0, 2);
}

/*
ROSENBROCK 1, min
a: 
b: comes close
*/ 
double fn5(vector<double> xs) {
    double x1 = xs[0];
    double x2 = xs[1];
    return 100.0 * pow(x1 * x1 - x2, 2) + pow(1.0 - x1, 2);
}

// ROSENBROCK 2, min
double fn6(vector<double> xs) {
    double sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += 100.0 * pow(xs[i] * xs[i] - xs[i+1], 2) + pow(1.0 - xs[i], 2);
    }
    return sum;
}

// HYPERSPHERE, min
double fn7(vector<double> xs) {
    double sum = 0;
    for (int i = 0; i < 6; i++) {
        sum += xs[i] * xs[i];
    }
    return sum;
}

// GRIEWANGK, max
double fn8(vector<double> xs) {
    double mul = 1, sum = 0;
      for (int i = 0; i < 10; i++) {
        sum += xs[i] * xs[i];
      }
      sum /= 4000.0f;
      for (int i = 0; i < 10; i++) {
        mul *= cos(xs[i] / sqrt(i+1));
      }
      return 1.0 / (0.1 + sum - mul + 1.0);
}

vector<double> derivatives(double (*fn)(vector<double>), int arity, vector<double> xs) {
    vector<double> partial_derivatives;
    for (int i = 0; i < arity; ++i) {
        vector<double> xs_with_delta = xs;
        xs_with_delta[i] += DERIVATIVE_DELTA;
        // cout << "(" << fn(xs_with_delta) << " - " << fn(xs) << ")" << "/" << DERIVATIVE_DELTA << endl;
        double deriv = (fn(xs_with_delta) - fn(xs)) / DERIVATIVE_DELTA;
        partial_derivatives.push_back(deriv);
    }
    return partial_derivatives;
}

void test_fns() {
    test_fn1();
    test_fn2();
}
