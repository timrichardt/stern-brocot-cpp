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

  bool operator==(const Number &other) const;
  bool operator!=(const Number &other) const;
  bool operator<(const Number &other) const;
  bool operator<=(const Number &other) const;
  bool operator>(const Number &other) const;
  bool operator>=(const Number &other) const;
};

class HomIterator : public Iterator {
public:
  explicit HomIterator(Hom H, const Number &n);
  std::optional<Branch> next() override;
  std::unique_ptr<Iterator> clone() override;

private:
  Hom G;
  Number m;
};

extern const Hom I;
std::ostream &operator<<(std::ostream &os, Hom H);
std::ostream &operator<<(std::ostream &os, Branch branch);
std::ostream &operator<<(std::ostream &os, std::vector<Branch> path);
std::ostream &operator<<(std::ostream &os, std::unique_ptr<Iterator> &u);
std::ostream &operator<<(std::ostream &os, Iterator &u);
std::ostream &operator<<(std::ostream &os, Number &&n);

int8_t sign(Number &x);
Number parse_SSB(const std::string &str);
Number Q_to_SSB(int64_t n, int64_t d);

Number take(uint64_t n, Number &x);
std::optional<Branch> take_one(Number &x);

std::unique_ptr<Iterator> make_e();
std::unique_ptr<Iterator> make_sqrt2();
std::unique_ptr<Iterator> make_phi();

#endif
