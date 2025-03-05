#include "src/homographic.h"
#include "src/tree.h"
#include <cassert>
#include <iostream>
#include <optional>
#include <vector>

int main() {
  test_hom_sign();
  test_hom_sign_large();
  test_parse_SB();
  test_hom_sign_sqrt2();
  test_hom_sign_e();

  Node node = {4, 2, 3, 4};
  const std::vector<Branch> x = {Branch::L, Branch::R, Branch::R, Branch::L};

  std::cout << "emittable? " << is_R_emittable(node) << "\n"
            << emit_R(node).c << "\n";
  std::cout << "emittable? " << is_L_emittable(node) << "\n"
            << emit_L(node).c << "\n";
  std::cout << x << "\n" << std::endl;

  auto e = make_e();

  // std::cout << take(100, e) << std::endl;

  SingleChunkIterator y({Branch::L, Branch::R});

  // std::cout << take(100, y) << std::endl;

  int s = 1;
  std::vector<Branch> p = {Branch::L, Branch::R, Branch::L};
  std::vector<Branch> q = {};

  Number numb = {1, p};

  ChunkedIterator e2 = make_e();

  Number numb2 = {-1, std::nullopt, e2};

  Number numb3 = {1, std::nullopt, y};

  Number numb4 = {1, q};

  std::cout << numb << std::endl;
  std::cout << numb2 << std::endl;
  std::cout << numb3 << std::endl;
  std::cout << numb4 << std::endl;

  return 0;
}
