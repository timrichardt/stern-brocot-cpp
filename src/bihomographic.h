#ifndef BIHOMOGRAPHIC_H
#define BIHOMOGRAPHIC_H

#include "tree.h"
#include <functional>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

// Struct representing a node in the tree
struct Bihom {
  int64_t a, b, c, d, e, f, g, h;

  void ll();
  void lr();
  void rl();
  void rr();
  void ar();
  void al();
  void br();
  void bl();
  void up();
  void down();
  double to_fraction() const;
  int64_t to_N() const;
  int64_t det() const;
  bool operator==(const Bihom &other) const;
};

class BihomIterator : public Iterator {
public:
  explicit BihomIterator(Bihom B, const Number &a, const Number &b);
  std::optional<Branch> next() override;
  std::unique_ptr<Iterator> clone() override;
  int s;

private:
  Bihom C;
  Hom H;
  Number m;
  Number n;
};

int bihom_sign(Bihom B, std::unique_ptr<Iterator> &a,
               std::unique_ptr<Iterator> &b);

Number bihom(Bihom H, Number &x, Number &y);

#endif
