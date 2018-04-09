#include <random>
#include <chrono>
#include <ctime>
#include <cmath>
#include <iostream>
#include <vector>
#include <iterator>

using std::cout;
using std::endl;
using std::vector;
using std::next;

static const int N = 10;
static const int T = 5;
static const int ITERS = 100;

struct Point {
     double x;
     double y;
     double res;
};

double d_random(double lower_bound, double upper_bound) {
   std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
   std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
   return unif(re);
}

double fn1(double x1, double x2) {
    return 3905.93 - 100 * (pow(x1, 2) - pow(x2, 2)) - pow(1 - x1, 2);
}

void pprint_point(Point p) {
    cout << "fn1(" << p.x << ", " << p.y << ") = " << p.res << endl;
}

void pprint(vector<Point> data) {
    for (int i = 0; i < N; ++i)
        pprint_point(data[i]);
}

vector<Point> selection(vector<Point> data) {
    for (auto it = data.begin(); it != data.end(); ++it) {
        // pprint_point(*it);
    }
    return data;
}

int main(int argc, char** argv) {
    vector<Point> data;
    for (int i = 0; i < N; ++i) {
        double x = d_random(-2.048, 2.048);
        double y = d_random(-2.048, 2.048);
        data.push_back(Point{ x, y, fn1(x,y) });
    }

    // pprint(data);

    selection(data);

    // for (int iter = 0; iter < ITERS; ++iter) {

    // }
}
