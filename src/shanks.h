#ifndef SHANKS_H
#define SHANKS_H

#include "tree.h"

Number *pow(Number *a, uint64_t n);

class PowIterator : public Iterator {
public:
  explicit PowIterator(Number *, uint64_t);
  std::optional<Branch> next() override;
  Iterator *clone() override;

private:
  uint64_t n;
  Number *a;
  Number **mem;
};

class LogIterator : public Iterator {
public:
  explicit LogIterator(Number *a, Number *b);
  std::optional<Branch> next() override;
  Iterator *clone() override;
  int s;

private:
  Branch dir;
  uint64_t n;
  std::vector<Number *> mem;
  std::vector<Number *> as;
  std::vector<Number *> bs;
};

Number *log(Number *a, Number *b);

#endif
