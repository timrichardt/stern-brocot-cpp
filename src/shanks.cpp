#include "shanks.h"
#include "arithmetic.h"
#include "tree.h"
#include <iostream>

LogIterator::LogIterator(Number *a, Number *b)
    : mem({parse_SSB("")}), as({a->clone()}), bs({b->clone()}), n(0) {
  dir = Branch::R;
}

Branch flip(Branch b) {
  if (b == Branch::R) {
    return Branch::L;
  } else {
    return Branch::R;
  }
}

PowIterator::PowIterator(Number *a, uint64_t n) : a(a->clone()), n(n) {
  mem = new Number *[n];

  mem[0] = a;

  for (uint i = 1; i < n; ++i) {
    mem[i] = mul(mem[i - 1], a);
  }
}

std::optional<Branch> PowIterator::next() { return mem[n - 1]->seq->next(); }

Iterator *PowIterator::clone() { return new PowIterator(a, n); }

std::optional<Branch> LogIterator::next() {
iter:
  std::cout << "mem: " << mem.back() << std::endl;
  std::cout << "a:   " << as.back() << std::endl;
  std::cout << "b:   " << bs.back() << std::endl;

  Number *tmp = mul(mem.back(), as.back());
  std::cout << "tmp: " << tmp << std::endl;

  if (tmp < bs.back()) {
    std::cout << "<" << std::endl;
    mem.emplace_back(mul(mem.back(), as.back()));
    return dir;
  }

  if (mem.back() > bs.back()) {
    std::cout << ">" << std::endl;
    as.emplace_back(div(bs.back(), mem.back()));
    bs.emplace_back(as[as.size() - 2]);
    mem.emplace_back(parse_SSB(""));
    goto iter;
  }

  return std::nullopt;
}

Iterator *LogIterator::clone() { return new LogIterator(as[0], bs[0]); }

Number *log(Number *a, Number *b) {}
