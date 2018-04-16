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

int yn() {
    while (1) {
        cout << "Iterate more? (yNUM/n) > ";
        char a;
        cin >> a;
        if (a == 'y' || a == 'Y') {
            std::string s = "";
            int n;
            getline(cin, s);
            n = stoi(s, nullptr);
            return n;
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
    // return 0;

    // Population* pop = new Population(fn1, 2, -2.048, 2.048, more);
    // Population* pop = new Population(fn2, 2, -2, 2, less);
    Population* pop = new Population(fn3, 2, -5, 10, less);

    pop->randomize(POPULATION_SIZE);

    if (LOG_LEVEL >= 1) {
        cout << "- random ini" << endl;
        pop->pprint();
    }

    pop->set_best_ever();
    
    for (pop->iter = 1; pop->iter <= MAX_ITERATIONS; ++pop->iter) {
        if (LOG_LEVEL >= 0) {
            cout << "   ***   ITER " << pop->iter << "   ***" << endl;
        }

        pop->iterate();
    }

    int cur_iter_limit = pop->iter;
    while (1) {
        if (pop->iter >= cur_iter_limit)
            cur_iter_limit += yn();
        if (pop->iter >= cur_iter_limit)
            break;

        if (LOG_LEVEL >= 0) {
            cout << "   ***   ITER " << pop->iter << "   ***" << endl;
        }

        pop->iterate();
        ++pop->iter;
    };

    return 0;
}
