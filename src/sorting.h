#pragma once
#include <vector>

typedef unsigned long long ull;

/**
 * @brief Ordena un vector con elementos de un universo discreto [0...u-1] de tamaño u según un subconjunto de bits, usando Bucket sort.
 *
 * @param to_be_ordered Vector a ordenar.
 * @param u Tamaño del universo.
 * @param bitmask Máscara de k bits consecutivos a usar para ordenar.
 * @param right_shift Desfase a aplicar a la máscara para que el menor valor filtrado sea 0.
 */
void bucket_sort(std::vector<ull> &to_be_ordered, ull u, ull bitmask, ull right_shift);

/**
 * @brief Ordena un vector con elementos de un universo discreto `[0, ..., 2^MAX_EXPONENT - 1]` usando Radix sort con rondas de a `k` bits.
 * 
 * @param to_be_ordered Vector a ordenar.
 * @param k Cantidad de bits usados por ronda.
 */
void radix_sort(std::vector<ull> &to_be_ordered, int k);


/**
 * @brief Ordena un vector de `unsigned long long` usando 3-way Quicksort
 * 
 * @param to_be_ordered Vector a ordenar.
 */
void quick_sort(std::vector<ull> &to_be_ordered);