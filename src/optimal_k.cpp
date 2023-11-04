#include <chrono>
#include <filesystem>
#include <fstream>
#include <limits>

#include "random_utils.h"
#include "sorting.h"
#include "t2.h"

int main(void) {
    std::filesystem::path exp_path{EXPERIMENTS_FOLDER};
    if (!std::filesystem::exists(exp_path)) {
        std::filesystem::create_directory(exp_path);
    }
    std::fstream
        radix_results(exp_path / "optimal_k", std::ios::out | std::ios::binary);
    std::vector<int> optimals(MAX_K - 1);
    for (int exponent = 1; exponent <= MAX_EXPONENT; exponent++) {
        unsigned long long u = 1ULL << exponent;
        std::vector<unsigned long long> radix_out_of_order(N);
        random_fill(radix_out_of_order, N, u);
        double min = std::numeric_limits<double>::infinity();
        int optimal_k;
        for (int k = 1; k <= MAX_K; k++) {
            std::vector<unsigned long long> copy = radix_out_of_order;
            auto start = std::chrono::high_resolution_clock::now();
            radix_sort(copy, k);
            auto stop = std::chrono::high_resolution_clock::now();
            auto delta_t_radix = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(stop - start).count();
            if (delta_t_radix < min) {
                min = delta_t_radix;
                optimal_k = k;
            }
        }
        optimals[exponent - 1] = optimal_k;
    }
    // TODO WRITE VECTOR OF OPTIMALS TO FILE
    return 0;
}