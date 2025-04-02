#include "shanks.h"
#include "arithmetic.h"
#include "tree.h"
#include <iostream>

inline Branch flip(Branch b) {
  if (b == Branch::R) {
    return Branch::L;
  } else {
    return Branch::R;
  }
}

PowIterator::PowIterator(Number *a, uint64_t n) : a(a->clone()), n(n) {
  mem = new Number *[n];

  mem[0] = new Number(1, new NullIterator());

  for (uint i = 1; i < n + 1; ++i) {
    mem[i] = mul(mem[i - 1], a);
  }
}

PowIterator::~PowIterator() {
  for (uint64_t i = 0; i < n + 1; ++i) {
    delete mem[i];
  }

  delete[] mem;
}

std::optional<Branch> PowIterator::next() { return mem[n]->seq->next(); }

Iterator *PowIterator::clone() { return new PowIterator(a, n); }

Number *pow(Number *a, uint64_t n) {
  if (n == 0)
    return new Number(1, new NullIterator());

  if (n == 1)
    return a->clone();

  if (n % 2 == 0)
    return new Number(1, new PowIterator(a, n));

  return new Number(a->sign, new PowIterator(a, n));
}

LogIterator::LogIterator(Number *a, Number *b)
    : as({a->clone()}), bs({b->clone()}), tmp({parse_SSB("")}) {
  dir = Branch::R;
}

std::optional<Branch> LogIterator::next() {
iter:
  Number *ttmp = mul(tmp.back(), as.back());

  // std::cout << tmp.size() << "\n";
  // std::cout << "a:   " << as.back() << "\n";
  // std::cout << "b:   " << bs.back() << "\n";
  // std::cout << "tmp: " << tmp.back() << "\n";

  if (*ttmp < *bs.back()) {
    // std::cout << "<" << "\n";
    tmp.push_back(mul(tmp.back(), as.back()));
    return dir;
  }

  if (*ttmp > *bs.back()) {
    // std::cout << ">" << "\n";
    // as.emplace_back(div(bs.back(), pow(as.back(), i)));
    as.push_back(div(bs.back(), tmp.back()));
    bs.push_back(as[as.size() - 2]);
    tmp.push_back(tmp[0]);
    dir = flip(dir);
    goto iter;
  }

  return std::nullopt;
}

Iterator *LogIterator::clone() { return new LogIterator(as[0], bs[0]); }

Number *log(Number *a, Number *b) {}
