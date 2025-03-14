#include "src/bihomographic.h"
#include "src/tests.h"
#include "src/tree.h"
#include <iostream>

int main() {
  // test_parse_SSB();
  // test_number_comparators();
  // test_hom_sign();
  // test_hom_sign_large();
  // test_hom_sign_sqrt2();
  // test_hom_sign_e();
  // test_hom();
  // test_bihom_sign();
  test_bihom();

  std::cout << "-----------------------" << std::endl;

  // std::vector<Branch> u = {Branch::R, Branch::L, Branch::L, Branch::R};

  // std::cout << u << std::endl;

  // std::vector<Branch> v = {Branch::R, Branch::L, Branch::R};

  // std::unique_ptr<Iterator> e = make_e();
  // std::cout << *take(50, e) << std::endl;
  // std::unique_ptr<Iterator> sqrt2 = make_sqrt2();
  // std::cout << *take(50, sqrt2) << std::endl;
  // std::unique_ptr<Iterator> phi = make_phi();
  // std::cout << *take(50, phi) << std::endl;

  // // SingleChunkIterator b = SingleChunkIterator(u);
  // // std::unique_ptr<SingleChunkIterator> c =
  // //     std::make_unique<SingleChunkIterator>(b);
  // // Number n = {-1, std::move(e)};
  // // std::cout << std::move(n) << std::endl;

  // Number m = fraction_to_SSB(1, 5);
  // std::cout << std::move(m) << std::endl;

  // Number q = fraction_to_SSB(1, 1);
  // Hom h = {1, 1, 0, 23};
  // std::unique_ptr<Iterator> hi = std::make_unique<HomIterator>(h, q);

  // std::cout << "hi: " << *hi << std::endl;

  // Number q2 = fraction_to_SSB(4, 3);
  // Hom h2 = {0, 1, -1, 0};
  // Number n2 = hom(h2, q2);

  // Hom h3 = {1, 0, 0, 1};
  // Number ee = {1, make_e()};
  // Number n3 = hom(h3, ee);

  // std::cout << "n2: " << std::move(n2) << std::endl;
  // std::cout << "ee: " << std::move(take(50, ee)) << std::endl;
  // std::cout << "n3: " << std::move(take(50, n3)) << std::endl;
  // std::cout << "n3: " << take(50, n3).to_double() << std::endl;

  Bihom B2 = {0, 0, 0, 1, 0, 0, 0, 0};
  Bihom B2_2 = {0, 0, 0, 1, 0, 1, 0, 0};
  // Number n6 = fraction_to_SSB(42, 23);
  Number n6 = parse_SSB("R");
  // Number n7 = fraction_to_SSB(1, 1);
  Number n7 = parse_SSB("RRL");
  Number n6_2 = parse_SSB("R");
  Number n7_2 = parse_SSB("RRL");

  // std::unique_ptr<Iterator> bi = std::make_unique<BihomIterator>(B2, n6, n7);
  // std::unique_ptr<Iterator> i2 = std::make_unique<BihomIterator>(B2, n6, n7);
  // Number ks = {1, std::make_unique<BihomIterator>(B2, n6, n7)};
  // Number ks1 = {1, std::make_unique<BihomIterator>(B2_2, n6_2, n7_2)};

  // Number ks2 = {1, std::make_unique<BihomIterator>(B2, n6, n7)};
  // std::cout << "bi: " << bi << std::endl;

  // Number ks1 = bihom(B2_2, std::move(n6_2), std::move(n7_2));

  // std::cout << "a:   " << std::move(n6) << std::endl;
  // std::cout << "b:   " << std::move(n7) << std::endl;
  // std::cout << "res: " << std::move(ks1) << std::endl << std::endl;

  // // 1st run differs from 2nd run
  // Number n3 = parse_SSB("RR");
  // Hom H3 = {1, 0, -1, 5};
  // Number h3 = hom(H3, std::move(n3));
  // Number res3 = parse_SSB("RL");
  // std::cout << "1st run: " << std::move(h3) << std::endl;

  // Number n4 = parse_SSB("RR");
  // Hom H4 = {1, 0, -1, 5};
  // // std::cout << "H4: " << H4;
  // // std::cout << "n4: " << std::move(n4) << std::endl;
  // Number h4 = hom(H4, std::move(n4));
  // Number res4 = parse_SSB("RL");
  // std::cout << "2nd run: " << std::move(h4) << std::endl;

  return 0;
}
