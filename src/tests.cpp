#include "tests.h"
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

  assert(hom_sign(node, n.seq) == 1);

  std::cout << "Test passed: Homographic sign algorithm\n";
}

void test_hom_sign_large() {
  Hom node = {1, -10'000'001, 0, 2};
  std::vector<Branch> u(10'000'000, Branch::R);
  std::unique_ptr<Iterator> ui = std::make_unique<SingleChunkIterator>(u);

  assert(hom_sign(node, ui) == 0);

  std::cout << "Test passed: Homographic sign algorithm for large number\n";
}

void test_hom_sign_sqrt2() {
  std::unique_ptr<Iterator> sqrt2 = make_sqrt2();
  Hom node = {100000000000, -141421356238, 0, 1};
  Hom node2 = {100000000000, -141421356237, 0, 1};

  assert(hom_sign(node, sqrt2) == -1);
  assert(hom_sign(node2, sqrt2) == 1);

  std::cout << "Test passed: Homographic sign algorithm for sqrt(2)\n";
}

void test_hom_sign_e() {
  std::unique_ptr<Iterator> e1 = make_e();
  std::unique_ptr<Iterator> e2 = make_e();
  Hom node = {100000, -271829, 0, 1};
  Hom node2 = {100000, -271828, 0, 1};

  assert(hom_sign(node, e1) == -1);
  assert(hom_sign(node2, e2) == 1);

  std::cout << "Test passed: Homographic sign algorithm for e\n";
}
