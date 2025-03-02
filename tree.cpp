#include <cassert>
// #include <iostream>
#include "tree.h"
#include <optional>
#include <stdexcept>
#include <vector>

std::ostream &operator<<(std::ostream &os, Branch branch) {
  switch (branch) {
  case Branch::R:
    return os << "R";
  case Branch::L:
    return os << "L";
  }
}

std::ostream &operator<<(std::ostream &os, std::vector<Branch> path) {
  os << "[";
  for (const auto &branch : path) {
    os << branch;
  }
  os << "]";
  return os;
}

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

ChunkedIterator::ChunkedIterator(ChunkGenerator generator)
    : generator(generator), chunkIndex(0) {
  loadNextChunk();
}

Branch ChunkedIterator::next() {
  if (chunk.empty()) {
    throw std::out_of_range("No more elements available");
  }

  Branch value = chunk[chunkIndex++];

  if (chunkIndex >= chunk.size()) {
    loadNextChunk();
  }

  return value;
}

void ChunkedIterator::loadNextChunk() {
  chunk = generator();
  chunkIndex = 0;
}

std::vector<Branch> get_chunk_sqrt2() {
  return {Branch::R, Branch::R, Branch::L, Branch::L};
}

std::vector<Branch> get_chunk_phi() { return {Branch::R, Branch::L}; }

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

void test_qToSB() {
  std::vector<Branch> u;
  qToSB(4, 3, u);
  std::vector<Branch> expected = {Branch::R, Branch::L, Branch::L};
  assert(u == expected);
}
