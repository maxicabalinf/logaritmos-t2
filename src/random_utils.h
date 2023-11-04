#include <vector>

/**
 * @brief Rellena un vector con elementos aleatorios de un universo discreto [1, u]
 *
 * @param target Vector a rellenar
 * @param upper_bound Máximo del universo
 * @cite Obtenido de StackOverflow - https://stackoverflow.com/a/23143753
 */
void random_fill(std::vector<unsigned long long>& target, int size, unsigned long long upper_bound);