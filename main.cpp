#include "Genetic.h"

#include <iostream>
#include <random>

using namespace std;

float beale(float* params) {
    float x = params[0];
    float y = params[1];
    return pow((1.5 - x + x * y), 2) + pow((2.25 - x + x * pow(y, 2)), 2) + pow((2.625 - x + x * pow(y, 3)), 2) + 10;
}

int main() {
    Genetic opt = Genetic(2, 1000, 500, -10, 10, 0.0001, 0.001, &beale);
    opt.optimize(100);
    cout << beale(opt.params);
}
