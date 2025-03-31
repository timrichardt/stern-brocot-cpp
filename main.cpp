#include "src/arithmetic.h"
#include "src/bihomographic.h"
#include "src/homographic.h"
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
  test_bihom();
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

  // Number *n2 = parse_SSB("RR");
  // Hom H2 = {2, -1, 0, 5};
  // // 2x - 1
  // // ------
  // //   5
  // Number *h2 = hom(H2, n2);
  // Number *res2 = parse_SSB("");

  // std::cout << "h2:   " << h2 << std::endl;
  // std::cout << "res2: " << res2 << std::endl;
  // std::cout << "n2 :  " << n2 << std::endl;
  // bool foo = (*h2 == *res2);
  // std::cout << foo << "\n";
  // std::cout << "n2 :  " << n2 << std::endl;

  // assert(*h2 == *res2);

  // Number *a2 = parse_SSB("");
  // Number *b2 = parse_SSB("RRL");
  // Bihom B2 = {0, 0, 0, 1, 1, 0, 0, 0};
  // Number *c2 = parse_SSB("LLR");
  // Number *res2 = bihom(B2, a2, b2);
  // bool foo = (*res2 == *c2);

  // std::cout << "res2:" << res2 << "\n";
  // std::cout << "c2:  " << c2 << "\n";
  // std::cout << "foo: " << foo << "\n";

  // Number *n2 = parse_SSB("RR");
  // Hom H2 = {3, -1, 0, 5};
  // // // 2x - 1
  // // // ------
  // // //   5
  // Number *h2 = hom(H2, n2);
  // Number *res2 = parse_SSB("");

  // std::cout << "res2:" << res2 << "\n";
  // std::cout << "c2:  " << n2 << "\n";
  // std::cout << "h2:  " << h2 << "\n";
  return 0;
}
