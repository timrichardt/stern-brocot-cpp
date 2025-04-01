#include "shanks.h"
#include "arithmetic.h"
#include "tree.h"
#include <iostream>

LogIterator::LogIterator(Number *a, Number *b)
    : mem({parse_SSB("")}), a(a->clone()), b(b->clone()), n(0) {
  dir = Branch::R;
}

Branch flip(Branch b) {
  if (b == Branch::R) {
    return Branch::L;
  } else {
    return Branch::R;
  }
}

std::optional<Branch> LogIterator::next() {
iter:
  mem.emplace_back(mul(mem.back(), a));

  if (mem.back() < b) {
    return dir;
  }

  if (mem.back() > b) {
    Number *a_c = a;
    a = div(b, mem.back());
    b = a_c;
    mem.emplace_back(parse_SSB(""));
    goto iter;
  }

  return std::nullopt;
}

Iterator *LogIterator::clone() { return new LogIterator(a, b); }

Number *log(Number *a, Number *b) {}
