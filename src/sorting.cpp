#include "sorting.h"

#include <bitset>
#include <iostream>
#include <utility>

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

void partition2(std::vector<ull>& a, ull low, ull high, ull& i, ull& j) {
    // To handle 2 elements
    if (high - low <= 1) {
        if (a[high] < a[low])
            std::swap(a[high], a[low]);
        i = low;
        j = high;
        return;
    }

    ull mid = low;
    ull pivot = a[high];
    while (mid <= high) {
        if (a[mid] < pivot)
            std::swap(a[low++], a[mid++]);
        else if (a[mid] == pivot)
            mid++;
        else if (a[mid] > pivot)
            std::swap(a[mid], a[high--]);
    }

    // update i and j
    i = low - 1;
    j = mid;  // or high+1
}

/**
 * @brief Ordena un vector de `unsigned long long` usando 3-way Quicksort
 *
 * @param a Vector de `unsigned long long` a ordenar
 * @param low Índice inferior del segmento a ordenar
 * @param high Índice superior del segmento a ordenar
 * @cite Implementación original de Geeks4Geeks - https://www.geeksforgeeks.org/3-way-quicksort-dutch-national-flag/
 */
void quicksort_(std::vector<ull>& a, ull low, ull high) {
    if (low >= high)  // 1 or 0 elements
        return;

    ull i, j;

    // Note that i and j are passed as reference
    partition2(a, low, high, i, j);

    // Recur
    quicksort_(a, low, i);
    quicksort_(a, j, high);
}

void quick_sort(std::vector<ull>& to_be_ordered) {
    quicksort_(to_be_ordered, 0, size(to_be_ordered) - 1);
}