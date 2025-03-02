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

int homSgn(const Node &H, ChunkedIterator &u) {
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
    __attribute__((musttail)) return homSgn(H.right(), u);
  } else if (next == Branch::L) {
    __attribute__((musttail)) return homSgn(H.left(), u);
  } else {
    throw std::runtime_error("Invalid sequence character");
  }
}

bool emitU(const Node &H) {
  return (H.c <= H.a && H.d < H.b) || (H.c < H.a && H.d <= H.b);
}

bool emitD(const Node &H) {
  return (H.a <= H.c && H.b < H.d) || (H.a < H.c && H.b <= H.d);
}

Node U(const Node &H) { return {H.a - H.c, H.b - H.d, H.c, H.d}; }

Node D(const Node &H) { return {H.a, H.b, H.c - H.a, H.d - H.b}; }

Node homEmit(const Node &H, ChunkedIterator &u) {
  if (emitU(H)) {
    return U(H);
  } else if (emitD(H)) {
    return D(H);
  } else {
    auto next = u.next();
    if (next == Branch::R) {
      return H.right();
    } else {
      return H.left();
    }
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
  ChunkedIterator phi(get_chunk_sqrt2);

  Node node = {100000000000, -241421356238, 0, 1};
  Node node2 = {100000000000, -241421356237, 0, 1};

  std::cout << "Test passed: Homographic sign algorithm for sqrt(2)\n";
  assert(homSgn(node, phi) == -1);
  assert(homSgn(node2, phi) == 1);
}

void testHomSgnE() {
  int n = 0;
  auto get_chunk_e = [&n]() -> std::vector<Branch> {
    std::vector<Branch> result;

    if (n % 2 == 0) { // If n is even
      result.push_back(Branch::R);
      result.insert(result.end(), 2 * n, Branch::L);
      result.push_back(Branch::R);
    } else { // If n is odd
      result.push_back(Branch::L);
      result.insert(result.end(), 2 * n, Branch::R);
      result.push_back(Branch::L);
    }
    n++;
    return result;
  };

  ChunkedIterator e(get_chunk_e);

  Node node = {100000000000, -241421356238, 0, 1};
  Node node2 = {100000000000, -241421356237, 0, 1};

  std::cout << "Test passed: Homographic sign algorithm for sqrt(2)\n";
  assert(homSgn(node, e) == -1);
  assert(homSgn(node2, e) == 1);
}

int main() {
  testHomSgn();
  testHomSgnLarge();
  testParseSB();
  testHomSgnSqrt2();

  Node node = {4, 2, 3, 4};
  const std::vector<Branch> x = {Branch::L, Branch::R, Branch::R, Branch::L};

  std::cout << "emittable? " << emitU(node) << "\n" << U(node).c << "\n";
  std::cout << "emittable? " << emitD(node) << "\n" << D(node).c << "\n";
  std::cout << x << "\n" << std::endl;

  return 0;
}
