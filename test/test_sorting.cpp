#include "assert.h"
#include "sorting.h"

void test_bucket_sort(void) {
    std::vector<ull> sortee = {1, 20, 39, 47, 28, 8};
    std::vector<ull> expected = {1, 8, 20, 28, 39, 47};
    bucket_sort(sortee);
    assert(sortee == expected);
}

void test_radix_sort(void) {
    std::vector<ull> sortee = {1, 20, 39, 47, 28, 8};
    std::vector<ull> expected = {1, 8, 20, 28, 39, 47};
    radix_sort(sortee, 1);
    assert(sortee == expected);
}

int main(void) {
    test_bucket_sort();
    test_radix_sort();
    return 0;
}