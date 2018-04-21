#include "Population.h"
#include "config.h"
#include "fns.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <stdlib.h>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int more_iterations_dialog() {
    while (true) {
        cout << "Iterate more? (yNUM/n) > ";
        char a;
        cin >> a;
        if (a == 'y' || a == 'Y') {
            std::string s = "";
            getline(cin, s);
            try {
                return stoi(s, nullptr);
            }
            catch (const std::invalid_argument &e) {
                return 1;
            }
        }
        else if (a == 'n' || a == 'N') {
            return 0;
        }
        else {
            cout << endl << "WUT" << endl;
        }
    }
}

bool more(Chromosome* c1, Chromosome* c2) { return *c1 > *c2; }
bool less(Chromosome* c1, Chromosome* c2) { return *c1 < *c2; }

int main(int argc, char* argv[]) {
    // test_fns();

    // (5,5)->0
    // vector<double> xs = {5,5};
    // cout << fn4(xs) << endl;
    // return 0;

    // (1,1)->0
    // vector<double> xs = {1,1};
    // cout << fn5(xs) << endl;
    // return 0;

    Population* pop1 = new Population(fn1, 2, -2.048, 2.048, more); // close
    Population* pop2 = new Population(fn2, 2, -2, 2, less); // exact point with garbadge
    Population* pop3 = new Population(fn3, 2, -5, 10, less); // exact point with garbadge, stops by derivative
    Population* pop4 = new Population(fn4, 2, 0, 10, less); // close, stops by derivative before 5,5
    Population* pop5 = new Population(fn5, 2, -1.2, 1.2, less); // a // exact point, stops by derivative
    Population* pop6 = new Population(fn5, 2, -10, 10, less); // b // exact point, stops by derivative
    Population* pop7 = new Population(fn6, 4, -1.2, 1.2, less); // exact point, stops by derivative
    Population* pop8 = new Population(fn7, 6, -5.12, 5.12, less); // exact point, stops by derivative
    vector<Population*> pops = { pop1, pop2, pop3, pop4, pop5, pop6, pop7, pop8 };

    int fn_num = 0;
    if (argc == 2) {
        fn_num = std::strtol(argv[1], nullptr, 0) - 1;
    }

    cout << fn_num;
    Population* pop = pops[fn_num];

    pop->randomize(POPULATION_SIZE);

    if (LOG_LEVEL >= 1) {
        cout << "- random ini" << endl;
        pop->pprint();
    }

    pop->set_best_ever();

    for (pop->iter = 1; pop->iter <= MAX_ITERATIONS; ) {
        if (LOG_LEVEL >= 0) {
            cout << "   ***   ITER " << pop->iter << "   ***" << endl;
        }

        pop->iterate();
    }

    int cur_iter_limit = pop->iter;
    while (true) {
        if (pop->iter >= cur_iter_limit)
            cur_iter_limit += more_iterations_dialog();
        if (pop->iter >= cur_iter_limit)
            break;

        if (LOG_LEVEL >= 0) {
            cout << "   ***   ITER " << pop->iter << "   ***" << endl;
        }

        pop->iterate();
    };

    return 0;
}

