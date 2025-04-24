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
    mem[i] = mul(*mem[i - 1], *a);
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
    : as({a->clone()}), bs({b->clone()}), mems({parse_SSB("")}),
      i(std::nullopt) {

  Number *one = parse_SSB("");

  if (*a == *b) {
    s = 1;
    i = new NullIterator();
    return;
  }

  if (*b == *one) {
    s = 0;
    i = new NullIterator();
    return;
  }

  Number *a_inv = inv(*a);
  Number *b_inv = inv(*b);

  if (*a < *one) {
    if (*b < *one) {
      s = 1;
      if (*a_inv < *b_inv) {
        as = {inv(*a)->clone()};
        bs = {inv(*b)->clone()};
        dir = Branch::R;
      } else {
        as = {inv(*b)->clone()};
        bs = {inv(*a)->clone()};
        dir = Branch::L;
      }
    }
    if (*b > *one) {
      s = -1;
      if (*a_inv < *b) {
        as = {a_inv->clone()};
        dir = Branch::R;
      } else {
        as = {b->clone()};
        bs = {a_inv->clone()};
        dir = Branch::L;
      }
    }
  }
  if (*a > *one) {
    if (*b < *one) {
      s = -1;
      if (*a < *b_inv) {
        bs = {b_inv->clone()};
        dir = Branch::R;
      } else {
        as = {b_inv->clone()};
        bs = {a->clone()};
        dir = Branch::L;
      }
    }
    if (*b > *one) {
      s = 1;
      if (*a < *b) {
        dir = Branch::R;
      } else {
        as = {b->clone()};
        bs = {a->clone()};
        dir = Branch::L;
      }
    }
  }

  delete a_inv;
  delete b_inv;
}

std::optional<Branch> LogIterator::next() {
  if (i)
    return (*i)->next();

iter:
  Number *next_mem = mul(*mems.back(), *as.back());

  // std::cout << mems.size() << "\n";
  // std::cout << "a:   " << as.back() << "\n";
  // std::cout << "b:   " << bs.back() << "\n";
  // std::cout << "mems: " << mems.back() << "\n";

  if (*next_mem < *bs.back()) {
    // std::cout << "<" << "\n";
    mems.push_back(mul(*mems.back(), *as.back()));
    delete next_mem;
    return dir;
  }

  if (*next_mem > *bs.back()) {
    // std::cout << ">" << "\n";
    // as.emplace_back(div(bs.back(), pow(as.back(), i)));
    as.push_back(div(*bs.back(), *mems.back()));
    bs.push_back(as[as.size() - 2]);
    mems.push_back(mems[0]);
    dir = flip(dir);
    delete next_mem;
    goto iter;
  }

  return std::nullopt;
}

Iterator *LogIterator::clone() { return new LogIterator(as[0], bs[0]); }

Number *log(Number *a, Number *b) {
  LogIterator *li = new LogIterator(a, b);

  return new Number(li->s, li);
}
