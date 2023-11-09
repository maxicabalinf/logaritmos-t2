#pragma once
#include <vector>

typedef unsigned long long ull;

/**
 * @brief Ordena un vector con elementos de un universo discreto [0...u-1] de tamaño u.
 *
 * @param to_be_ordered Vector a ordenar.
 * @param u Tamaño del universo.
 * @param bitmask Máscara de k bits consecutivos a usar para ordenar.
 * @param right_shift Desfase a aplicar a la máscara para que el menor valor filtrado sea 0.
 */
void bucket_sort(std::vector<ull> &to_be_ordered, ull u, ull bitmask, ull right_shift);

void radix_sort(std::vector<ull> &to_be_ordered, int k);

void quick_sort(std::vector<ull> &to_be_ordered);