#include "sorting.h"

#include <omp.h>

#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

void radix_sort(std::vector<ull>& to_be_ordered, int k) {
    // TODO Implementar
}

void quick_sort(std::vector<ull>& to_be_ordered) {
    // TODO Implementar
}

void bucket_sort_inplace(std::vector<ull>& to_be_ordered, ull max_val) {
    std::vector<ull> count(max_val + 1, 0);

    // Contar la frecuencia de cada elemento
    for (ull num : to_be_ordered) {
        count[num]++;
    }

    ull index = 0;
    for (ull i = 0; i <= max_val; ++i) {
        while (count[i] > 0) {
            to_be_ordered[index++] = i;
            count[i]--;
        }
    }
}

// Función para generar un arreglo aleatorio con un tamaño y rango dados
void generateRandomArray(std::vector<ull>& arr, int size, ull range) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<ull> dis(1, range);

#pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }
}

int main() {
    int repetitions = 2;  // Número de repeticiones por tamaño de universo

    for (int power = 2; power <= 64; ++power) {
        ull u = 1ULL << power;  // Genera u = 2^power
        int size = 100000000;   // Tamaño fijo del arreglo (100 millones) - Ajustado para mantener la misma cantidad de elementos

        double total_time_radix = 0.0, total_time_quick = 0.0;

        std::vector<ull> random_numbers(size);  // Crear un único arreglo grande para los números aleatorios

        for (int rep = 0; rep < repetitions; ++rep) {
            // Generar números aleatorios en el mismo arreglo
            generateRandomArray(random_numbers, size, u);

            try {
                // Radix Sort in-place
                auto start_radix = std::chrono::steady_clock::now();
                bucket_sort_inplace(random_numbers, u);
                auto end_radix = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds_radix = end_radix - start_radix;
                total_time_radix += elapsed_seconds_radix.count();

                // Quick Sort
                auto start_quick = std::chrono::steady_clock::now();
                quick_sort(random_numbers);
                auto end_quick = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsed_seconds_quick = end_quick - start_quick;
                total_time_quick += elapsed_seconds_quick.count();
            } catch (std::bad_alloc& ba) {
                std::cerr << "Error de asignación de memoria: " << ba.what() << std::endl;
                return 1;
            }
        }

        // Imprimir resultados
        std::cout << "Universo de tamaño 2^" << power << ": \n";
        std::cout << "Tiempo promedio Radix Sort: " << total_time_radix / repetitions << " segundos\n";
        std::cout << "Tiempo promedio Quick Sort: " << total_time_quick / repetitions << " segundos\n";
    }

    return 0;
}