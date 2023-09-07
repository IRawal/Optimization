//
// Created by isha on 9/4/23.
//
#include <random>

#ifndef OPTIMIZATION_GENETIC_H
#define OPTIMIZATION_GENETIC_H


class Genetic {
    std::uniform_real_distribution<float> dist;
    std::uniform_real_distribution<float> norm;
    std::normal_distribution<float> mut_dist;

    int pop_size;
    int param_count;
    int parent_count;

    float (*fun)(float*);
public:
    Genetic(int param_count, int pop_size, int parent_count, float domain_min, float domain_max, float randomness, float step_size, float (*fun)(float*));
    void optimize(int steps);
    float* params;
};


#endif //OPTIMIZATION_GENETIC_H
