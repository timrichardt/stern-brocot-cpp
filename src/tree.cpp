#include <cassert>
// #include <iostream>
#include "tree.h"
#include <stdexcept>
#include <vector>

Branch Iterator::next() {
  throw std::runtime_error(
      "Iterator::next() should be overridden by derived class");
}

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

double Node::to_fraction() const {
  return static_cast<double>(a + b) / static_cast<double>(c + d);
}

int64_t Node::to_N() const { return (a + b) * (c + d); }

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

std::vector<Branch> take(uint64_t n, ChunkedIterator &u) {
  std::vector<Branch> r;

  for (uint i = 0; i < n; i++) {
    r.push_back(u.next());
  }

  return r;
}

auto make_e_generator() {
  return [n = 0]() mutable -> std::vector<Branch> {
    std::vector<Branch> result;

    if (n % 2 == 0) {
      result.push_back(Branch::R);
      result.insert(result.end(), 2 * n, Branch::L);
      result.push_back(Branch::R);
    } else {
      result.push_back(Branch::L);
      result.insert(result.end(), 2 * n, Branch::R);
      result.push_back(Branch::L);
    }
    n++;
    return result;
  };
}

ChunkedIterator make_e() {
  auto e_gen = make_e_generator();
  ChunkedIterator e(e_gen);
  return e;
}

double SB_to_double(std::vector<Branch> &u) {
  Node node = I;

  for (Branch b : u) {
    if (b == Branch::R) {
      node = node.right();
    } else {
      node = node.left();
    }
  }
  return node.to_fraction();
}

void Q_to_SB(int64_t n, int64_t d, std::vector<Branch> &u) {
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
void test_parse_SB() {
  Node parsed = parseSB("RRRLRLLL");
  Node expected = {25, 7, 7, 2};
  assert(parsed == expected);
}

void test_Q_to_SB() {
  std::vector<Branch> u;
  Q_to_SB(4, 3, u);
  std::vector<Branch> expected = {Branch::R, Branch::L, Branch::L};
  assert(u == expected);
}
