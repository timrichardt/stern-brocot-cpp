#ifndef TREE_H
#define TREE_H

#include <cstdint>
#include <functional>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

int sign(int64_t a);

// Struct representing a node in the tree
struct Hom {
  int64_t a, b, c, d;

  Hom left() const;
  Hom right() const;
  double to_fraction() const;
  int64_t to_N() const;
  int64_t det() const;
  bool operator==(const Hom &other) const;
};

extern const Hom I; // Root node of the tree

Hom parse_SB(const std::string &str);

enum class Branch { R, L };

std::ostream &operator<<(std::ostream &os, Branch branch);
std::ostream &operator<<(std::ostream &os, std::vector<Branch> path);

class Iterator {
public:
  virtual ~Iterator() = default;
  Iterator() = default;
  virtual std::optional<Branch> next();
};

class SingleChunkIterator : public Iterator {
public:
  explicit SingleChunkIterator(const std::vector<Branch> &chunk);
  std::optional<Branch> next() override;

private:
  std::vector<Branch> chunk;
  size_t index;
};

class ChunkedIterator : public Iterator {
public:
  using ChunkGenerator = std::function<std::vector<Branch>()>;

  explicit ChunkedIterator(ChunkGenerator generator);
  std::optional<Branch> next() override;

private:
  ChunkGenerator generator;
  std::vector<Branch> chunk;
  size_t chunk_index;
  void load_next_chunk();
};

std::vector<Branch> get_chunk_sqrt2();
std::vector<Branch> get_chunk_phi();
std::vector<Branch> get_chunk_e();

ChunkedIterator make_e();

double SB_to_double(std::vector<Branch> &u);

struct Number {
  int sign;
  std::optional<std::vector<Branch>> vec;
  std::optional<std::variant<SingleChunkIterator, ChunkedIterator>> seq;
};

std::ostream &operator<<(std::ostream &os, Number &num);

// std::vector<Branch> take(uint64_t n, Iterator &u);
std::vector<Branch> take(uint64_t n, Number &u);
std::vector<Branch> take(uint64_t n,
                         std::variant<SingleChunkIterator, ChunkedIterator> &u);
std::optional<Branch>
take_one(std::variant<SingleChunkIterator, ChunkedIterator> &u);

void Q_to_SB(int64_t n, int64_t d, std::vector<Branch> &u);
void Q_to_SB(int64_t n, int64_t d);
void Q_to_SB(int64_t n, int64_t d);

Number Q_to_SSB(int64_t n, int64_t d);

// Test functions
void test_parse_SB();
void test_q_to_SB();

#endif
