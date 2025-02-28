#include <cassert>
// #include <iostream>
#include "tree.h"
#include <optional>
#include <stdexcept>
#include <vector>

Node Node::left() const { return {a + b, b, c + d, d}; }
Node Node::right() const { return {a, a + b, c, c + d}; }
double Node::toFraction() const {
  return static_cast<double>(a + b) / static_cast<double>(c + d);
}

int64_t Node::toN() const { return (a + b) * (c + d); }
int64_t Node::det() const { return a * d - b * c; }
bool Node::operator==(const Node &other) const {
  return a == other.a && b == other.b && c == other.c && d == other.d;
}

const Node I = {1, 0, 0, 1}; // Root node of the tree

Node parseSB(const std::string &str) {
  Node node = I;

  for (char ch : str) {
    if (ch == 'L') {
      node = node.left();
    } else if (ch == 'R') {
      node = node.right();
    } else {
      throw std::invalid_argument("Invalid character");
    }
  }

  return node;
}

Sqrt2Iter::Sqrt2Iter() : pos(0), current_chunk(get_chunk()) {}

std::vector<Branch> Sqrt2Iter::get_chunk() const {
  return {Branch::R, Branch::R, Branch::L, Branch::L};
}

std::optional<Branch> Sqrt2Iter::next() {
  if (pos == current_chunk.size()) {
    pos = 1;
    current_chunk = get_chunk();
    return current_chunk[0];
  } else {
    return current_chunk[pos++];
  }
}

void qToSB(int64_t n, int64_t d, std::vector<Branch> &u) {
  while (n != d) {
    if (n < d) {
      u.push_back(Branch::L);
      d -= n;
    } else {
      u.push_back(Branch::R);
      n -= d;
    }
  }
}

// Test functions
void testParseSB() {
  Node parsed = parseSB("RRRLRLLL");
  Node expected = {25, 7, 7, 2};
  assert(parsed == expected);
}

void test_phiIter() {
  Sqrt2Iter s_iter;
  for (int i = 0; i < 5; ++i) {
    auto branch = s_iter.next();
    if (i % 2 == 0) {
      assert(branch == Branch::R);
    } else {
      assert(branch == Branch::L);
    }
  }
}

void test_qToSB() {
  std::vector<Branch> u;
  qToSB(4, 3, u);
  std::vector<Branch> expected = {Branch::R, Branch::L, Branch::L};
  assert(u == expected);
}

// int main() {
//   // Run tests
//   test_parseSB();
//   test_phiIter();
//   test_qToSB();

//   // Example usage of PhiIter
//   PhiIter s_iter;
//   for (int i = 0; i < 42; ++i) {
//     auto branch = s_iter.next();
//     if (branch) {
//       std::cout << (*branch == Branch::R ? "R" : "L") << "\n";
//     }
//   }

//   return 0;
// }
