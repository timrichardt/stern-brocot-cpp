#ifndef SHANKS_H
#define SHANKS_H

#include "tree.h"

class LogIterator : public Iterator {
public:
  explicit LogIterator(Number *a, Number *b);
  std::optional<Branch> next() override;
  Iterator *clone() override;
  int s;

private:
  Branch dir;
  std::vector<Number *> mem;
  Number *a;
  Number *b;
  uint n;
};

Number *log(Number *a, Number *b);

#endif
