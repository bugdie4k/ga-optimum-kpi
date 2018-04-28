#include "Population.h"
#include "utils.h"
#include "config.h"
#include "fns.h"

#include <assert.h>
#include <iostream>
#include <algorithm>
#include <cmath>

using std::vector;
using std::array;
using std::ostream;
using std::cout;
using std::endl;

ostream &operator << (ostream &os, Population &obj) {
    for (auto it = obj.pop.begin(); it != obj.pop.end(); ++it)
        os << *it;
    return os;
}

ostream &operator << (ostream &os, Population *objp) {
    os << *objp;
    return os;
}

Population::Population(double (*fn)(vector<double>), int fn_arity, double from, double to, bool (*left_is_better)(Chromosome*, Chromosome*)) {
    this->fn = fn;
    this->fn_arity = fn_arity;
    this->from = from;
    this->to = to;
    this->left_is_better = left_is_better;
    this->iter = 0;
    this->mutation_stage = 0;
}

void Population::randomize(int n) {
    for (int i = 0; i < n; ++i) {
        Chromosome* ch = new Chromosome();
        ch->randomize(this->fn_arity, this->from, this->to, this->fn);
        pop.push_back(ch);
    }
}

vector<Chromosome*> Population::select() {
    int size = this->size();
    vector<Chromosome*> parents;
    for (int i = 0; i < size; ++i) {
        Chromosome* c1 = this->pop[random_i(0, size - 1)];
        Chromosome* c2 = this->pop[random_i(0, size - 1)];
        if (c1 < c2)
            parents.push_back(c2);
        else
            parents.push_back(c1);
    }
    return parents;
}

int Population::size() {
    return pop.size();
}

void Population::pprint() {
    cout << this;
}

int Population::is_in_interval(double x) {
    if (x <= this->from)
        return -1;
    else if (x >= this->to)
        return 1;
    return 0;
}

Chromosome* Population::cross2(Chromosome* c1, Chromosome* c2) {
    if (LOG_LEVEL >= 2) {
        cout << "  - crossing 2" << endl;
        cout << "  " << c1 << "  " << c2;
    }

    int argn1 = c1->size();
    int argn2 = c2->size();
    assert(argn1 == argn2);
    array<Chromosome*, 3> crossed;
    for (auto c = crossed.begin(); c != crossed.end(); ++c)
        (*c) = new Chromosome();

    for (int i = 0; i < argn1; ++i) {
        double x1 = c1->argv[i];
        double x2 = c2->argv[i];
        double crossed_arg1 = (x1 + x2) / 2;
        double crossed_arg2 = (3 * x1 - x2) / 2;
        double crossed_arg3 = (3 * x2 - x1) / 2;

        if (LOG_LEVEL >=3) {
            cout << "    - crossing arguments " << i + 1 << ": " << x1 << ", " << x2 << " -> "
                 << crossed_arg1 << ", " << crossed_arg2 << ", " << crossed_arg3 << endl;
        }

        int is_in_interval1 = this->is_in_interval(crossed_arg1);
        if (is_in_interval1 != 0) {
            if (LOG_LEVEL >= 4) {
                cout << "      - arg exceeds: " << crossed_arg1 << endl;
            }

            if (is_in_interval1 == 1)
                crossed_arg1 = this->to;
            if (is_in_interval1 == -1)
                crossed_arg1 = this->from;

            if (LOG_LEVEL >= 4) {
                cout << "      - set to interval bound: " << crossed_arg1 << endl;
            }
        }

        int is_in_interval2 = this->is_in_interval(crossed_arg2);
        if (is_in_interval2 != 0) {
            if (LOG_LEVEL >= 4) {
                cout << "      - arg exceeds: " << crossed_arg2 << endl;
            }

            if (is_in_interval2 == 1)
                crossed_arg2 = this->to;
            if (is_in_interval2 == -1)
                crossed_arg2 = this->from;

            if (LOG_LEVEL >= 4) {
                cout << "      - set to interval bound: " << crossed_arg2 << endl;
            }
        }

        int is_in_interval3 = this->is_in_interval(crossed_arg3);
        if (is_in_interval3 != 0) {
            if (LOG_LEVEL >= 4) {
                cout << "      - arg exceeds: " << crossed_arg3 << endl;
            }

            if (is_in_interval3 == 1)
                crossed_arg3 = this->to;
            if (is_in_interval3 == -1)
                crossed_arg3 = this->from;

            if (LOG_LEVEL >= 4) {
                cout << "      - set to interval bound: " << crossed_arg3 << endl;
            }
        }

        crossed[0]->push(crossed_arg1);
        crossed[1]->push(crossed_arg2);
        crossed[2]->push(crossed_arg3);
    }
    // fill the "res" field
    for (auto c = crossed.begin(); c != crossed.end(); ++c)
        (*c)->res = this->fn((*c)->argv);

    if (LOG_LEVEL >= 3) {
        cout << "  - 3 children of 2 crossed:" << endl;
        for (auto c = crossed.begin(); c != crossed.end(); ++c)
            cout << "  " << *c;
    }

    std::sort(crossed.begin(), crossed.end(), this->left_is_better);

    if (LOG_LEVEL >= 3) {
        cout << "  - leaving among 3 chromosomes:" << endl << "  " << crossed[0] << endl;
    }

    return crossed[0];
}

