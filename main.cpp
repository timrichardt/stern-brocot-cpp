#include "src/arithmetic.h"
#include "src/bihomographic.h"
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
  // test_arithmetic_binary();
  std::cout << "-----------------------" << std::endl;

  // Number x = parse_SSB("RRRR");
  std::unique_ptr<Number> x =
      std::make_unique<Number>(Number{1, std::make_unique<EulerIterator>()});
  std::unique_ptr<Number> x1 =
      std::make_unique<Number>(Number{1, std::make_unique<EulerIterator>()});
  std::unique_ptr<Number> x2 =
      std::make_unique<Number>(Number{1, std::make_unique<EulerIterator>()});
  // std::unique_ptr<Number> y = std::make_unique<Number>(parse_SSB("-"));
  std::unique_ptr<Number> u = std::make_unique<Number>(parse_SSB("-RRRR"));
  // auto foo = add(x1, x);
  // // auto foo_100 = take(1000, foo);
  // // std::cout << foo_100->to_double() << std::endl;
  // auto bar = add(foo, x2);
  // auto bar_100 = take(50, foo);
  // std::cout << bar_100->to_double() << std::endl;

  std::unique_ptr<Number> a = bihom(Bihom{0, 1, 1, 0, 0, 0, 0, 1}, x, x1);
  std::unique_ptr<Number> b = bihom(Bihom{0, 1, 1, 0, 0, 0, 0, 1}, a, u);
  std::unique_ptr<Number> b_100 = take(100, b);
  std::cout << b_100 << std::endl;

  // auto asd = bar->seq->next();
  // auto asd2 = bar->seq->next();
  // auto asd3 = bar->seq->next();
  // auto asd4 = bar->seq->next();
  //  auto asd5 = bar->seq->next();
  //  auto asd6 = bar->seq->next();

  // std::cout << *asd << std::endl;
  // std::cout << *asd2 << std::endl;
  // if (asd3) {
  //   std::cout << *asd3 << std::endl;
  // } else {
  //   std::cout << "x" << std::endl;
  // }
  // std::cout << *asd4 << std::endl;
  // std::cout << *asd5 << std::endl;
  // std::cout << *asd6 << std::endl;

  return 0;
}
