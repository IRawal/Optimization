//
// Created by isha on 9/4/23.
//

#include <cstdlib>
#include <random>
#include <algorithm>
#include "Genetic.h"

using namespace std;

default_random_engine gen;
uniform_real_distribution<float> dist;
uniform_real_distribution<float> norm;

int pop_size;
int param_count;
int parent_count;
float* params;

auto populations = vector<pair<float, float*>>();

float (*fun)(float*);

Genetic::Genetic(int param_count, int pop_size, int parent_count, float domain_min, float domain_max, float randomness, float step_size, float (*fun)(float*)) {
    this->pop_size = pop_size;
    this->param_count = param_count;
    this->parent_count = parent_count;

    uniform_real_distribution<float> dist(domain_min, domain_max);
    uniform_real_distribution<float> norm(0, randomness);

    float sigma = (domain_max - domain_min) * step_size;

    this->std_dist = std::normal_distribution<float>(0, step_size);
    this->dist = dist;
    this->norm = norm;

    this->fun = fun;

    populations.reserve(pop_size);
    // Take random guess at param values and sort them
    for (int i = 0; i < pop_size; i++) {
        auto params = static_cast<float*>(malloc(sizeof(float) * param_count));
        for (int k = 0; k < param_count; k++) {
            params[k] = dist(gen);
        }
        float fit = fun(params) + norm(gen); // Add randomness to fitness
        populations.emplace_back(fit, params);
    }
    sort(populations.begin(), populations.end());
}
/*
 * Bit mutation, found to lead to NaNs and Infs
void mutate(float* param, int size, float mutation_prob) {
    for (int i = 0; i < size; i++) {
        if ((rand() / (RAND_MAX + 1.0)) >= mutation_prob) {
            continue;
        }
        int tmp = * (int * ) &param[i] ^ (1 << rand() % 32);
        if (tmp < 0 || tmp > 2139095039) // Check that float can be cast correctly
            tmp = 0;
        param[i] = * (float * ) &tmp;
    }
}
 */
void mutate(float* param, int size) {
    for (int i = 0; i < size; i++) {
        param[i] += dist(gen);
    }
}
float* cross(float* p1, float* p2, int size) {
    auto baby = static_cast<float*>(malloc(sizeof(float) * size));
    for (int i = 0; i < size; i++) {
        if (rand() > (RAND_MAX / 2)) {
            baby[i] = p1[i];
        }
        else {
            baby[i] = p2[i];
        }
    }
    return baby;
}
void Genetic::optimize(int iterations) {
    for (int k = 0; k < iterations; k++) {
        for (int i = 0; i < parent_count - 1; i++) {
            float *p1 = populations[i].second;
            float *p2 = populations[i + 1].second;
            float *baby = cross(p1, p2, param_count);
            mutate(baby, param_count);
            float fit = fun(baby) + norm(gen);
            populations[pop_size - i - 1] = pair<float, float *>(fit, baby);
        }
        sort(populations.begin(), populations.end());
    }
    // Evaluate true fits
    for (int i = 0; i < parent_count - 1; i++) {
        float* p1 = populations[i].second;
        float fit = fun(p1);
        populations[i].first = fit;
    }
    this->params = populations[0].second;
}
