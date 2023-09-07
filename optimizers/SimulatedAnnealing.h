//
// Created by isha on 9/6/23.
//

#ifndef OPTIMIZATION_SIMULATEDANNEALING_H
#define OPTIMIZATION_SIMULATEDANNEALING_H


#include <random>

class SimulatedAnnealing {
    int param_count;
    float init_temp;
    float step_size;
    float (*fun)(float*);
    std::default_random_engine gen;
    std::uniform_real_distribution<float> start_dist;
    std::uniform_real_distribution<float> step_dist;
    float* new_params;
public:
    SimulatedAnnealing(int param_count, float domain_min, float domain_max, float init_temp, float step_size, float (*fun)(float*));
    void optimize(int iterations);
    float* params;
};


#endif //OPTIMIZATION_SIMULATEDANNEALING_H
