#include "tests.h"
#include "arithmetic.h"
#include "bihomographic.h"
#include "homographic.h"
#include "tree.h"
#include <cassert>
#include <iostream>
#include <vector>

void test_parse_SSB() {
  Number *parsed_1 = parse_SSB("RLR");
  std::vector<Branch> u_1 = {Branch::R, Branch::L, Branch::R};
  Number *expected_1 = new Number(1, new SingleChunkIterator(u_1));

  assert(*parsed_1 == *expected_1);

  Number *parsed_2 = parse_SSB("-RLL");
  std::vector<Branch> u_2 = {Branch::R, Branch::L, Branch::L};
  Number *expected_2 = new Number(-1, new SingleChunkIterator(u_2));

  assert(*parsed_2 == *expected_2);

  Number *parsed_3 = parse_SSB("0");
  std::vector<Branch> u_3 = {};
  Number *expected_3 = new Number(0, new SingleChunkIterator(u_3));

  assert(*parsed_3 == *expected_3);

  std::cout << "Test passed: parse SSB sequences" << std::endl;
}

void test_number_comparators() {
  // ==
  Number *lhs_1 = parse_SSB("RLR");
  Number *rhs_1 = parse_SSB("RLR");

  assert(*lhs_1 == *rhs_1);
  assert((*lhs_1 != *rhs_1) == false);

  delete lhs_1;
  delete rhs_1;

  // !=
  Number *lhs_2 = parse_SSB("RLL");
  Number *rhs_2 = parse_SSB("RLR");

  assert(*lhs_2 != *rhs_2);
  assert((*lhs_2 == *rhs_2) == false);

  delete lhs_2;
  delete rhs_2;

  // <
  Number *lhs_3 = parse_SSB("RLRL");
  Number *rhs_3 = parse_SSB("RLR");

  assert(*lhs_3 < *rhs_3);
  assert((*lhs_3 >= *rhs_3) == false);

  delete lhs_3;
  delete rhs_3;

  Number *lhs_31 = parse_SSB("RLLRLLLLLL");
  Number *rhs_31 = parse_SSB("RLLRLLR");

  assert(*lhs_31 < *rhs_31);
  assert((*lhs_31 >= *rhs_31) == false);

  delete lhs_31;
  delete rhs_31;

  // <=
  Number *lhs_4 = parse_SSB("RLRL");
  Number *rhs_4 = parse_SSB("RLR");

  assert(*lhs_4 <= *rhs_4);
  assert((*lhs_4 > *rhs_4) == false);

  delete lhs_4;
  delete rhs_4;

  // >
  Number *lhs_5 = parse_SSB("RLRR");
  Number *rhs_5 = parse_SSB("RLR");

  assert(*lhs_5 > *rhs_5);
  assert((*lhs_5 <= *rhs_5) == false);

  delete lhs_5;
  delete rhs_5;

  // >=
  Number *lhs_6 = parse_SSB("RLRR");
  Number *rhs_6 = parse_SSB("RLR");

  assert(*lhs_6 >= *rhs_6);
  assert((*lhs_6 < *rhs_6) == false);

  delete lhs_6;
  delete rhs_6;

  std::cout << "Test passed: number comparators" << std::endl;
}

void test_hom_sign() {
  Hom node = {-5, 7, 1, 2};
  Number *n = parse_SSB("RLLRLR");

  assert(hom_sign(node, n->seq) == 1);

  delete n;

  std::cout << "Test passed: homographic sign algorithm\n";
}

void test_hom_sign_large() {
  Hom node = {1, -10'000'001, 0, 2};
  std::vector<Branch> u(10'000'000, Branch::R);
  Iterator *ui = new SingleChunkIterator(u);

  assert(hom_sign(node, ui) == 0);

  delete ui;

  std::cout << "Test passed: homographic sign algorithm for large number\n";
}

void test_hom_sign_sqrt2() {
  Iterator *sqrt21 = make_sqrt2();
  Iterator *sqrt22 = make_sqrt2();
  Hom node1 = {100000000000, -141421356238, 0, 1};
  Hom node2 = {100000000000, -141421356237, 0, 1};

  assert(hom_sign(node1, sqrt21) == -1);
  assert(hom_sign(node2, sqrt22) == 1);

  delete sqrt21;
  delete sqrt22;

  std::cout << "Test passed: homographic sign algorithm for sqrt(2)\n";
}

