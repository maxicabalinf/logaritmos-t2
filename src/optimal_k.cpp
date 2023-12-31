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
    for (int k = 1; k <= MAX_EXPONENT; k++) {
        file << "k=" + std::to_string(k) + " ";
    }
    file << std::endl;
}

int main(void) {
    // Crea directorio de experimentos si no existe
    std::filesystem::path exp_path{EXPERIMENTS_FOLDER};
    if (!std::filesystem::exists(exp_path)) {
        std::filesystem::create_directory(exp_path);
    }

    // Crea archivo que almacenará resultados de experimento.
    std::fstream
        k_per_u(exp_path / "k_per_u", std::ios::out | std::ios::binary),
        optimal_ks(exp_path / "optimal_ks", std::ios::out | std::ios::binary);
    write_headers(k_per_u);

    // Realiza n_repetitions por cada k por cada u.
    std::vector<int> optimals(MAX_EXPONENT);
    int n_repetitions = 1;
    for (int exponent = 1; exponent <= MAX_EXPONENT; exponent++) {
        k_per_u << "2^" + std::to_string(exponent) + " ";
        unsigned long long u = 1ULL << exponent;

        // Crea vector aleatorio.
        std::cout << "Creating random vector ...";
        std::vector<unsigned long long> radix_out_of_order(N);
        random_fill(radix_out_of_order, N, u);
        std::cout << " DONE !" << std::endl;

        // Encuentra k óptimo para el u actual.
        double min = std::numeric_limits<double>::infinity();
        int optimal_k = -1;
        for (int k = 1; k <= MAX_EXPONENT; k++) {
            std::cout << "u=2^" + std::to_string(exponent)+ ", k=" + std::to_string(k) << std::endl;
            double kth_total_time = 0.0;

            // Toma n_repetitions muestras de tiempos de ordenamiento.
            for (int repetition = 0; repetition < n_repetitions; repetition++) {
                std::vector<unsigned long long> copy = radix_out_of_order;
                std::cout << "Sorting vector ...";
                auto start = std::chrono::high_resolution_clock::now();
                radix_sort(copy, k);
                auto stop = std::chrono::high_resolution_clock::now();
                std::cout << " DONE RADIX!" << std::endl;
                auto delta_t = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(stop - start).count();
                kth_total_time += delta_t;
            }
            double kth_avg = kth_total_time / (double)n_repetitions;
            if (kth_avg < min) {
                min = kth_avg;
                optimal_k = k;
            }
            std::cout << "Writing avg. for k=" + std::to_string(k) + " ...";
            k_per_u << std::to_string(kth_avg) + " ";
            std::cout << " DONE !\n" << std::endl;
        }
        optimals[exponent - 1] = optimal_k;
        k_per_u << std::endl;
    }

    // Escribe optimos para cada u en archivo.
    std::cout << "Writing optimals in file ...";
    int len = size(optimals);
    optimal_ks.write(reinterpret_cast<const char *>(&len), sizeof(len));
    optimal_ks.write(reinterpret_cast<const char *>(&optimals[0]), optimals.size() * sizeof(int));
    std::cout << " DONE !" << std::endl;
    return 0;
}