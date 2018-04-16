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

int main(int argc, char** argv) {
    // test_fns();
    // return 0;

    // Population* pop = new Population(fn1, 2, -2.048, 2.048, [](Chromosome* c1, Chromosome* c2) -> bool { return *c1 > *c2; });
    Population* pop = new Population(fn2, 2, -2, 2, [](Chromosome* c1, Chromosome* c2) -> bool { return *c1 < *c2; });

    pop->randomize(POPULATION_SIZE);

    if (LOG_LEVEL >= 1) {
        cout << "- random ini" << endl;
        pop->pprint();
    }

    pop->set_best_ever();

    int iter;
    for (iter = 1; iter <= MAX_ITERATIONS; ++iter) {
        if (LOG_LEVEL >= 0) {
            cout << "   ***   ITER " << iter << "   ***" << endl;
        }

        pop->iterate();
    }

    int cur_iter_limit = iter;
    while (1) {
        if (iter >= cur_iter_limit)
            cur_iter_limit += yn();        
        if (iter >= cur_iter_limit)
            break;

        if (LOG_LEVEL >= 0) {
            cout << "   ***   ITER " << iter << "   ***" << endl;
        }

        pop->iterate();
        ++iter;
    };

    return 0;
}
