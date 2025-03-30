#include "src/arithmetic.h"
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

  // Number *e1 = new Number(1, make_e());
  // Number *e2 = new Number(1, make_e());
  // Number *e3 = new Number(1, make_e());
  // Number *phi = new Number(1, make_phi());
  // Number *r = add(e1, e2);
  // Number *s = add(r, phi);
  // Number *t = mul(s, e3);

  // Number *o = take(100, t);
  // Number *p = inv(o);

  // std::cout << p->to_double() << std::endl;

  // Number *foo1 = parse_SSB("RRL");
  // Number *foo2 = parse_SSB("");
  // Number *foo3 = add(foo1, foo2);

  // std::cout << foo3 << std::endl;

  // std::cout << "foo1:" << foo1 << std::endl;

  Number *n2 = parse_SSB("RRL");
  Hom H2 = {2, -1, 0, 5};
  // 2x - 1
  // -----
  //   5
  Number *h2 = hom(H2, n2);
  Number *res2 = parse_SSB("LRRRR");

  // std::cout << "h2:   " << h2 << std::endl;
  // std::cout << "res2: " << res2 << std::endl;
  // std::cout << "n2 :  " << n2 << std::endl;
  bool foo = (*h2 == *res2);
  std::cout << foo << "\n";
  std::cout << "n2 :  " << n2 << std::endl;

  // assert(*h2 == *res2);

  delete n2;
  delete h2;
  delete res2;

  return 0;
}
