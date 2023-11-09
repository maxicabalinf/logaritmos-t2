#include "sorting.h"

#include <bitset>
#include <iostream>

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
    std::cout.setstate(std::ios_base::failbit);
    std::cout << "right_shift=" + std::to_string(right_shift) << std::endl;
    auto n = size(to_be_ordered);  // Tamaño de arreglo a ordenar
    std::vector<ull> count(u, 0);
    std::vector<ull> temp_ordered(n);

    // Cuenta la frecuencia de cada elemento
    std::cout << "Creating count array ...";
    for (ull num : to_be_ordered) {
        count[((num & bitmask) >> right_shift) + 1]++;
    }
    std::cout << " DONE !\n";

    // Convierte los valores del arreglo en índices del arreglo final
    std::cout << "Adjusting count array ...";
    for (ull i = 1; i <= u; i++) {
        count[i] += count[i - 1];
    }
    std::cout << " DONE !\n";

    // Llena el arreglo ordenado
    std::cout << "Filling final array ...";
    for (ull num : to_be_ordered) {
        ull num_k_bits = ((num & bitmask) >> right_shift);
        temp_ordered[count[num_k_bits]] = num;
        count[num_k_bits]++;
    }
    std::cout << " DONE !\n\n";
    std::cout.clear();
    to_be_ordered = temp_ordered;
}