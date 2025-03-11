#include "src/tests.h"
#include "src/tree.h"
#include <iostream>

int main() {
  test_parse_SSB();
  test_number_comparators();
  test_hom_sign();
  test_hom_sign_large();
  test_hom_sign_sqrt2();
  test_hom_sign_e();

  std::cout << "-----------------------" << std::endl;

  std::vector<Branch> u = {Branch::R, Branch::L, Branch::L, Branch::R};

  std::cout << u << std::endl;

  std::vector<Branch> v = {Branch::R, Branch::L, Branch::R};

  std::unique_ptr<Iterator> e = make_e();
  std::cout << take(50, e) << std::endl;
  std::unique_ptr<Iterator> sqrt2 = make_sqrt2();
  std::cout << take(50, sqrt2) << std::endl;
  std::unique_ptr<Iterator> phi = make_phi();
  std::cout << take(50, phi) << std::endl;

  // SingleChunkIterator b = SingleChunkIterator(u);
  // std::unique_ptr<SingleChunkIterator> c =
  //     std::make_unique<SingleChunkIterator>(b);
  // Number n = {-1, std::move(e)};
  // std::cout << std::move(n) << std::endl;

  Number m = fraction_to_SSB(-3, 4);
  std::cout << std::move(m) << std::endl;

  Number q = fraction_to_SSB(4, 1);
  Hom h = {1, 1, 0, 23};
  std::unique_ptr<Iterator> hi = std::make_unique<HomIterator>(h, q);

  std::cout << "hi: " << *hi << std::endl;

  Number q2 = fraction_to_SSB(4, 1);
  Hom h2 = {2, 1, 0, 1};
  Number n2 = hom(h2, q);

  std::cout << "n2: " << std::move(n2) << std::endl;

  return 0;
}
