#include "tree.h"
#include <cassert>
#include <iostream>
#include <optional>
#include <vector>

int sgn(int64_t a) {
  if (a == 0)
    return 0;
  return (a > 0) ? 1 : -1;
}

std::optional<int64_t> linSgn(int64_t a, int64_t b) {
  if (a == 0 && b == 0)
    return 0;

  int sumOfSigns = sgn(a) + sgn(b);
  if (sumOfSigns > 0)
    return 1;
  if (sumOfSigns < 0)
    return -1;

  return std::nullopt;
}

int homSgn(const Node &H, const std::vector<char> &u, size_t index = 0) {
  if (index >= u.size()) {
    return sgn(H.a + H.b) * sgn(H.c + H.d);
  }

  auto nomSgn = linSgn(H.a, H.b);
  auto denomSgn = linSgn(H.c, H.d);

  if (nomSgn && denomSgn) {
    return (*nomSgn) * (*denomSgn);
  }

  if (u[index] == 'R') {
    __attribute__((musttail)) return homSgn(H.right(), u, index + 1);
  } else if (u[index] == 'L') {
    __attribute__((musttail)) return homSgn(H.left(), u, index + 1);
  } else {
    throw std::runtime_error("Invalid sequence character");
  }
}

int homSgnInf(const Node &H, Sqrt2Iter &u) {
  // if (index >= u.size()) {
  //   return sgn(H.a + H.b) * sgn(H.c + H.d);
  // }

  auto nomSgn = linSgn(H.a, H.b);
  auto denomSgn = linSgn(H.c, H.d);

  if (nomSgn && denomSgn) {
    return (*nomSgn) * (*denomSgn);
  }

  auto next = u.next();

  if (next == Branch::R) {
    __attribute__((musttail)) return homSgnInf(H.right(), u);
  } else if (next == Branch::L) {
    __attribute__((musttail)) return homSgnInf(H.left(), u);
  } else {
    throw std::runtime_error("Invalid sequence character");
  }
}

void testHomSgn() {
  Node node = {-5, 7, 1, 2};
  std::vector<char> u = {'R', 'L', 'L', 'R', 'L', 'R'};
  assert(homSgn(node, u) == 1);
  std::cout << "Test passed: Homographic sign algorithm\n";
}

void testHomSgnLarge() {
  Node node = {1, -100'000'001, 0, 2};
  std::vector<char> u(100'000'000, 'R');
  assert(homSgn(node, u) == 0);
  std::cout << "Test passed: Homographic sign algorithm for large number\n";
}

void testHomSgnSqrt2() {
  Sqrt2Iter phi;
  Node node = {100000000000, -241421356238, 0, 1};
  Node node2 = {100000000000, -241421356237, 0, 1};
  std::cout << "Test passed: Homographic sign algorithm for sqrt(2)\n";
  assert(homSgnInf(node, phi) == -1);
  assert(homSgnInf(node2, phi) == 1);
}

int main() {
  testHomSgn();
  testHomSgnLarge();
  testParseSB();
  testHomSgnSqrt2();

  // PhiIter phi;
  // std::vector<char> u(1'000'000, 'R');
  // std::cout << homSgnInf(node, phi) << "\n";

  return 0;
}
