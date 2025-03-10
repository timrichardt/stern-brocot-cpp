#include "src/tests.h"
#include "src/tree.h"
#include <iostream>

int main() {
  test_parse_SSB();
  test_number_comparators();

  std::cout << "------------------------------" << std::endl;

  std::vector<Branch> u = {Branch::R, Branch::L, Branch::L, Branch::R};

  std::cout << u << std::endl;

  std::vector<Branch> v = {Branch::R, Branch::L, Branch::R};

  std::unique_ptr<Iterator> a = std::make_unique<SingleChunkIterator>(v);

  // std::cout << *a << std::endl;

  SingleChunkIterator b = SingleChunkIterator(u);
  std::unique_ptr<SingleChunkIterator> c =
      std::make_unique<SingleChunkIterator>(b);
  Number n = {-1, std::move(a)};
  std::cout << std::move(n) << std::endl;

  return 0;
}
