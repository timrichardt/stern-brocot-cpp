#ifndef TREE_H
#define TREE_H

#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

int8_t sign(int64_t a);

// Struct representing a node in the tree
struct Hom {
  int64_t a, b, c, d;

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

std::ostream &operator<<(std::ostream &os, Hom H);

enum class Branch { R, L };

std::ostream &operator<<(std::ostream &os, Branch branch);
std::ostream &operator<<(std::ostream &os, std::vector<Branch> path);

class Iterator {
public:
  virtual ~Iterator() = default;
  Iterator() = default;
  virtual std::optional<Branch> next();
  virtual std::unique_ptr<Iterator> clone();
};

class SingleChunkIterator : public Iterator {
public:
  explicit SingleChunkIterator(const std::vector<Branch> &chunk);
  std::optional<Branch> next() override;
  std::unique_ptr<Iterator> clone() override;

private:
  std::vector<Branch> chunk;
  size_t index;
};

class ChunkedIterator : public Iterator {
public:
  using ChunkGenerator = std::function<std::vector<Branch>()>;

  explicit ChunkedIterator(ChunkGenerator generator);
  std::optional<Branch> next() override;
  std::unique_ptr<Iterator> clone() override;

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

struct Number {
  int sign;
  // std::weak_ptr ?
  std::unique_ptr<Iterator> seq;

  bool operator==(const Number &other) const;
  bool operator!=(const Number &other) const;
  bool operator<(const Number &other) const;
  bool operator<=(const Number &other) const;
  bool operator>(const Number &other) const;
  bool operator>=(const Number &other) const;
};

std::ostream &operator<<(std::ostream &os, Number &num);

class HomIterator : public Iterator {
public:
  explicit HomIterator(Hom H, const Number &n);
  std::optional<Branch> next() override;
  std::unique_ptr<Iterator> clone() override;

private:
  Hom G;
  Number m;
};

Number parse_SB(const std::string &str);

int8_t sign(Number &x);

Number take(uint64_t n, Number &x);
std::optional<Branch> take_one(Number &x);

Number Q_to_SSB(int64_t n, int64_t d);

// Test functions
void test_parse_SB();
void test_q_to_SB();

#endif
