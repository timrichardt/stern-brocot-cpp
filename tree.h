#ifndef TREE_H
#define TREE_H

#include <cstdint>
#include <functional>
#include <iostream>
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

// std::ostream &operator<<(std::ostream &os, Branch branch) {
//   switch (branch) {
//   case Branch::R:
//     os << "R";
//   case Branch::L:
//     os << "L";
//   default:
//     os << "Unknown";
//   }
//   return os;
// }

class ChunkedIterator {
public:
  using ChunkGenerator = std::function<std::vector<Branch>()>;

  explicit ChunkedIterator(ChunkGenerator generator);
  Branch next();

private:
  ChunkGenerator generator;
  std::vector<Branch> chunk;
  size_t chunkIndex;
  void loadNextChunk();
};

std::vector<Branch> get_chunk_sqrt2();
std::vector<Branch> get_chunk_phi();

void qToSB(int64_t n, int64_t d, std::vector<Branch> &u);

// Test functions
void testParseSB();
void test_phiIter();
void test_qToSB();

#endif
