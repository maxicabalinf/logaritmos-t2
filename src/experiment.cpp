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

int main(int argc, char *argv[]) {
    for (int exponent = 1; exponent <= 64; exponent++) {
        ull MAX_RANGE = pow(2, exponent);
        std::vector<double> radix_times(100), quick_times(100);
        for (int repetition = 0; repetition < 100; repetition++) {
            // First create an instance of an engine.
            std::random_device rnd_device;
            // Specify the engine and distribution.
            std::mt19937 mersenne_engine{rnd_device()};  // Generates random integers
            std::uniform_int_distribution<int> dist{1, MAX_RANGE};

            auto gen = [&dist, &mersenne_engine]() {
                return dist(mersenne_engine);
            };
            std::vector<ull> radix_out_of_order(N);
            generate(begin(radix_out_of_order), end(radix_out_of_order), gen);
            std::vector<ull> quick_out_of_order = radix_out_of_order;
            // Compara tiempo de ordenamiento promedio por tamaño del universo entre radix sort y quick sort
            // TODO tomar tiempo
            radix_sort(radix_out_of_order, K);

            // TODO tomar tiempo
            quick_sort(quick_out_of_order);

            // TODO registrar tiempos
        }
        // TODO calcular estadísticas
        // TODO imprimir estadísticas por u
    }
    return 0;
}