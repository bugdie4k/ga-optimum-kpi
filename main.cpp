#include "Population.h"

#include <cmath>
#include <iostream>
#include <vector>
#include <array>
#include <iterator>
#include <string>
#include <assert.h>
#include <algorithm>
#include <functional>

using std::cout;
using std::endl;
using std::vector;
using std::array;
using std::string;

static const int N = 10;
static const int ITERS = 100;

double fn1(vector<double> argv) {
    double x1 = argv[0];
    double x2 = argv[1];
    return 3905.93 - 100 * (pow(x1, 2) - pow(x2, 2)) - pow(1 - x1, 2);
}

int main(int argc, char** argv) {
    Population* pop = new Population(fn1, -2.048, 2.048);
    pop->randomize(N, 2);

    cout << "- random ini" << endl;
    pop->pprint();

    pop->iterate();
    // for (int i = 0; i < ITERS; ++i) {
    //     pop->iterate();
    // }

    return 0;
}
