#include "stats.h"

#include <fstream>
#include <functional>
#include <string>

/**
 * @brief Diccionario con los valores críticos para los intervalos de confianza del 95% y del 99%.
 *
 */
std::map<int, double> critical_values{{95, 1.96}, {99, 2.576}};

std::pair<double, double> confidence_interval(int percentage, double mean, double stdev, int n_samples) {
    double sqrt_n = sqrt(n_samples);
    double offset = critical_values[percentage] * stdev / sqrt_n;
    return std::make_pair(mean - offset, mean + offset);
}

void save_results(std::fstream &file, int N, stats &measurements) {
    file << std::to_string(N) + " ";
    file << std::get<0>(measurements) << " ";
    file << std::get<1>(measurements) << " ";
    file << "[";
    file << std::get<2>(measurements).first << ", ";
    file << std::get<2>(measurements).second << " ";
    file << "] ";
    file << "[";
    file << std::get<3>(measurements).first << ", ";
    file << std::get<3>(measurements).second << " ";
    file << "] ";
    file << std::endl;
}

stats calculate_stats(std::vector<double> &samples) {
    std::cout << "Calculating stats ..." << std::endl;
    double sum = std::accumulate(samples.begin(), samples.end(), 0.0);
    double mean = sum / samples.size();

    std::vector<double> diff(samples.size());
    std::transform(samples.begin(), samples.end(), diff.begin(),
                   std::bind(std::minus<double>(), std::placeholders::_1, mean));
    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / samples.size());

    return make_tuple(mean, stdev,
                      confidence_interval(99, mean, stdev),
                      confidence_interval(95, mean, stdev));
}