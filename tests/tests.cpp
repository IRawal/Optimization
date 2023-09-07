//
// Created by isha on 9/6/23.
//
#include "tests.h"
#include "../optimizers/Genetic.h"
#include "functions.h"

#include <iostream>

/* Approximate the solution to Bukin Function No. 6*/
void test_genetic() {
    Genetic opt = Genetic(2, 10000, 500, -12, 12, 0.1, 0.1, &bukin6);
    opt.optimize(10000);
    std::cout << bukin6(opt.params) << "\n";
    for (int i = 0; i < 2; i++) {
        std::cout << "x" << i <<": " << opt.params[i] << "\n";
    }
}