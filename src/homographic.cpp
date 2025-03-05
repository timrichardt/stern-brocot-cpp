#include "homographic.h"
#include "tree.h"
#include <cassert>
#include <iostream>
#include <optional>
#include <vector>

std::optional<int64_t> lin_sign(int64_t a, int64_t b) {
  if (a == 0 && b == 0)
    return 0;

  int sum_of_signs = sign(a) + sign(b);
  if (sum_of_signs > 0)
    return 1;
  if (sum_of_signs < 0)
    return -1;

  return std::nullopt;
}

int hom_sign(const Node &H, const std::vector<char> &u, size_t index = 0) {
  if (index >= u.size()) {
    return sign(H.a + H.b) * sign(H.c + H.d);
  }

  auto nom_sign = lin_sign(H.a, H.b);
  auto denom_sign = lin_sign(H.c, H.d);

  if (nom_sign && denom_sign) {
    return (*nom_sign) * (*denom_sign);
  }

  if (u[index] == 'R') {
    __attribute__((musttail)) return hom_sign(H.right(), u, index + 1);
  } else if (u[index] == 'L') {
    __attribute__((musttail)) return hom_sign(H.left(), u, index + 1);
  } else {
    throw std::runtime_error("Invalid sequence character");
  }
}

int hom_sign(const Node &H, Iterator &u) {
  // if (index >= u.size()) {
  //   return sign(H.a + H.b) * sign(H.c + H.d);
  // }

  auto nom_sign = lin_sign(H.a, H.b);
  auto denom_sign = lin_sign(H.c, H.d);

  if (nom_sign && denom_sign) {
    return (*nom_sign) * (*denom_sign);
  }

  auto next = u.next();

  if (next == Branch::R) {
    __attribute__((musttail)) return hom_sign(H.right(), u);
  } else if (next == Branch::L) {
    __attribute__((musttail)) return hom_sign(H.left(), u);
  } else {
    throw std::runtime_error("Invalid sequence character");
  }
}

bool is_R_emittable(const Node &H) {
  return (H.c <= H.a && H.d < H.b) || (H.c < H.a && H.d <= H.b);
}

bool is_L_emittable(const Node &H) {
  return (H.a <= H.c && H.b < H.d) || (H.a < H.c && H.b <= H.d);
}

Node emit_R(const Node &H) { return {H.a - H.c, H.b - H.d, H.c, H.d}; }

Node emit_L(const Node &H) { return {H.a, H.b, H.c - H.a, H.d - H.b}; }

Node hom_emit(const Node &H, Iterator &u) {
  if (is_R_emittable(H)) {
    return emit_R(H);
  } else if (is_L_emittable(H)) {
    return emit_L(H);
  } else {
    auto next = u.next();
    if (next == Branch::R) {
      return H.right();
    } else {
      return H.left();
    }
  }
}

int hom_sb(const Node &H, Iterator &u) {
  if (H.det() == 0) {
    Q_to_SB((int64_t)(H.a + H.b), (int64_t)(H.c + H.d));
  } else {
    int sign = hom_sign(H, u);
    switch (sign) {
    case 0:
      return 0;
    case 1:
      return 1;
    case -1:
      return -1;
    };
  }
  return 0;
}

void test_hom_sign() {
  Node node = {-5, 7, 1, 2};
  std::vector<char> u = {'R', 'L', 'L', 'R', 'L', 'R'};
  assert(hom_sign(node, u) == 1);
  std::cout << "Test passed: Homographic sign algorithm\n";
}

void test_hom_sign_large() {
  Node node = {1, -10'000'001, 0, 2};
  std::vector<char> u(10'000'000, 'R');
  assert(hom_sign(node, u) == 0);
  std::cout << "Test passed: Homographic sign algorithm for large number\n";
}

void test_hom_sign_sqrt2() {
  ChunkedIterator phi(get_chunk_sqrt2);

  Node node = {100000000000, -241421356238, 0, 1};
  Node node2 = {100000000000, -241421356237, 0, 1};

  std::cout << "Test passed: Homographic sign algorithm for sqrt(2)\n";
  assert(hom_sign(node, phi) == -1);
  assert(hom_sign(node2, phi) == 1);
}

void test_hom_sign_e() {
  auto e1 = make_e();
  auto e2 = make_e();

  // std::vector<Branch> u1 = take(20, e1);
  // std::cout << SBtoFloat(u1) << std::endl;
  // std::vector<Branch> u2 = take(20, e2);
  // std::cout << SBtoFloat(u2) << std::endl;

  // 2.7182818
  Node node = {100000, -271829, 0, 1};
  Node node2 = {100000, -271828, 0, 1};

  assert(hom_sign(node, e1) == -1);
  assert(hom_sign(node2, e2) == 1);

  std::cout << "Test passed: Homographic sign algorithm for e\n";
}
