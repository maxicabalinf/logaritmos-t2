#include "sorting.h"

void radix_sort(std::vector<ull>& to_be_ordered, int k) {
    ull bitmask = (1 << k) - 1;
    ull right_shift = 0;
    while (right_shift < 64) {
        bucket_sort(to_be_ordered, (1 << k) - 1, bitmask, right_shift);
        bitmask <<= k;
        right_shift += k;
    }

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