#include "tree.h"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

void Hom::left() {
  a += b;
  c += d;
}

void Hom::right() {
  b += a;
  d += c;
}

void Hom::up() {
  a -= c;
  b -= d;
}

void Hom::down() {
  c -= a;
  d -= b;
}

double Hom::to_fraction() const {
  return static_cast<double>(a + b) / static_cast<double>(c + d);
}

int64_t Hom::to_N() const { return (a + b) * (c + d); }

int64_t Hom::det() const { return a * d - b * c; }

bool Hom::operator==(const Hom &other) const {
  return a == other.a && b == other.b && c == other.c && d == other.d;
}

const Hom I = {1, 0, 0, 1};

std::optional<Branch> Iterator::next() {
  throw std::runtime_error(
      "Iterator::next() should be overridden by derived class");
}

Iterator *Iterator::clone() {
  throw std::runtime_error(
      "Iterator::clone() should be overridden by derived class");
}

SingleChunkIterator::SingleChunkIterator(const std::vector<Branch> &chunk)
    : chunk(chunk), index(0) {}

std::optional<Branch> SingleChunkIterator::next() {
  if (index >= chunk.size()) {
    return std::nullopt;
  }
  return chunk[index++];
}

Iterator *SingleChunkIterator::clone() {
  return new SingleChunkIterator(chunk);
}

ChunkedIterator::ChunkedIterator(ChunkGenerator generator)
    : generator(generator), chunk_index(0) {
  load_next_chunk();
}

std::optional<Branch> ChunkedIterator::next() {
  if (chunk.empty()) {
    return std::nullopt;
  }

  Branch value = chunk[chunk_index++];

  if (chunk_index >= chunk.size()) {
    load_next_chunk();
  }

  return value;
}

Iterator *ChunkedIterator::clone() { return new ChunkedIterator(generator); }

void ChunkedIterator::load_next_chunk() {
  chunk = generator();
  chunk_index = 0;
}

EulerIterator::EulerIterator() : n(0), chunk_index(0) { load_next_chunk(); }

std::optional<Branch> EulerIterator::next() {
  Branch value = chunk[chunk_index++];

  if (chunk_index >= chunk.size()) {
    load_next_chunk();
  }

  return value;
}

Iterator *EulerIterator::clone() { return new EulerIterator(); }

void EulerIterator::load_next_chunk() {
  std::vector<Branch> result;

  if (n % 2 == 0) {
    result.push_back(Branch::R);
    result.insert(result.end(), 2 * n, Branch::L);
    result.push_back(Branch::R);
  } else {
    result.push_back(Branch::L);
    result.insert(result.end(), 2 * n, Branch::R);
    result.push_back(Branch::L);
  }

  n++;
  chunk = result;
  chunk_index = 0;
}

NullIterator::NullIterator() {}

std::optional<Branch> NullIterator::next() { return std::nullopt; }

Iterator *NullIterator::clone() { return new NullIterator(); }

bool Number::operator==(const Number *&other) const {
  if (sign != other->sign)
    return false;

  Iterator *seq_c = seq->clone();
  Iterator *other_seq_c = other->seq->clone();

  std::optional<Branch> a, b;

get_branches:
  a = seq_c->next();
  b = other_seq_c->next();

  if (a && b) {
    if (*a != *b) {
      return false;
    }
    goto get_branches;
  }

  if (a || b)
    return false;

  return true;
}

bool Number::operator==(const Number &other) const {
  if (sign != other.sign)
    return false;

  Iterator *seq_c = seq->clone();
  Iterator *other_seq_c = other.seq->clone();

  std::optional<Branch> a, b;

get_branches:
  a = seq_c->next();
  b = other_seq_c->next();

  if (a && b) {
    if (*a != *b) {
      return false;
    }
    goto get_branches;
  }

  if (a || b)
    return false;

  return true;
}

double Number::to_double() {
  Iterator *u = seq->clone();
  Hom H = I;

absorb:
  std::optional<Branch> b = u->next();
  if (b) {
    if (b == Branch::R)
      H.right();
    if (b == Branch::L)
      H.left();
    goto absorb;
  }
  return sign * static_cast<double>(H.a + H.b) / static_cast<double>(H.c + H.d);
}

std::pair<int64_t, int64_t> Number::to_fraction() {
  Iterator *u = seq->clone();
  Hom H = I;

absorb:
  std::optional<Branch> b = u->next();
  if (b) {
    if (b == Branch::R)
      H.right();
    if (b == Branch::L)
      H.left();
    goto absorb;
  }
  return {H.a + H.b, H.c + H.d};
}

Number *Number::clone() { return new Number(Number{sign, seq->clone()}); }

bool Number::operator!=(const Number &other) const {
  if (sign != other.sign)
    return true;

  Iterator *seq_c = seq->clone();
  Iterator *other_seq_c = other.seq->clone();

  std::optional<Branch> a, b;

get_branches:
  a = seq_c->next();
  b = other_seq_c->next();

  if (a && b) {
    if (*a != *b) {
      return true;
    } else {
      goto get_branches;
    }
  }

  if (a || b)
    return true;

  return false;
}

bool Number::operator<(const Number &other) const {
  if (sign > other.sign)
    return false;

  Iterator *seq_c = seq->clone();
  Iterator *other_seq_c = other.seq->clone();

  if (sign == other.sign) {
    std::optional<Branch> a, b;

  get_branches:
    a = seq_c->next();
    b = other_seq_c->next();

    if (a && b) {
      if ((*a == Branch::R) && (*b == Branch::L))
        return false;
      if ((*a == Branch::L) && (*b == Branch::R))
        return true;
      goto get_branches;
    }

    if (!b)
      if (*a == Branch::L)
        return true;

    if (!a)
      if (*b == Branch::R)
        return true;
  }

  return false;
}

