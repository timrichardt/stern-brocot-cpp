#include "tests.h"
#include "bihomographic.h"
#include "homographic.h"
#include "tree.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

void test_parse_SSB() {
  Number parsed_1 = parse_SSB("RLR");
  std::vector<Branch> u_1 = {Branch::R, Branch::L, Branch::R};
  Number expected_1({1, std::make_unique<SingleChunkIterator>(u_1)});

  assert(parsed_1 == expected_1);

  Number parsed_2 = parse_SSB("-RLL");
  std::vector<Branch> u_2 = {Branch::R, Branch::L, Branch::L};
  Number expected_2({-1, std::make_unique<SingleChunkIterator>(u_2)});

  assert(parsed_2 == expected_2);

  Number parsed_3 = parse_SSB("0");
  std::vector<Branch> u_3 = {};
  Number expected_3({0, std::make_unique<SingleChunkIterator>(u_3)});

  assert(parsed_3 == expected_3);

  std::cout << "Test passed: parse SSB sequences" << std::endl;
}

void test_number_comparators() {
  // ==
  Number lhs_1 = parse_SSB("RLR");
  Number rhs_1 = parse_SSB("RLR");

  assert(lhs_1 == rhs_1);
  assert((lhs_1 != rhs_1) == false);

  // !=
  Number lhs_2 = parse_SSB("RLL");
  Number rhs_2 = parse_SSB("RLR");

  assert(lhs_2 != rhs_2);
  assert((lhs_2 == rhs_2) == false);

  // <
  Number lhs_3 = parse_SSB("RLRL");
  Number rhs_3 = parse_SSB("RLR");

  assert(lhs_3 < rhs_3);
  assert((lhs_3 >= rhs_3) == false);

  // <=
  Number lhs_4 = parse_SSB("RLRL");
  Number rhs_4 = parse_SSB("RLR");

  assert(lhs_4 <= rhs_4);
  assert((lhs_4 > rhs_4) == false);

  // >
  Number lhs_5 = parse_SSB("RLRR");
  Number rhs_5 = parse_SSB("RLR");

  assert(lhs_5 > rhs_5);
  assert((lhs_5 <= rhs_5) == false);

  // >=
  Number lhs_6 = parse_SSB("RLRR");
  Number rhs_6 = parse_SSB("RLR");

  assert(lhs_6 >= rhs_6);
  assert((lhs_6 < rhs_6) == false);

  std::cout << "Test passed: number comparators" << std::endl;
}

void test_hom_sign() {
  Hom node = {-5, 7, 1, 2};
  Number n = parse_SSB("RLLRLR");

  assert(hom_sign(node, std::move(n.seq)) == 1);

  std::cout << "Test passed: Homographic sign algorithm\n";
}

void test_hom_sign_large() {
  Hom node = {1, -10'000'001, 0, 2};
  std::vector<Branch> u(10'000'000, Branch::R);
  std::unique_ptr<Iterator> ui = std::make_unique<SingleChunkIterator>(u);

  assert(hom_sign(node, std::move(ui)) == 0);

  std::cout << "Test passed: Homographic sign algorithm for large number\n";
}

void test_hom_sign_sqrt2() {
  std::unique_ptr<Iterator> sqrt2 = make_sqrt2();
  Hom node = {100000000000, -141421356238, 0, 1};
  Hom node2 = {100000000000, -141421356237, 0, 1};

  assert(hom_sign(node, std::move(sqrt2)) == -1);
  assert(hom_sign(node2, std::move(sqrt2)) == 1);

  std::cout << "Test passed: Homographic sign algorithm for sqrt(2)\n";
}

void test_hom_sign_e() {
  std::unique_ptr<Iterator> e1 = make_e();
  std::unique_ptr<Iterator> e2 = make_e();
  Hom node = {100000, -271829, 0, 1};
  Hom node2 = {100000, -271828, 0, 1};

  assert(hom_sign(node, std::move(e1)) == -1);
  assert(hom_sign(node2, std::move(e2)) == 1);

  std::cout << "Test passed: Homographic sign algorithm for e\n";
}

