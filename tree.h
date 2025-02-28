#ifndef TREE_H
#define TREE_H

#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

// Struct representing a node in the tree
struct Node {
  int64_t a, b, c, d;

  Node left() const;
  Node right() const;
  double toFraction() const;
  int64_t toN() const;
  int64_t det() const;
  bool operator==(const Node &other) const;
};

extern const Node I; // Root node of the tree

Node parseSB(const std::string &str);

enum class Branch { R, L };

class PhiIter {
private:
  size_t pos;
  std::vector<Branch> current_chunk;
  std::vector<Branch> get_chunk() const;

public:
  PhiIter();
  bool exhausted;
  std::optional<Branch> next();
};

void qToSB(int64_t n, int64_t d, std::vector<Branch> &u);

// Test functions
void test_parseSB();
void test_phiIter();
void test_qToSB();

#endif
