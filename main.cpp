#include "Genetic.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <cfloat>
#include <cstring>
#include <bit>

using namespace std;

float fitness(float* params) {
    float x = params[0];
    float y = params[1];
    return pow((1.5 - x + x * y), 2) + pow((2.25 - x + x * pow(y, 2)), 2) + pow((2.625 - x + x * pow(y, 3)), 2);
}

int main() {
    Genetic opt = Genetic(2, 10000, 9500, -10, 10, 0.5, &fitness);
    opt.optimize(100);
    cout << fitness(opt.params);
}
