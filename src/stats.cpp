#include "stats.h"

std::pair<double, double> confidence_interval(int percentage, double mean, double stdev, int n_samples) {
    double sqrt_n = sqrt(n_samples);
    double offset = critical_values[percentage] * stdev / sqrt_n;
    return std::make_pair(mean - offset, mean + offset);
}

stats calculate_stats(std::vector<double> &samples) {
    std::cout << "Calculating stats ..." << std::endl;
    double sum = std::accumulate(samples.begin(), samples.end(), 0.0);
    double mean = sum / samples.size();

    std::vector<double> diff(samples.size());
    std::transform(samples.begin(), samples.end(), diff.begin(),
                   std::bind2nd(std::minus<double>(), mean));
    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / samples.size());

    return make_tuple(mean, stdev,
                      confidence_interval(99, mean, stdev),
                      confidence_interval(95, mean, stdev));
}