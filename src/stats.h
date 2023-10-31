#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

/**
 * @brief Tupla representando para una muestra su promedio, desviación estándar, intervalo de confianza del 99% del promedio e intervalo de confianza del 95% del promedio, respectivamente.
 *
 */
typedef std::tuple<
    double,
    double,
    std::pair<double, double>,
    std::pair<double, double>>
    stats;

/**
 * @brief Calcula el intervalo de confianza de una muestra.
 *
 * @param percentage Porcentaje de confianza.
 * @param mean Promedio de la muestra.
 * @param stdev Desviación estándar de la muestra.
 * @param n_samples Cantidad de datos de la muestra.
 * @return Un par con las cotas del intervalo.
 */
std::pair<double, double> confidence_interval(int percentage, double mean, double stdev, int n_samples = 100);

/**
 * @brief Calcula resultados agregados de una muestra.
 *
 * @param samples Muestras del evento
 * @return Objeto con resultados agregados
 */
stats calculate_stats(std::vector<double> &samples);

/**
 * @brief Agrega a un archivo los resultados agregados de las repeticiones de un experimento.
 *
 * @param file Archivo donde se guarda el resultado
 * @param N Identificador del experimento
 * @param measurements Objeto con los resultados agregados
 */
void save_results(std::fstream &file, int N, stats &measurements);