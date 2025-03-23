#ifndef BIHOMOGRAPHIC_H
#define BIHOMOGRAPHIC_H

#include "homographic.h"
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
  inline bool same_ratio();
  inline bool R_emittable();
  inline bool L_emittable();
  std::optional<Branch> emit(Iterator* &m,
                             Iterator* &n);
  double to_double() const;
  int64_t to_N() const;
  bool operator==(const Bihom &other) const;
};

class BihomIterator : public Iterator {
public:
  explicit BihomIterator(Bihom B, Number* &a, Number* &b);
  std::optional<Branch> next() override;
  Iterator* clone() override;
  int s;

private:
  Bihom C;
	Number* &m;
	Number* &n;
  std::optional<Iterator*> &hi;
};

int bihom_sign(Bihom &B, Iterator* &a, Iterator* &b);

std::ostream &operator<<(std::ostream &os, Bihom B);

// Number bihom(Bihom B, Number &a, Number &b); 
Number* bihom(Bihom B, Number* &a, Number* &b);

#endif
