//
// Created by isha on 9/6/23.
//

#include "SimulatedAnnealing.h"

#include <random>
#include <iostream>

SimulatedAnnealing::SimulatedAnnealing(int param_count, float domain_min, float domain_max, float init_temp, float step_size, float (*fun)(float*)) {
    this->param_count = param_count;
    this->init_temp = init_temp;
    this->step_size = step_size;
    this->fun = fun;

    std::uniform_real_distribution<float> start_dist(domain_min, domain_max);
    std::uniform_real_distribution<float> step_dist(-step_size, step_size);

    this->start_dist = start_dist;
    this->step_dist = step_dist;

    this->params = static_cast<float*>(malloc(sizeof(float) * param_count));
    this->new_params = static_cast<float*>(malloc(sizeof(float) * param_count));

    for (int i = 0; i < param_count; i++) {
        params[i] = start_dist(gen);
    }
}
void SimulatedAnnealing::optimize(int iterations) {
    for (int k = 0; k < iterations; k++) {
        float temp = init_temp / (k + 1);
        float fit = fun(params);
        for (int i = 0; i < param_count; i++) {
            new_params[i] = params[i] + step_dist(gen);
        }
        float new_fit = fun(new_params);
        if (new_fit < fit) {
            std::copy(new_params, new_params + param_count, params);
        } else {
            float metrop_hastings = exp(-(new_fit - fit) / temp);
            if (metrop_hastings > (rand() / (RAND_MAX + 1.0))) {
                std::copy(new_params, new_params + param_count, params);
            }
        }
        std::cout << "Loss: " << fun(params) << "\n";
    }
}