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
  test_arithmetic_binary();
  std::cout << "-----------------------" << std::endl;

  // Number x = parse_SSB("RRRR");
  Number x = {1, std::make_unique<EulerIterator>()};
  Number x1 = {1, std::make_unique<EulerIterator>()};
  Number y = parse_SSB("RRLL");
  // Number u = parse_SSB("RRRRLL");
  Number f = parse_SSB("");
  // Number g;
  // Number z = add(x,y); // bihom(Bihom{0, 1, 1, 0, 0, 0, 0, 1}, std::move(x),
  // std::move(y)); std::unique_ptr<Number> z = std::make_unique<Number>(x + y);
  Number z = (x + x1);
  // Number g = u + f;
  // Number b = take(100, x);
  // Number w = z * f;
  // Number k = take(100, x);

  // auto t = take(1000, g+z).to_double();
  // std::cout << std::move(y) << std::endl;
  std::cout << take(100, z).to_double() << std::endl;
  // if (z == u) std::cout << "yip" << std::endl;
  // if (z == u) {
  // 	std::cout << "yip" << std::endl;
  // }

  // std::unique_ptr<Number> w = std::make_unique<Number>(*z + u);
  // std::cout << z << std::endl;

  return 0;
}
