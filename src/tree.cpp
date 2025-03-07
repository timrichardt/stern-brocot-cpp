#include "tree.h"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>

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

// std::ostream &operator<<(std::ostream &os, Number &num) {
//   char sign_sym = (num.sign == 1) ? '+' : (num.sign == -1) ? '-' : '0';
//   if (num.vec) {
//     os << sign_sym << *num.vec;
//   } else {
//     auto k = *num.seq;
//     auto r = take(50, k);
//     os << sign_sym << r;
//     std::visit(Overload{[&os](ChunkedIterator &k) {
//                           std::optional<Branch> next_branch = k.next();
//                           if (next_branch) {
//                             os << "…";
//                           }
//                         },
//                         [&os](SingleChunkIterator &k) {
//                           std::optional<Branch> next_branch = k.next();
//                           if (next_branch) {
//                             os << "…";
//                           }
//                         }},
//                k);
//   }
//   return os;
// }

std::ostream &operator<<(std::ostream &os, Hom H) {
  os << H.a << " " << H.b << " " << H.c << " " << H.d << std::endl;
  return os;
}

int8_t sign(int64_t a) {
  if (a == 0)
    return 0;
  return (a > 0) ? 1 : -1;
}

void Hom::left() {
  a = a + b;
  c = c + d;
}

void Hom::right() {
  b = b + a;
  d = d + c;
}

void Hom::up() {
  a = a - c;
  b = b - d;
}

void Hom::down() {
  c = c - a;
  d = d - b;
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

SingleChunkIterator::SingleChunkIterator(const std::vector<Branch> &chunk)
    : chunk(chunk), index(0) {}

std::optional<Branch> SingleChunkIterator::next() {
  if (index >= chunk.size()) {
    return std::nullopt;
  }
  return chunk[index++];
}

bool Number::operator==(const Number &other) const {
  std::cout << "HERE I AM";

  if (sign != other.sign)
    return false;

  std::optional<Branch> a, b;

  while (true) {
    a = seq.next();
    b = other.seq.next();

    std::cout << "a: " << *a << std::endl;
    std::cout << "b: " << *b << std::endl;

    if (a) {
      if (b) {
        if (*a != *b)
          return false;
      } else {
        return false;
      }
    } else {
      if (b) {
        return false;
      } else {
        return true;
      }
    }
  }
}

Number parse_SB(const std::string &str) {
  std::vector<Branch> u;
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
      s = 0;
      break;
    case '0':
      s = 0;
      break;
    default:
      throw std::invalid_argument(
          "Failed parsing sequence. Invalid character.");
    }
  }

  SingleChunkIterator ci(u);
  Number ret = {s, ci};

  return ret;
}

void test_parse_SB() {
  Number parsed_1 = parse_SB("RLR");
  SingleChunkIterator u({Branch::R, Branch::L, Branch::R});
  std::cout << *u.next() << *u.next() << *u.next();
  Number expected_1 = {1, u};
  assert(parsed_1 == expected_1);
  std::cout << "Test passed: parse SB sequence" << std::endl;
}