void test_hom() {
  Number n1 = parse_SSB("RRL");
  Hom H1 = {0, 1, 1, 0};
  // std::unique_ptr<Iterator> h1 = std::make_unique<HomIterator>(H1, n1);
  Number h1 = hom(H1, std::move(n1));
  Number res1 = parse_SSB("LLR");
  assert(h1 == res1);

  Number n2 = parse_SSB("RR");
  Hom H2 = {2, -1, 0, 5};
  Number h2 = hom(H2, std::move(n2));
  Number res2 = parse_SSB("");
  assert(h2 == res2);

  Number n3 = parse_SSB("RR");
  Hom H3 = {0, -1, -1, 5};
  Number h3 = hom(H3, std::move(n3));
  // std::cout << std::move(h3) << std::endl;
  Number res3 = parse_SSB("-L");
  assert(h3 == res3);

  std::cout << "Test passed: Homographic algorithm\n";
}

void test_bihom_sign() {
  // Bihom B1 = {0, 1, 0, 0, 0, 0, 1, 0};
  // Hom h0 = {1, 0, 0, 1};
  // Hom h1 = {1, 0, 0, 1};
  // Number n0 = fraction_to_SSB(10'000'002, 1);
  // Number n1 = fraction_to_SSB(-1, 1);
  // std::unique_ptr<Iterator> j1 = std::make_unique<HomIterator>(h0, n0);
  // std::unique_ptr<Iterator> k1 = std::make_unique<HomIterator>(h1, n1);
  // assert(bihom_sign(B1, std::move(j1), std::move(k1)) == -1);

  Bihom B1 = {0, 1, 0, -10'000'001, 0, 0, 0, 1};
  Hom h2 = {1, 0, 0, 1};
  Hom h3 = {1, 0, 0, 1};
  Number a1 = fraction_to_SSB(10'000'002, 1);
  Number b1 = fraction_to_SSB(1, 1);
  assert(bihom_sign(B1, a1.seq, b1.seq) == 1);

  Bihom B = {0, 1, 0, -10'000'001, 0, 0, 0, 1};
  Hom h4 = {1, 0, 0, 1};
  Hom h5 = {1, 0, 0, 1};
  Number n4 = fraction_to_SSB(10'000'000, 1);
  Number n5 = fraction_to_SSB(1, 1);
  std::unique_ptr<Iterator> j = std::make_unique<HomIterator>(h4, n4);
  std::unique_ptr<Iterator> k = std::make_unique<HomIterator>(h5, n5);
  assert(bihom_sign(B, j, k) == -1);

  std::cout << "Test passed: Bihomographic sign algorithm for large number\n";
}

void test_bihom() {
  Number a1 = parse_SSB("LLLR");
  Number b1 = parse_SSB("RRL");
  Bihom B1 = {1, 0, 0, -1, 1, 0, 0, 0};
  Number c1 = parse_SSB("-LLR");
  Number res1 = bihom(B1, std::move(a1), std::move(b1));
  assert(res1 == c1);

  Number a3 = parse_SSB("LRLR");
  Number b3 = parse_SSB("RRL");
  Bihom B3 = {0, 1, 0, 0, 0, 0, 1, 0};
  Number c3 = parse_SSB("LLL");
  Number res3 = bihom(B3, std::move(a3), std::move(b3));
  assert(res3 == c3);

  Number a4 = parse_SSB("LRLR");
  Number b4 = parse_SSB("RRL");
  Bihom B4 = {0, 0, 0, 1, 0, 0, 1, 0};
  Number c4 = parse_SSB("LLR");
  Number res4 = bihom(B4, std::move(a4), std::move(b4));
  assert(res4 == c4);

  // works with swapped arguments?!
  Number a2 = parse_SSB("");
  Number b2 = parse_SSB("RRL");
  Bihom B2 = {0, 0, 0, 1, 1, 0, 0, 0};
  Number c2 = parse_SSB("LLR");
  Number res2 = bihom(B2, std::move(a2), std::move(b2));
  std::cout << "res2: " << std::move(res2) << std::endl;
  assert(res2 == c2);

  std::cout << "Test passed: Bihomographic algorithm\n";
}