void test_hom_sign_e() {
  Iterator *e1 = make_e();
  Iterator *e2 = make_e();
  Hom node1 = {100000, -271829, 0, 1};
  Hom node2 = {100000, -271828, 0, 1};

  assert(hom_sign(node1, e1) == -1);
  assert(hom_sign(node2, e2) == 1);

  delete e1;
  delete e2;

  std::cout << "Test passed: homographic sign algorithm for e\n";
}

void test_hom() {
  Number *n1 = parse_SSB("RRL");
  Hom H1 = {0, 1, 1, 0};
  Number *h1 = hom(H1, n1);
  Number *res1 = parse_SSB("LLR");

  assert(*h1 == *res1);

  delete n1;
  delete h1;
  delete res1;

  Number *n2 = parse_SSB("RR");
  Hom H2 = {2, -1, 0, 5};
  Number *h2 = hom(H2, n2);
  Number *res2 = parse_SSB("");

  assert(*h2 == *res2);

  delete n2;
  delete h2;
  delete res2;

  Number *n3 = parse_SSB("RR");
  Hom H3 = {0, -1, -1, 5};
  Number *h3 = hom(H3, n3);
  Number *res3 = parse_SSB("-L");

  assert(*h3 == *res3);

  delete n3;
  delete h3;
  delete res3;

  Number *n4 = parse_SSB("RR");
  Hom H4 = {1, -1, -1, 4};
  Number *h4 = hom(H4, n4);
  Number *res4 = parse_SSB("R");

  assert(*h4 == *res4);

  delete n4;
  delete h4;
  delete res4;

  Number *n5 = parse_SSB("LL");
  Hom H5 = {1, 0, 0, 2};
  Number *h5 = hom(H5, n5);
  Number *res5 = parse_SSB("LLLLL");
  assert(*h5 == *res5);

  delete n5;
  delete h5;
  delete res5;

  std::cout << "Test passed: homographic algorithm\n";
}

void test_bihom_sign() {
  Bihom B1 = {0, 1, 0, -10'000'001, 0, 0, 0, 1};
  Number *a1 = fraction_to_SSB(10'000'002, 1);
  Number *b1 = fraction_to_SSB(1, 1);
  assert(bihom_sign(B1, a1->seq, b1->seq) == 1);

  Bihom B2 = {0, 1, 0, -10'000'001, 0, 0, 0, 1};
  Number *a2 = fraction_to_SSB(10'000'000, 1);
  Number *b2 = fraction_to_SSB(1, 1);
  assert(bihom_sign(B2, a2->seq, b2->seq) == -1);

  Bihom B3 = {1, -1, -2, 0, 0, 0, 0, 1};
  Number *a3 = fraction_to_SSB(4, 1);
  Number *b3 = fraction_to_SSB(2, 1);
  assert(bihom_sign(B3, a3->seq, b3->seq) == 0);

  Bihom B4 = {0, 3, -2, 0, 1, 0, 0, 0};
  Number *a4 = fraction_to_SSB(2, 3);
  Number *b4 = fraction_to_SSB(1, 1);
  assert(bihom_sign(B4, a4->seq, b4->seq) == 0);

  std::cout << "Test passed: bihomographic sign algorithm\n";
}

