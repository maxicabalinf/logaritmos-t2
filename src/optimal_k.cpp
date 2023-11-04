#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>

#include "random_utils.h"
#include "sorting.h"
#include "t2.h"

void write_headers(std::fstream &file) {
    file << "u ";
    for (int k = 1; k < MAX_EXPONENT; k++) {
        file << "k=" + std::to_string(k) + " ";
    }
}

int main(void) {
    // Crea directorio de experimentos si no existe
    std::filesystem::path exp_path{EXPERIMENTS_FOLDER};
    if (!std::filesystem::exists(exp_path)) {
        std::filesystem::create_directory(exp_path);
    }

    // Crea archivo que almacenará resultados de experimento.
    std::fstream
        radix_results(exp_path / "optimal_k", std::ios::out | std::ios::binary);
    write_headers(radix_results);
    
    // Realiza 100 ordenamientos por cada k por cada u.
    std::vector<int> optimals(MAX_K - 1);
    int n_repetitions = 100;
    for (int exponent = 1; exponent <= MAX_EXPONENT; exponent++) {
        std::cout << "u=2^" + std::to_string(exponent) << std::endl;
        radix_results << "2^" + std::to_string(exponent) +" ";
        unsigned long long u = 1ULL << exponent;

        // Crea vector aleatorio.
        std::cout << "Creating random vector ...";
        std::vector<unsigned long long> radix_out_of_order(N);
        random_fill(radix_out_of_order, N, u);
        std::cout << " DONE !" << std::endl;

        // Encuentra k óptimo para el u actual.
        double min = std::numeric_limits<double>::infinity();
        int optimal_k;
        for (int k = 1; k <= MAX_EXPONENT; k++) {
            std::cout << "k=" + std::to_string(k) << std::endl;
            double kth_total_time = 0.0;

            // Toma n_repetitions muestras de tiempos de ordenamiento.
            for (int repetition = 0; repetition < n_repetitions; repetition++) {
                std::vector<unsigned long long> copy = radix_out_of_order;
                std::cout << "Sorting vector ...";
                auto start = std::chrono::high_resolution_clock::now();
                radix_sort(copy, k);
                auto stop = std::chrono::high_resolution_clock::now();
                std::cout << " DONE !" << std::endl;
                auto delta_t = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(stop - start).count();
            }
            double kth_avg = kth_total_time / (double)n_repetitions;
            if (kth_avg < min) {
                min = kth_avg;
                optimal_k = k;
            }
            std::cout << "Writing avg. for k=" + std::to_string(k) + " ...";
            radix_results << std::to_string(kth_avg) +" ";
            std::cout << " DONE !" << std::endl;
        }
        optimals[exponent - 1] = optimal_k;
        radix_results << std::endl;
    }
    // TODO WRITE VECTOR OF OPTIMALS TO FILE
    return 0;
}