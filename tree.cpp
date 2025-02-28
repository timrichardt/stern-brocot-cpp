#include <cassert>
// #include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>

struct Node {
  int64_t a, b, c, d;

  Node left() const { return {a + b, b, c + d, d}; }

  Node right() const { return {a, a + b, c, c + d}; }

  double toFraction() const {
    return static_cast<double>(a + b) / static_cast<double>(c + d);
  }

  int64_t toN() const { return (a + b) * (c + d); }

  int64_t det() const { return a * d - b * c; }

  bool operator==(const Node &other) const {
    return a == other.a && b == other.b && c == other.c && d == other.d;
  }
};

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

enum class Branch { R, L };

class PhiIter {
  size_t pos;
  std::vector<Branch> current_chunk;

  std::vector<Branch> get_chunk() const { return {Branch::R, Branch::L}; }

public:
  PhiIter() : pos(0), current_chunk(get_chunk()) {}

  std::optional<Branch> next() {
    if (pos == current_chunk.size()) {
      pos = 1;
      current_chunk = get_chunk();
      return current_chunk[0];
    } else {
      return current_chunk[pos++];
    }
  }
};

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
void test_parseSB() {
  Node parsed = parseSB("RRRLRLLL");
  Node expected = {25, 7, 7, 2};
  assert(parsed == expected);
}

void test_phiIter() {
  PhiIter s_iter;
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
