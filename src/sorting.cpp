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

void bucket_sort(std::vector<ull>& to_be_ordered, ull max_val, ull bitmask = ~0, ull right_shift = 0) {
    std::vector<ull> count(max_val + 1, 0);
    std::vector<ull> temp_ordered(to_be_ordered.size());
    // Contar la frecuencia de cada elemento
    for (ull num : to_be_ordered) {
        count[(num & bitmask) >> right_shift]++;
    }
    for (ull i = 1; i <= max_val; i++) {
        count[i] += count[i - 1];
    }
    for (ull num : to_be_ordered) {
        ull index = count[((num & bitmask) >> right_shift) - 1];
        temp_ordered[count[((num & bitmask) >> right_shift) - 1]] = num;
        count[((num & bitmask) >> right_shift) - 1]--;
    }
    to_be_ordered = temp_ordered;
}