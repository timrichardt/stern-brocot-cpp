#include "src/arithmetic.h"
#include "src/bihomographic.h"
#include "src/tests.h"
#include "src/tree.h"
#include <iostream>

int main() {
  // std::cout << "Tests: ----------------" << std::endl;
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
  std::cout << "-----------------------" << std::endl;

  // Number x = parse_SSB("RRRR");
  std::unique_ptr<Number> x =
      std::make_unique<Number>(Number{1, std::make_unique<EulerIterator>()});
  std::unique_ptr<Number> x1 =
      std::make_unique<Number>(Number{1, std::make_unique<EulerIterator>()});
  std::unique_ptr<Number> y = std::make_unique<Number>(parse_SSB("RRLLLLRR"));
  Number u = parse_SSB("R");
  // std::unique_ptr<Number> f = std::make_unique<Number>(u + *y);
  // std::unique_ptr<Number> f = add(y, x1);
  // Number g;
  // Number z = add(x,y); // bihom(Bihom{0, 1, 1, 0, 0, 0, 0, 1}, std::move(x),
  // std::move(y)); std::unique_ptr<Number> z = std::make_unique<Number>(x + y);
  // std::unique_ptr<Number> z = std::make_unique<Number>(y + f);
  // std::unique_ptr<Number> g = std::make_unique<Number>(*z + u);
  std::unique_ptr<Number> foo = add(x, y);
  std::unique_ptr<Number> b = take(100, foo);
  std::unique_ptr<Number> c = add(foo, b);
  std::unique_ptr<Number> d = take(100, c);
  // std::unique_ptr<Number> k = take(100, k);

  // auto t = take(1000, g+z).to_double();
  // std::cout << std::move(y) << std::endl;
  // auto foo = take(100, x);
  std::cout << d << std::endl;
  // if (z == u) std::cout << "yip" << std::endl;
  // if (z == u) {
  // 	std::cout << "yip" << std::endl;
  // }

  // std::unique_ptr<Number> w = std::make_unique<Number>(*z + u);
  // std::cout << z << std::endl;

  return 0;
}
