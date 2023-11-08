#pragma once
#include <vector>

typedef unsigned long long ull;

void bucket_sort(std::vector<ull>& to_be_ordered, ull max_val, ull bitmask, ull right_shift);

void radix_sort(std::vector<ull> &to_be_ordered, int k);

void quick_sort(std::vector<ull> &to_be_ordered);