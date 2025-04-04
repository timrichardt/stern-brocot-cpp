#ifndef TREE_H
#define TREE_H

#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

// Struct representing a node in the tree
struct Hom {
  int64_t a, b, c, d;

  inline bool R_emittable();
  inline bool L_emittable();

  void left();
  void right();
  void up();
  void down();

  double to_fraction() const;
  int64_t to_N() const;
  int64_t det() const;
  bool operator==(const Hom &other) const;
};

extern const Hom I;

enum class Branch { R, L };

class Iterator {
public:
  virtual ~Iterator() = default;
  Iterator() = default;
  virtual std::optional<Branch> next();
  virtual Iterator *clone();
};

class SingleChunkIterator : public Iterator {
public:
  explicit SingleChunkIterator(const std::vector<Branch> &chunk);
  std::optional<Branch> next() override;
  Iterator *clone() override;

private:
  std::vector<Branch> chunk;
  size_t index;
};

class ChunkedIterator : public Iterator {
public:
  using ChunkGenerator = std::function<std::vector<Branch>()>;
  explicit ChunkedIterator(ChunkGenerator generator);
  std::optional<Branch> next() override;
  Iterator *clone() override;

private:
  ChunkGenerator generator;
  std::vector<Branch> chunk;
  size_t chunk_index;
  void load_next_chunk();
};

class EulerIterator : public Iterator {
public:
  explicit EulerIterator();
  std::optional<Branch> next() override;
  Iterator *clone() override;

private:
  uint n;
  std::vector<Branch> chunk;
  size_t chunk_index;
  void load_next_chunk();
};

class NullIterator : public Iterator {
public:
  explicit NullIterator();
  std::optional<Branch> next() override;
  Iterator *clone() override;
};

class Number {
public:
  int sign;
  // std::weak_ptr ?
  Iterator *seq;
  explicit Number(int sign, Iterator *seq);
  Number(Number &a);

  double to_double();
  std::pair<int64_t, int64_t> to_fraction();
  Number *clone();

  Number *operator+(Number *&other);
  Number *operator-(Number *other);
  Number *operator*(Number *other);
  Number *operator/(Number *other);
};

bool operator==(const Number &lhs, const Number &rhs);
bool operator!=(const Number &lhs, const Number &rhs);
bool operator<(const Number &lhs, const Number &rhs);
bool operator<=(const Number &lhs, const Number &rhs);
bool operator>(const Number &lhs, const Number &rhs);
bool operator>=(const Number &lhs, const Number &rhs);

std::ostream &operator<<(std::ostream &os, Hom H);
std::ostream &operator<<(std::ostream &os, Branch branch);
std::ostream &operator<<(std::ostream &os, std::vector<Branch> path);
std::ostream &operator<<(std::ostream &os, Iterator *u);
std::ostream &operator<<(std::ostream &os, Number *n);

int8_t sign(int64_t x);
int sign(int x);

Number *parse_SSB(const std::string &str);
Number *fraction_to_SSB(int64_t n, int64_t d);
Number *SSB_to_CF(const Number *a);

Iterator *make_e();
Iterator *make_sqrt2();
Iterator *make_phi();

Iterator *take(uint64_t n, Iterator *u);
Number *take(uint64_t n, Number *x);
std::optional<Branch> take_one(Number &x);

#endif
