#ifndef SHANKS_H
#define SHANKS_H

#include "tree.h"

class PowIterator : public Iterator {
public:
  explicit PowIterator(Number *, uint64_t);
  std::optional<Branch> next() override;
  Iterator *clone() override;
  ~PowIterator();

private:
  Number *a;
  uint64_t n;
  Number **mem;
};

Number *pow(Number *, uint64_t);

class LogIterator : public Iterator {
public:
  explicit LogIterator(Number *, Number *);
  std::optional<Branch> next() override;
  Iterator *clone() override;
  int s;

private:
  Branch dir;
  std::vector<Number *> as;
  std::vector<Number *> bs;
  std::vector<Number *> mems;
};

Number *log(Number *a, Number *b);

#endif
