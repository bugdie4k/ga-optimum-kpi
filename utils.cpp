#include "utils.h"
#include <iostream>
#include <random>
#include <chrono>
#include <ctime>

using std::string;
using std::cout;
using std::endl;

double random_d(double lower_bound, double upper_bound) {
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> uni(lower_bound, upper_bound);
    return uni(re);
}

int random_i(int lower_bound, int upper_bound) {
    std::random_device rd;   // only used once to initialise (seed) engine
    std::mt19937 rng(rd());  // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(lower_bound, upper_bound);
    return uni(rng);
}
