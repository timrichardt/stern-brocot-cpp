#ifndef HOMOGRAPHIC_H
#define HOMOGRAPHIC_H

#include "tree.h"
#include <functional>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

class HomIterator : public Iterator {
public:
  ~HomIterator();
  explicit HomIterator(Hom H, Number *n, bool clone = true);
  std::optional<Branch> next() override;
  Iterator *clone() override;
  int s;

private:
  Hom G_init;
  Hom G;
  Number *m;
  std::optional<Iterator *> i;
};

std::optional<int64_t> lin_sign(int64_t a, int64_t b);
int hom_sign(Hom &H, Iterator *u);

Number *hom(Hom, Number *);

#endif
