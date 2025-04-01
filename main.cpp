#include "src/arithmetic.h"
#include "src/bihomographic.h"
#include "src/homographic.h"
#include "src/shanks.h"
#include "src/tests.h"
#include "src/tree.h"
#include <iostream>

int main() {
  std::cout << "Tests: ----------------" << std::endl;
  test_parse_SSB();
  test_number_comparators();
  test_hom_sign();
  test_hom_sign_large();
  test_hom_sign_sqrt2();
  test_hom_sign_e();
  test_hom();
  test_bihom_sign();
  test_bihom();
  test_arithmetic_binary();
  test_arithmetic_chained();
  std::cout << "-----------------------" << std::endl;

  Number *a = parse_SSB("R");
  Number *b = parse_SSB("RRR");

  Iterator *foo = new LogIterator(a, b);

  std::cout << foo << "\n";

  return 0;
}
