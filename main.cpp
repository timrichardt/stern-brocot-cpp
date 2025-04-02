#include "src/arithmetic.h"
#include "src/bihomographic.h"
#include "src/homographic.h"
#include "src/shanks.h"
#include "src/tests.h"
#include "src/tree.h"
#include <iostream>

int main() {
  std::cout << "Tests: ----------------" << std::endl;
  // test_parse_SSB();
  // test_number_comparators();
  // test_hom_sign();
  // test_hom_sign_large();
  // test_hom_sign_sqrt2();
  // test_hom_sign_e();
  // test_hom();
  // test_bihom_sign();
  // test_bihom();
  // test_arithmetic_binary();
  // test_arithmetic_chained();
  std::cout << "-----------------------" << std::endl;

  Number *a = parse_SSB("RL");
  Number *b = parse_SSB("RRRRRRR");

  Iterator *foo = new LogIterator(a, b);

  std::cout << foo << "\n";

  Iterator *p = new PowIterator(a, 2);

  Number *q = new Number(1, p);

  std::cout << "pow: " << p << std::endl;
  std::cout << "a:   " << a->to_double() << std::endl;
  std::cout << "pow: " << q->to_double() << std::endl;

  return 0;
}
