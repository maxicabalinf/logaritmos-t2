#include <fstream>
#include <vector>
#include <iostream>

int main(void) {
  std::fstream file("experiments/optimal_ks", std::ios::in | std::ios::binary);
  int len;
  file.read(reinterpret_cast<char*>(&len), sizeof(int));
  std::vector<int> optimals(len);
  file.read(reinterpret_cast<char*>(&optimals[0]), sizeof(int)*len);
  std::cout << len << std::endl;
  for (auto i: optimals)
    std::cout << i << ' ';
  std::cout << std::endl;
  return 0;
}