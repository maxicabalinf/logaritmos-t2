#include <chrono>
#include <random>

#include "sorting.h"
#include "stats.h"
// Tamaño n de arreglo fijo 100000000
#define N 100000000
#define K 1  // TODO fijar K definitivo
// Crear arreglos aleatorios con números entre [1,u] con u en [2, 2^2, 2^3, ..., 2^64]
// al menos 100 repeticiones por cada tamaño de universo. Cada repetición debe ser con un arreglo distinto y se debe usar el mismo arreglo para ambos métodos.
/* Comparar:
  - tiempo de ordenamiento promedio de radix sort según número de bits k y tamaño del universo.
  - tiempo de ordenamiento promedio por tamaño del universo entre radix sort y quick sort
*/

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
    for (int exponent = 1; exponent <= 64; exponent++) {
        ull MAX_RANGE = pow(2, exponent);
        std::vector<std::chrono::milliseconds> radix_times, quick_times;
        for (int repetition = 0; repetition < 100; repetition++) {
            std::vector<ull> radix_out_of_order(N);
            random_fill(radix_out_of_order, MAX_RANGE);
            std::vector<ull> quick_out_of_order = radix_out_of_order;

            // Mide tiempos de ordenamiento
            auto start = std::chrono::high_resolution_clock::now();
            radix_sort(radix_out_of_order, K);
            auto stop = std::chrono::high_resolution_clock::now();
            auto delta_t_radix = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

            auto start = std::chrono::high_resolution_clock::now();
            quick_sort(quick_out_of_order);
            auto stop = std::chrono::high_resolution_clock::now();
            auto delta_t_quick = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

            radix_times.push_back(delta_t_radix);
            quick_times.push_back(delta_t_quick);
        }
        // TODO calcular estadísticas
        // TODO imprimir estadísticas por u
    }
    return 0;
}