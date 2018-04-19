#include "Population.h"
#include "config.h"
#include "fns.h"

#include <iostream>
#include <vector>
#include <sstream>

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

int main(int argc, char** argv) {
    // test_fns();


    // (5,5)->0
    // vector<double> xs = {5,5};
    // cout << fn4(xs) << endl;
    // return 0;

    // (1,1)->0
    // vector<double> xs = {1,1};
    // cout << fn5(xs) << endl;
    // return 0;

    // Population* pop = new Population(fn1, 2, -2.048, 2.048, more);
    // Population* pop = new Population(fn2, 2, -2, 2, less);
    // Population* pop = new Population(fn3, 2, -5, 10, less);
    // Population* pop = new Population(fn4, 2, 0, 10, less);    
    Population* pop = new Population(fn5, 2, -1.2, 1.2, less); // a
    // Population* pop = new Population(fn5, 2, -10, 10, less); // b
    // Population* pop = new Population(fn6, 4, -1.2, 1.2, less);
    // Population* pop = new Population(fn7, 6, -5.12, 5.12, less);

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

