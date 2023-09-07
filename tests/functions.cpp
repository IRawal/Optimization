//
// Created by isha on 9/6/23.
//

#include "functions.h"

#include <cmath>

float beale(float* params) {
    float x = params[0];
    float y = params[1];
    return pow((1.5 - x + x * y), 2) + pow((2.25 - x + x * pow(y, 2)), 2) + pow((2.625 - x + x * pow(y, 3)), 2);
}
float bukin6(float* params) {
    return 100 * sqrtf(std::abs(params[1] - 0.01 * pow(params[0], 2))) + 0.01 * std::abs(params[0] + 10);
}