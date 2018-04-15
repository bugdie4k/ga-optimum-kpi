#include "Population.h"

#include <cmath>
#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

static const int N = 10;
static const int ITERS = 100;

double fn1(vector<double> argv) {
    double x1 = argv[0];
    double x2 = argv[1];
    return 3905.93 - 100 * (pow(x1, 2) - pow(x2, 2)) - pow(1 - x1, 2);
}

int yn() {
    cout << "iterate? (y/n)" << endl;
    char a;
    cin >> a;
    if (a == 'y')
        return 1;
    else
        return 0;    
}

int main(int argc, char** argv) {
    Population* pop = new Population(fn1, -2.048, 2.048);
    pop->randomize(N, 2);

    cout << "- random ini" << endl;
    pop->pprint();

    while (yn()) {
        pop->iterate();
        cout << "-------------------------------------------" << endl;        
    }        
    
    // for (int i = 0; i < ITERS; ++i) {
    //     pop->iterate();
    // }

    return 0;
}