vector<Chromosome*> Population::crossover(vector<Chromosome*> parents) {
    if (LOG_LEVEL >= 2) {
        cout << "- selected" << endl;
        pprint_v(parents);
    }

    vector<Chromosome*> new_pop_v;
    int size = parents.size();
    for (int i = 0; i < size; ++i) {
        Chromosome* c1 = parents[random_i(0, size - 1)];
        Chromosome* c2 = parents[random_i(0, size - 1)];
        Chromosome* child = cross2(c1, c2);
        new_pop_v.push_back(child);
    }

    if (LOG_LEVEL >= 1) {
        cout << "- new_population" << endl;
        pprint_v(new_pop_v);
    }

    return new_pop_v;
}

double mutate_arg_on_stage(double arg, int stage) {
    int sign = (random_i(0, 1)) ? 1 : -1;
    double abs_delta = pow(0.1, stage);
    // return random_d(arg, arg + sign * abs_delta);
    return arg + sign * abs_delta;
}

vector<Chromosome*> Population::mutate(vector<Chromosome*> pop) {
    if (LOG_LEVEL >= 3) {
        cout << "  - before mutation" << endl << "  ";
        pprint_v(pop, "  ");
    }

    if (LOG_LEVEL >= 0) {
        cout << "- mutation stage: " << this->mutation_stage << endl;
        cout << "- iters on stage: " << this->iters_on_stage << endl;
    }

    for (int i = 0; i < MUTANTS; ++i) {
        int random_c = random_i(0, pop.size() - 1);
        Chromosome* c = pop[random_c];
        // mutate random amount of arguments
        int random_argn = random_i(1, c->size());

        if (LOG_LEVEL >= 3) {
            cout << "    - mutating chromosome, mutating " << random_argn << " arguments" << endl << "    " << c;
        }

        for (int j = 0; j < random_argn; ++j) {
            if (this->mutation_stage == 0 || SINGLE_MUTATION_STAGE)
                c->argv[j] = random_d(this->from, this->to);
            else
                c->argv[j] = mutate_arg_on_stage(c->argv[j], this->mutation_stage);

            int is_in_interval = this->is_in_interval(c->argv[j]);
            if (is_in_interval != 0) {
                if (LOG_LEVEL >= 4) {
                    cout << "      - arg exceeds: " << c->argv[j] << endl;
                }

                if (is_in_interval == 1)
                    c->argv[j] = this->to;
                if (is_in_interval == -1)
                    c->argv[j] = this->from;

                if (LOG_LEVEL >= 4) {
                    cout << "      - set to interval bound: " << c->argv[j] << endl;
                }
            }
        }

        c->res = this->fn(c->argv);

        if (LOG_LEVEL >= 3) {
            cout << "    - chromosome after mutation" << endl << "    " << c;
        }
    }

    if (this->same_best_ever >= 100 && this->iters_on_stage >= 100 && !SINGLE_MUTATION_STAGE) {
        if (this->mutation_stage >= 12)
            this->mutation_stage = 0;
        else
            ++this->mutation_stage;
        this->iters_on_stage = 0;
    } else {
        ++this->iters_on_stage;
    }

    if (LOG_LEVEL >= 2) {
        cout << "  - after mutation" << endl << "  ";
        pprint_v(pop, "  ");
    }

    return pop;
}

