#include <omp.h>

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <random>

#include "random_utils.h"
#include "sorting.h"
#include "stats.h"
#include "t2.h"

/**
 * @brief Registra en archivo los tiempos de ejecución de Radix sort y Quicksort sobre un mismo vector aleatorio con elementos de un universo discreto [1, u], con u en el rango [2, 2^2, 2^3, ... , 2^64].
 */
int main(void) {
    // Crea directorio de experimentos si no existe
    std::filesystem::path exp_path{EXPERIMENTS_FOLDER};
    if (!std::filesystem::exists(exp_path)) {
        std::filesystem::create_directory(exp_path);
    }

    // Crea archivos que almacenarán resultados de experimento.
    std::fstream
        radix_results(exp_path / "radix_results", std::ios::out | std::ios::binary),
        quick_results(exp_path / "quick_results", std::ios::out | std::ios::binary);

    // Lee archivo con los óptimos para cada u.
    std::fstream optimals_file(exp_path / "optimal_ks", std::ios::in | std::ios::binary);
    int optimals_len;
    optimals_file.read(reinterpret_cast<char*>(&optimals_len), sizeof(int));
    std::vector<int> optimals(optimals_len);
    optimals_file.read(reinterpret_cast<char*>(&optimals[0]), sizeof(int) * optimals_len);
    optimals_file.close();

    try {
        // Realiza 100 ordenamientos por cada tamaño de universo 2^exponent.
        for (int exponent = 1; exponent <= optimals_len; exponent++) {
            ull u = 1ULL << exponent;
            std::cout << "u=2^" + std::to_string(exponent) << std::endl;
            std::vector<double> radix_times, quick_times;
            int k = optimals[exponent - 1];
            for (int repetition = 0; repetition < 100; repetition++) {
                // Crea vector aleatorio común.
                std::cout << "Creating random vector ...";
                std::vector<ull> radix_out_of_order(N);
                random_fill(radix_out_of_order, N, u);
                std::vector<ull> quick_out_of_order = radix_out_of_order;
                std::cout << " DONE !" << std::endl;

                // Mide tiempo de ordenamiento de Radix sort.
                std::cout << "Sorting Radix sort vector ...";
                auto start = std::chrono::high_resolution_clock::now();
                radix_sort(radix_out_of_order, k);
                auto stop = std::chrono::high_resolution_clock::now();
                std::cout << " DONE !" << std::endl;
                auto delta_t_radix = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(stop - start).count();

                // Mide tiempo de ordenamiento de Quicksort.
                std::cout << "Sorting Quicksort vector ...";
                start = std::chrono::high_resolution_clock::now();
                quick_sort(quick_out_of_order);
                stop = std::chrono::high_resolution_clock::now();
                std::cout << " DONE !" << std::endl;
                auto delta_t_quick = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(stop - start).count();

                // Almacena resultados de eventos.
                radix_times.push_back(delta_t_radix);
                quick_times.push_back(delta_t_quick);
            }

            // Procesa muestra de 100 eventos por método.
            stats radix_stats = calculate_stats(radix_times);
            stats quick_stats = calculate_stats(quick_times);

            // Guarda resultados en archivo.
            save_results(radix_results, u, radix_stats);
            save_results(quick_results, u, quick_stats);
            std::cout << "SAVED !" << std::endl;
        }
    } catch (std::bad_alloc& ba) {
        std::cerr << "Memory error: " << ba.what() << std::endl;
        return 1;
    }
    return 0;
}