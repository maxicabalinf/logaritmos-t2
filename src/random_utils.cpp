#include "random_utils.h"

#include <omp.h>

#include <random>

void random_fill(std::vector<unsigned long long>& target, int size, unsigned long long upper_bound) {
    // First create an instance of an engine.
    std::random_device rnd_device;
    // Specify the engine and distribution.
    std::mt19937 mersenne_engine{rnd_device()};  // Generates random integers
    std::uniform_int_distribution<unsigned long long> dist{1, upper_bound};

#pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        target[i] = dist(mersenne_engine);
    }
}