void Population::set_best_ever() {
    if (this->best_ever == nullptr) {
        this->best_ever = *(this->begin());
    }

    Chromosome* new_best = this->best_ever;
    for (auto it = this->begin(); it != this->end(); ++it) {
        Chromosome* c = *it;
        if (this->left_is_better(c, this->best_ever)) {
            new_best = c;
        }
    }

    if (new_best == this->best_ever) {
        this->same_best_ever += 1;
    } else {
        this->same_best_ever = 0;
        this->best_ever = new_best;
    }

    if (LOG_LEVEL >= 0) {
        cout << "- best ever: " << this->best_ever;
        cout << "- same for: " << this->same_best_ever << endl;
    }
}

vector<Chromosome*> Population::fix_errors(vector<Chromosome*> pop) {
    if (LOG_LEVEL >= 1) {
        cout << "- fixing errors less then: " << ERROR << endl;
    }
    if (LOG_LEVEL >= 2) {
        cout << "  - population before error fixing" << endl << "  ";
        pprint_v(pop, "  ");
    }

    for (auto it = pop.begin(); it != pop.end(); ++it) {
        Chromosome* c = *it;
        for (int i = 0; i < c->size(); ++i) {
            double *intpart;
            double argf = std::abs(std::modf(c->argv[i], intpart));
            argf = std::ceil(argf * REVERSE_ERROR) / REVERSE_ERROR;
            c->argv[i] = *intpart + argf;
            // if (argf < ERROR)
            //     c->argv[i] = std::trunc(c->argv[i]);
            // if (1 - argf < ERROR)
            //     c->argv[i] = std::ceil(c->argv[i]);
        }
        c->res = this->fn(c->argv);
    }

    if (LOG_LEVEL >= 2) {
        cout << "  - population after error fixing"  << endl << "  ";
        pprint_v(pop, "  ");
    }

    return pop;
}

void Population::calc_avg_fitness() {
    this->prev_avg_fitness = this->avg_fitness;
    double avg = 0;
    for (auto it = this->begin(); it != this->end(); ++it) {
        Chromosome* c = *it;
        avg += abs(this->best_ever->res - c->res);
    }
    this->avg_fitness =  avg / this->size();
}

void Population::iterate() {
    if (this->first) {
        this->calc_avg_fitness();
        this->prev_avg_fitness = this->avg_fitness;
        this->first = false;
    }
    while (true){
        vector<Chromosome *> new_pop_v = this->mutate(this->crossover(this->select()));
        // GIVES SEGFAULT WITH -O3 ¯\_(ツ)_/¯
        /* if (this->iter % 50 == 0)
            new_pop_v = this->fix_errors(new_pop_v); */
        vector<Chromosome*> prev_prev_pop = this->prev_pop;
        this->prev_pop = this->pop;
        this->pop = new_pop_v;
        this->calc_avg_fitness();
        if (this->avg_fitness > this->prev_avg_fitness) {
            this->pop = this->prev_pop;
            this->prev_pop = prev_prev_pop;
            ++this->iter;
            continue;
        }
        break;
    }
    this->set_best_ever();
    // KLUDGE KLUDGE KLUDGES ARE EVERYWHERE
    if (CALC_DERIVATIVE && this->iter % 200 == 0) {
        vector<double> derivs = derivatives(this->fn, this->fn_arity, this->best_ever->argv);
        bool all_close2zero = true;
        for (auto d = derivs.begin(); d != derivs.end(); ++d) {
            if (std::abs(*d) >= DERIVATIVE_ERROR) {
                all_close2zero = false;
            }
        }
        if (all_close2zero) {
            cout << "    ===   ALL PARTIAL DERIVATIVES ARE CLOSE TO ZERO   ===" << endl;
            pprint_v(derivs, ", ");
            cout << endl;
            cout << "    ===   BEST EVER RESULT   ===" << endl;
            cout << this->best_ever << endl;
            exit(0);
        }

        if (LOG_LEVEL >= 0) {
            cout << "- partial derivatives: ";
            pprint_v(derivs, ", ");
            cout << endl;
        }
    }
    ++this->iter;
}
