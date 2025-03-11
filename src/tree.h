#ifndef TREE_H
#define TREE_H

#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

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

enum class Branch { R, L };

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

struct Number {
  int sign;
  // std::weak_ptr ?
  std::unique_ptr<Iterator> seq;

  double to_double();
  int to_fraction;

  bool operator==(const Number &other) const;
  bool operator!=(const Number &other) const;
  bool operator<(const Number &other) const;
  bool operator<=(const Number &other) const;
  bool operator>(const Number &other) const;
  bool operator>=(const Number &other) const;
};

std::ostream &operator<<(std::ostream &os, Hom H);
std::ostream &operator<<(std::ostream &os, Branch branch);
std::ostream &operator<<(std::ostream &os, std::vector<Branch> path);
std::ostream &operator<<(std::ostream &os, std::unique_ptr<Iterator> &u);
std::ostream &operator<<(std::ostream &os, Iterator &u);
std::ostream &operator<<(std::ostream &os, Number &&n);

int8_t sign(int64_t x);
int sign(int x);

Number parse_SSB(const std::string &str);
Number fraction_to_SSB(int64_t n, int64_t d);

std::unique_ptr<Iterator> make_e();
std::unique_ptr<Iterator> make_sqrt2();
std::unique_ptr<Iterator> make_phi();

std::vector<Branch> take(uint64_t n, std::unique_ptr<Iterator> &u);
Number take(uint64_t n, Number &x);
std::optional<Branch> take_one(Number &x);

#endif
