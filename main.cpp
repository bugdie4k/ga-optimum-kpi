#include "Population.h"
#include "config.h"

#include <cmath>
#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

static const int N = 10;
static const int ITERS = 10;

// De Jong
double fn1(vector<double> xs) {
    double x1 = xs[0];
    double x2 = xs[1];
    return 3905.93d - 100.0d * (pow(x1, 2) - pow(x2, 2)) - pow(1 - x1, 2);
}

// Goldstein & Price
double fn2(vector<double> xs) {
    double x1 = xs[0];
    double x2 = xs[1];
    double f1 = 1.0d + pow(x1 + x2 + 1.0d, 2) * (19.0d - 14.0d * x1 + 3.0d * x1 * x1 - 14.0d * x2 + 6.0d * x1 * x1 + 3.0d * x2 * x2);
    double f2 = 30.0d + pow(2.0d * x1 - 3.0d * x2, 2) * (18.0d - 32.0d * x1 + 12.0d * x1 * x1 + 48.0d * x2 - 36.0d * x1 * x1 + 27.0d * x2 * x2);
    return f1 * f2;
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

int yn() {
    cout << "Iterate more? (y/n) > ";
    char a;
    cin >> a;
    if (a == 'y')
        return 1;
    else
        return 0;
}

int main(int argc, char** argv) {
    Population* pop = new Population(fn1, 2, -2.048, 2.048, [](Chromosome* c1, Chromosome* c2) -> bool { return *c1 > *c2; });
    pop->randomize(N);

    if (LOGS >= 1) {
        cout << "- random ini" << endl;
        pop->pprint();
    }

    pop->set_best_ever();

    int iter;
    for (iter = 0; iter < ITERS; ++iter) {
        if (LOGS >= 1) {
            cout << "   ***   ITER " << iter << "   ***" << endl;
        }

        pop->iterate();
    }

    while (yn()) {
        if (LOGS >= 1) {
            cout << "   ***   ITER " << iter << "   ***" << endl;
        }

        pop->iterate();
    }

    return 0;
}
