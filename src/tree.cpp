#include <cassert>
// #include <iostream>
#include "tree.h"
#include <stdexcept>
#include <variant>
#include <vector>

template <class... Fs> struct Overload : Fs... {
  using Fs::operator()...;
};
template <class... Fs> Overload(Fs...) -> Overload<Fs...>;

int sign(int64_t a) {
  if (a == 0)
    return 0;
  return (a > 0) ? 1 : -1;
}

std::optional<Branch> Iterator::next() {
  throw std::runtime_error(
      "Iterator::next() should be overridden by derived class");
}

std::ostream &operator<<(std::ostream &os, Branch branch) {
  switch (branch) {
  case Branch::R:
    return os << "R";
  case Branch::L:
    return os << "L";
  }
}

std::ostream &operator<<(std::ostream &os, std::vector<Branch> path) {
  for (const auto &branch : path) {
    os << branch;
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, Number &num) {
  std::optional<Branch> next_branch;
  char sign_sym = (num.sign == 1) ? '+' : (num.sign == -1) ? '-' : '0';
  if (num.vec) {
    os << sign_sym << *num.vec;
  } else {
    auto k = *num.seq;
    auto r = take(20, k);
    os << sign_sym << r;
    std::visit(Overload{[&os](ChunkedIterator &k) {
                          std::optional<Branch> next_branch = k.next();
                          if (next_branch) {
                            os << "…";
                          }
                        },
                        [&os](SingleChunkIterator &k) {
                          std::optional<Branch> next_branch = k.next();
                          if (next_branch) {
                            os << "…";
                          }
                        }},
               k);
  }
  return os;
}

void Hom::left() {
	a = a + b;
	c = c + d;
}

void Hom::right() {
	b = b + a;
	d = d + c;
}

double Hom::to_fraction() const {
  return static_cast<double>(a + b) / static_cast<double>(c + d);
}

int64_t Hom::to_N() const { return (a + b) * (c + d); }

int64_t Hom::det() const { return a * d - b * c; }

bool Hom::operator==(const Hom &other) const {
  return a == other.a && b == other.b && c == other.c && d == other.d;
}

const Hom I = {1, 0, 0, 1}; // Root node of the tree

Hom parseSB(const std::string &str) {
  Hom node = I;

  for (char ch : str) {
    if (ch == 'L') {
      node.left();
    } else if (ch == 'R') {
       node.right();
    } else {
      throw std::invalid_argument("Invalid character");
    }
  }

  return node;
}

SingleChunkIterator::SingleChunkIterator(const std::vector<Branch> &chunk)
    : chunk(chunk), index(0) {}

std::optional<Branch> SingleChunkIterator::next() {
  if (index >= chunk.size()) {
    return std::nullopt;
  }
  return chunk[index++];
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

void ChunkedIterator::load_next_chunk() {
  chunk = generator();
  chunk_index = 0;
}

std::vector<Branch> get_chunk_sqrt2() {
  return {Branch::R, Branch::R, Branch::L, Branch::L};
}

std::vector<Branch> get_chunk_phi() { return {Branch::R, Branch::L}; }

inline void absorb(std::vector<Branch> &r, uint &i, uint64_t &n,
                   std::optional<Branch> next_branch) {
  if (next_branch) {
    Branch b = *next_branch;
    r.push_back(b);
    i = i + 1;
  } else {
    i = n;
  }
}

std::vector<Branch>
take(uint64_t n, std::variant<SingleChunkIterator, ChunkedIterator> &u) {
  std::vector<Branch> r;

  uint i = 0;

  while (i < n) {
    std::visit(Overload{[&r, &i, &n](ChunkedIterator &k) {
                          std::optional<Branch> next_branch = k.next();
                          absorb(r, i, n, next_branch);
                        },
                        [&r, &i, &n](SingleChunkIterator &k) {
                          std::optional<Branch> next_branch = k.next();
                          absorb(r, i, n, next_branch);
                        }},
               u);
  }
  return r;
}

std::optional<Branch>
take_one(std::variant<SingleChunkIterator, ChunkedIterator> &u) {
	std::optional<Branch> next_branch = 
	std::visit(Overload{[](ChunkedIterator &k) {
                        std::optional<Branch> next_branch = k.next();
												return next_branch;
                      },
                      [](SingleChunkIterator &k) {
                        std::optional<Branch> next_branch = k.next();
												return next_branch;
                      }},
             u);
  if (next_branch) {
    return *next_branch;
  } else {
    return std::nullopt;
  }
}

auto make_e_generator() {
  return [n = 0]() mutable -> std::vector<Branch> {
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
    return result;
  };
}

ChunkedIterator make_e() {
  auto e_gen = make_e_generator();
  ChunkedIterator e(e_gen);
  return e;
}

auto make_rational_generator(std::vector<Branch> rat) {
  return [n = 0]() mutable -> std::vector<Branch> {
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
    return result;
  };
}

double SB_to_double(std::vector<Branch> &u) {
  Hom node = I;

  for (Branch b : u) {
    if (b == Branch::R) {
      node.right();
    } else {
      node.left();
    }
  }
  return node.to_fraction();
}

void Q_to_SB(int64_t n, int64_t d, std::vector<Branch> &u) {
  while (n != d) {
    if (n < d) {
      u.push_back(Branch::L);
      d -= n;
    } else {
      u.push_back(Branch::R);
      n -= d;
    }
  }
}

void Q_to_SB(int64_t n, int64_t d) {};

// Number::Number(int sign, std::optional<std::vector<Branch>> vec,
//                std::optional<Iterator> seq)
//     : sign(sign), vec(vec), seq(seq) {}

Number Q_to_SSB(int n, int d) {
  int s = sign(n) * sign(d);
  // Number res = {s};

  // return res;
}

// Number Q_to_SSB(int64_t n, int64_t d) {
//   int sign = sign(n) * sign(d);
//   Number result(sign);
//   return result;
// }

// Test functions
void test_parse_SB() {
  Hom parsed = parseSB("RRRLRLLL");
  Hom expected = {25, 7, 7, 2};
  assert(parsed == expected);
}

void test_Q_to_SB() {
  std::vector<Branch> u;
  Q_to_SB(4, 3, u);
  std::vector<Branch> expected = {Branch::R, Branch::L, Branch::L};
  assert(u == expected);
}
