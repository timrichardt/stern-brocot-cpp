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

  Number *a = parse_SSB("RR");
  Number *b = parse_SSB("RRRRRRRLR");

  Iterator *foo = new LogIterator(a, b);

  // std::cout << take(16, foo) << "\n";
  std::cout << a->to_double() << "\n";
  std::cout << b->to_double() << "\n";

  Number *bar = take(12, new Number(1, foo));
  std::cout << bar << "\n";
  std::cout << bar->to_double() << "\n";
  // std::cout << bar->to_double() << "\n";

  // Iterator *p = new PowIterator(a, 1);

  // Number *q = pow(a, 2);

  // std::cout << "a:   " << a->to_double() << std::endl;
  // std::cout << "pow: " << q->to_double() << std::endl;

  // std::cout << (parse_SSB("") < parse_SSB("RRR")) << std::endl;

  return 0;
}
