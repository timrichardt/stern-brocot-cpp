#include "src/tree.h"
#include "src/homographic.h"
#include <cassert>
#include <iostream>
#include <optional>
#include <vector>

int main() {
  testHomSgn();
  testHomSgnLarge();
  testParseSB();
  testHomSgnSqrt2();
  testHomSgnE();

  Node node = {4, 2, 3, 4};
  const std::vector<Branch> x = {Branch::L, Branch::R, Branch::R, Branch::L};

  std::cout << "emittable? " << emitU(node) << "\n" << U(node).c << "\n";
  std::cout << "emittable? " << emitD(node) << "\n" << D(node).c << "\n";
  std::cout << x << "\n" << std::endl;

  return 0;
}
