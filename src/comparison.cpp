#include <chrono>
#include <fstream>
#include <random>

#include "sorting.h"
#include "stats.h"

#define N 100000000 // Tamaño de arreglo a comparar
const std::string EXPERIMENTS_FOLDER = "./experiments";

/**
 * @brief Rellena un vector con elementos aleatorios de un universo discreto [1, u]
 *
 * @param target Vector a rellenar
 * @param upper_bound Máximo del universo
 * @cite Obtenido de StackOverflow - https://stackoverflow.com/a/23143753
 */
void random_fill(std::vector<ull> &target, ull upper_bound) {
    // First create an instance of an engine.
    std::random_device rnd_device;
    // Specify the engine and distribution.
    std::mt19937 mersenne_engine{rnd_device()};  // Generates random integers
    std::uniform_int_distribution<ull> dist{1, upper_bound};

    auto gen = [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    };
    generate(begin(target), end(target), gen);
}

/**
 * @brief Registra en archivo los tiempos de ejecución de Radix sort y Quicksort sobre un mismo vector aleatorio con elementos de un universo discreto [1, u], con u en el rango [2, 2^2, 2^3, ... , 2^64].
 */
int main(void) {
    std::fstream
        radix_results(EXPERIMENTS_FOLDER + "radix_results", std::ios::out | std::ios::binary),
        quick_results(EXPERIMENTS_FOLDER + "quick_results", std::ios::out | std::ios::binary);
    for (int exponent = 1; exponent <= 64; exponent++) {
        ull MAX_RANGE = pow(2, exponent);
        std::vector<double> radix_times, quick_times;
        int k; // TODO obtener k para cada universo
        for (int repetition = 0; repetition < 100; repetition++) {
            std::vector<ull> radix_out_of_order(N);
            random_fill(radix_out_of_order, MAX_RANGE);
            std::vector<ull> quick_out_of_order = radix_out_of_order;

            // Mide tiempos de ordenamiento
            auto start = std::chrono::high_resolution_clock::now();
            radix_sort(radix_out_of_order, k);
            auto stop = std::chrono::high_resolution_clock::now();
            auto delta_t_radix = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(stop - start).count();

            start = std::chrono::high_resolution_clock::now();
            quick_sort(quick_out_of_order);
            stop = std::chrono::high_resolution_clock::now();
            auto delta_t_quick = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(stop - start).count();

            radix_times.push_back(delta_t_radix);
            quick_times.push_back(delta_t_quick);
        }
        stats radix_stats = calculate_stats(radix_times);
        stats quick_stats = calculate_stats(quick_times);
        save_results(radix_results, MAX_RANGE, radix_stats);
        save_results(quick_results, MAX_RANGE, quick_stats);
    }
    return 0;
}