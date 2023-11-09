#include "sorting.h"
#include "t2.h"

void radix_sort(std::vector<ull>& to_be_ordered, int k) {
    ull bitmask = (1 << k) - 1;
    ull right_shift = 0;
    while (right_shift < MAX_EXPONENT) {
        bucket_sort(to_be_ordered, (1 << k), bitmask, right_shift);
        bitmask <<= k;
        right_shift += k;
    }
}

void quick_sort(std::vector<ull>& to_be_ordered) {
    // TODO Implementar
}

void bucket_sort(std::vector<ull>& to_be_ordered, ull u, ull bitmask = ~0, ull right_shift = 0) {
    auto n = size(to_be_ordered);  // Tamaño de arreglo a ordenar
    std::vector<ull> count(u, 0);
    std::vector<ull> temp_ordered(n);

    // Cuenta la frecuencia de cada elemento
    for (ull num : to_be_ordered) {
        count[((num & bitmask) >> right_shift) + 1]++;
    }

    // Convierte los valores del arreglo en índices del arreglo final
    for (ull i = 1; i <= u; i++) {
        count[i] += count[i - 1];
    }

    // Llena el arreglo ordenado
    for (ull num : to_be_ordered) {
        ull num_k_bits = ((num & bitmask) >> right_shift);
        temp_ordered[count[num_k_bits]] = num;
        count[num_k_bits]++;
    }
    to_be_ordered = temp_ordered;
}