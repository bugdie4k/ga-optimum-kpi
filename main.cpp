#include <random>
#include <chrono>
#include <ctime>
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

static const int N = 10;
static const int T = 5;

double d_random(double lower_bound, double upper_bound) {   
   std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
   std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
   return unif(re);
}

struct Point {
     double x;
     double y;
     double res;     
};

double fn1(double x1, double x2) {
    return 3905.93 - 100 * (pow(x1, 2) - pow(x2, 2)) - pow(1 - x1, 2);
}

void pprint(Point data[N]) {
    for (int i = 0; i < N; ++i) {
        cout << "fn1(" << data[i].x << ", " << data[i].y << ") = " << data[i].res << endl;
    }
}

Point selection() {
    
}

int main(int argc, char** argv) {
    // cout << fn1(1,1) << endl;
    
    // cout << d_random(-2.048, 2.048) << endl;    

    Point data[N];    
    for (int i = 0; i < N; ++i) {
        double x = d_random(-2.048, 2.048);
        double y = d_random(-2.048, 2.048);
        data[i].x = x;
        data[i].y = y;
        data[i].res = fn1(x, y);
    }

    pprint(data);
}
