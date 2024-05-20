#include <iostream>
#include <vector>
#include <iterator>
#include "Sorts.hpp"

int main() {

  std::vector<int>a{101, 214, -54, 8,7,6,5,4,3,2,1,0};
  mergeSort(a.begin(), a.end());
  print(a.begin(), a.end());
  return 0;
}