void test_bihom() {
  Number *a1 = parse_SSB("LLLR");
  Number *b1 = parse_SSB("RRL");
  Bihom B1 = {1, 0, 0, -1, 1, 0, 0, 0};
  Number *c1 = parse_SSB("-LLR");
  Number *res1 = bihom(B1, a1, b1);
  assert(*res1 == *c1);

  delete a1;
  delete b1;
  delete c1;
  delete res1;

  Number *a2 = parse_SSB("");
  Number *b2 = parse_SSB("RRL");
  Bihom B2 = {0, 0, 0, 1, 1, 0, 0, 0};
  Number *c2 = parse_SSB("LLR");
  Number *res2 = bihom(B2, b2, a2);
  assert(*res2 == *c2);

  delete a2;
  delete b2;
  delete c2;
  delete res2;

  Number *a3 = parse_SSB("LRLR");
  Number *b3 = parse_SSB("RRL");
  Bihom B3 = {0, 1, 0, 0, 0, 0, 1, 0};
  Number *c3 = parse_SSB("LLL");
  Number *res3 = bihom(B3, a3, b3);
  assert(*res3 == *c3);

  delete a3;
  delete b3;
  delete c3;
  delete res3;

  Number *a4 = parse_SSB("LRLR");
  Number *b4 = parse_SSB("RRL");
  Bihom B4 = {0, 0, 0, 1, 0, 1, 0, 0};
  Number *c4 = parse_SSB("RLRL");
  Number *res4 = bihom(B4, a4, b4);
  assert(*res4 == *c4);

  delete a4;
  delete b4;
  delete c4;
  delete res4;

  Number *a5 = parse_SSB("RL");
  Number *b5 = parse_SSB("-R");
  Bihom B5 = {0, 1, 1, 0, 0, 0, 0, 1};
  Number *c5 = parse_SSB("-L");
  Number *res5 = bihom(B5, b5, a5);
  assert(*res5 == *c5);

  delete a5;
  delete b5;
  delete c5;
  delete res5;

  Number *a6 = parse_SSB("RL");
  Number *b6 = parse_SSB("-R");
  Bihom B6 = {1, 0, 0, 0, 0, 0, 0, 1};
  Number *c6 = parse_SSB("-RR");
  Number *res6 = bihom(B6, b6, a6);
  assert(*res6 == *c6);

  delete a6;
  delete b6;
  delete c6;
  delete res6;

  Number *a7 = parse_SSB("RL");
  Number *b7 = parse_SSB("-R");
  Bihom B7 = {0, 0, 0, -3, 0, 0, 0, 1};
  Number *c7 = parse_SSB("-RR");
  Number *res7 = bihom(B7, b7, a7);
  assert(*res7 == *c7);

  delete a7;
  delete b7;
  delete c7;
  delete res7;

  Number *a8 = new Number(1, make_e());
  Number *b8 = new Number(1, make_phi());
  Bihom B8 = {0, 1, 1, 0, 0, 0, 0, 1};
  Number *c8 = parse_SSB("-RR");
  Number *res8 = bihom(B8, a8, b8);
  double res8_d = take(100, res8)->to_double();
  assert(res8_d < 4.33633);
  assert(res8_d >= 4.33631);

  delete a8;
  delete b8;
  delete c8;
  delete res8;

  std::cout << "Test passed: bihomographic algorithm\n";
}

void test_arithmetic_binary() {
  Number *x1 = parse_SSB("R");
  Number *y1 = parse_SSB("RRL");
  Number *z1 = parse_SSB("RRRRL");
  Number *res1 = add(x1, y1);
  assert(*res1 == *z1);

  delete x1;
  delete y1;
  delete z1;
  delete res1;

  Number *x2 = parse_SSB("R");
  Number *y2 = parse_SSB("RRL");
  Number *z2 = parse_SSB("-L");
  Number *res2 = sub(x2, y2);
  assert(*res2 == *z2);

  delete x2;
  delete y2;
  delete z2;
  delete res2;

  Number *x3 = parse_SSB("R");
  Number *y3 = parse_SSB("RRL");
  Number *z3 = parse_SSB("RRRR");
  Number *res3 = mul(x3, y3);
  assert(*res3 == *z3);

  delete x3;
  delete y3;
  delete z3;
  delete res3;

  Number *x4 = parse_SSB("RRRR");
  Number *y4 = parse_SSB("R");
  Number *z4 = parse_SSB("RRL");
  Number *res4 = div(x4, y4);
  assert(*res4 == *z4);

  delete x4;
  delete y4;
  delete z4;
  delete res4;

  Number *x5 = new Number(1, make_e());
  Number *y5 = parse_SSB("R");
  Number *z5 = parse_SSB("RLLRLLLLL");
  Number *res5 = sub(x5, y5);
  assert(*res5 < *z5);

  delete x5;
  delete y5;
  delete z5;
  delete res5;

  std::cout << "Test passed: binary arithmetic operations\n";
}
