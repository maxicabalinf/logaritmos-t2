#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

typedef std::tuple<
    double,
    double,
    std::pair<double, double>,
    std::pair<double, double>>
    stats;

std::map<int, double> critical_values{{95, 1.96}, {99, 2.576}};

std::pair<double, double> confidence_interval(int percentage, double mean, double stdev, int n_samples = 100);

stats calculate_stats(std::vector<double> &samples);