bool Number::operator<=(const Number &other) const {
  if (sign != other.sign)
    return true;

  Iterator *seq_c = seq->clone();
  Iterator *other_seq_c = other.seq->clone();

  std::optional<Branch> a, b;

  a = seq->next();
  b = other.seq->next();

  do {
    if ((*a == Branch::L) && (*b == Branch::R))
      return false;
    a = seq_c->next();
    b = other_seq_c->next();
  } while (a && b);

  if (a)
    return (*a == Branch::L);
  if (b)
    return (*b == Branch::R);

  return false;
}

bool Number::operator>(const Number &other) const {
  if (sign > other.sign)
    return true;

  if (sign == other.sign) {
    Iterator *seq_c = seq->clone();
    Iterator *other_seq_c = other.seq->clone();

    std::optional<Branch> a, b;

  get_branches:
    a = seq_c->next();
    b = other_seq_c->next();

    if (a && b) {
      if ((a == Branch::L) && (b == Branch::R))
        return false;
      if ((a == Branch::R) && (b == Branch::L))
        return true;
      goto get_branches;
    }

    if (a)
      return (*a == Branch::R);

    if (b)
      return (*b == Branch::L);
  }

  return false;
}

bool Number::operator>=(const Number &other) const {
  if (sign < other.sign)
    return false;

  if (sign == other.sign) {
    Iterator *seq_c = seq->clone();
    Iterator *other_seq_c = other.seq->clone();

    std::optional<Branch> a, b;

  get_branches:
    a = seq_c->next();
    b = other_seq_c->next();

    if (a && b) {
      if ((a == Branch::L) && (b == Branch::R))
        return false;
      if ((a == Branch::R) && (b == Branch::L))
        return true;
      goto get_branches;
    }

    if (a)
      return (*a == Branch::R);

    if (b)
      return (*b == Branch::L);
  }

  return true;
}

std::ostream &operator<<(std::ostream &os, Branch branch) {
  switch (branch) {
  case Branch::R:
    os << "R";
    break;
  case Branch::L:
    os << "L";
    break;
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, std::vector<Branch> path) {
  for (const auto &branch : path) {
    os << branch;
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, Hom H) {
  os << H.a << " " << H.b << " " << H.c << " " << H.d << std::endl;
  return os;
}

std::ostream &operator<<(std::ostream &os, Iterator *&u) {
  std::optional<Branch> branch;

  branch = u->next();

  while (branch) {
    os << *branch;
    branch = u->next();
  }

  return os;
}

std::ostream &operator<<(std::ostream &os, Iterator &u) {
  std::optional<Branch> branch = u.next();

  while (branch) {
    os << *branch;
    branch = u.next();
  }

  return os;
}

std::ostream &operator<<(std::ostream &os, Number *&n) {
  os << ((n->sign == 1) ? '+' : (n->sign == -1) ? '-' : '0');
  os << *n->seq;

  return os;
}

Iterator *take(uint64_t n, Iterator *&u) {
  // std::unique_ptr<Iterator> v = u->clone();

  std::vector<Branch> r = {};
  uint64_t i = 0;
  std::optional<Branch> next_branch;

  while (i < n) {
    next_branch = u->next();
    if (next_branch) {
      r.push_back(*next_branch);
      i++;
    } else {
      break;
    }
  }

  return new SingleChunkIterator(r);
}

Number *take(uint64_t n, Number *&x) {
  Iterator *u = take(n, x->seq);

  return new Number(x->sign, u);
}

Number take(uint64_t n, Number &x) { return Number{x.sign, take(n, x.seq)}; }

int8_t sign(int64_t a) {
  if (a == 0)
    return 0;
  return (a > 0) ? 1 : -1;
}

Number *parse_SSB(const std::string &str) {
  std::vector<Branch> u = {};
  int8_t s = 1;

  for (char ch : str) {
    switch (ch) {
    case 'R':
      u.push_back(Branch::R);
      break;
    case 'L':
      u.push_back(Branch::L);
      break;
    case '+':
      s = 1;
      break;
    case '-':
      s = -1;
      break;
    case '0':
      s = 0;
      break;
    default:
      throw std::invalid_argument(
          "Failed parsing sequence. Invalid character.");
    }
  }

  return new Number(s, new SingleChunkIterator(u));
}

Number *fraction_to_SSB(int64_t n, int64_t d) {
  std::vector<Branch> u;

  int s = sign(n) * sign(d);

  uint64_t an = sign(n) * n;
  uint64_t ad = sign(d) * d;

  while (an != ad) {
    if (an < ad) {
      u.push_back(Branch::L);
      ad -= an;
    } else {
      u.push_back(Branch::R);
      an -= ad;
    }
  }

  return new Number(s, new SingleChunkIterator(u));
}

Iterator *make_e() { return new EulerIterator(); }

std::vector<Branch> sqrt2_generator() {
  return {Branch::R, Branch::L, Branch::L, Branch::R};
}

Iterator *make_sqrt2() { return new ChunkedIterator(sqrt2_generator); }

std::vector<Branch> phi_generator() { return {Branch::R, Branch::L}; }

Iterator *make_phi() { return new ChunkedIterator(phi_generator); }

Number::Number(int sign, Iterator *seq) : sign(sign), seq(seq) {}
