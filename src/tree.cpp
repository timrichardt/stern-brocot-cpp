#include "tree.h"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <memory>
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

std::ostream &operator<<(std::ostream &os, Hom H) {
  os << H.a << " " << H.b << " " << H.c << " " << H.d << std::endl;
  return os;
}

std::ostream &operator<<(std::ostream &os, Number n) { return os; }

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

std::unique_ptr<Iterator> Iterator::clone() {
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

std::unique_ptr<Iterator> SingleChunkIterator::clone() {
  return std::make_unique<SingleChunkIterator>(chunk);
}

bool Number::operator==(const Number &other) const {
  if (sign != other.sign)
    return false;

  std::optional<Branch> a, b;

  a = seq->next();
  b = other.seq->next();

  do {
    if (*a != *b)
      return false;
    a = seq->next();
    b = other.seq->next();
  } while (a && b);

  if (a || b)
    return false;

  return true;
}

bool Number::operator!=(const Number &other) const {
  if (sign != other.sign)
    return true;

  std::optional<Branch> a, b;

  a = seq->next();
  b = other.seq->next();

  do {
    if (*a != *b)
      return true;
    a = seq->next();
    b = other.seq->next();
  } while (a && b);

  if (a || b)
    return true;

  return false;
}

bool Number::operator<(const Number &other) const {
  if (sign < other.sign)
    return true;

  if (sign == other.sign) {
    std::optional<Branch> a, b;

    a = seq->next();
    b = other.seq->next();

    do {
      if ((*a == Branch::R) && (*b == Branch::L))
        return false;
      a = seq->next();
      b = other.seq->next();
    } while (a && b);

    if (a)
      if (*a == Branch::L)
        return true;

    if (b)
      if (*b == Branch::R)
        return true;
  }

  return false;
}

bool Number::operator<=(const Number &other) const {
  if (sign != other.sign)
    return true;

  std::optional<Branch> a, b;

  a = seq->next();
  b = other.seq->next();

  do {
    if ((*a == Branch::L) && (*b == Branch::R))
      return false;
    a = seq->next();
    b = other.seq->next();
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
    std::optional<Branch> a, b;

    a = seq->next();
    b = other.seq->next();

    do {
      if (*a > *b)
        return true;
      a = seq->next();
      b = other.seq->next();
    } while (a && b);

    if (a)
      if (*a == Branch::R)
        return true;

    if (b)
      if (*b == Branch::L)
        return true;
  }

  return false;
}

bool Number::operator>=(const Number &other) const {
  if (sign != other.sign)
    return true;

  std::optional<Branch> a, b;

  a = seq->next();
  b = other.seq->next();

  do {
    if (*a <= *b)
      return true;
    a = seq->next();
    b = other.seq->next();
  } while (a && b);

  return false;
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

  return Number{s, std::make_unique<SingleChunkIterator>(u)};
}

void test_parse_SB() {

  // ==
  Number parsed_1 = parse_SB("RLR");
  std::vector<Branch> u_1 = {Branch::R, Branch::L, Branch::R};
  Number expected_1({1, std::make_unique<SingleChunkIterator>(u_1)});
  assert(parsed_1 == expected_1);

  // !=
  Number parsed_2 = parse_SB("RLL");
  std::vector<Branch> u_2 = {Branch::R, Branch::L, Branch::R};
  Number expected_2({1, std::make_unique<SingleChunkIterator>(u_2)});
  assert(parsed_2 != expected_2);

  // <
  Number parsed_3 = parse_SB("RLRL");
  std::vector<Branch> u_3 = {Branch::R, Branch::L, Branch::R};
  Number expected_3({1, std::make_unique<SingleChunkIterator>(u_3)});
  assert(parsed_3 < expected_3);

  // <=
  Number parsed_4 = parse_SB("RLRL");
  std::vector<Branch> u_4 = {Branch::R, Branch::L, Branch::R};
  Number expected_4({1, std::make_unique<SingleChunkIterator>(u_4)});
  assert(parsed_4 < expected_4);

  // >
  Number parsed_5 = parse_SB("RLRR");
  std::vector<Branch> u_5 = {Branch::R, Branch::L, Branch::R};
  Number expected_5({1, std::make_unique<SingleChunkIterator>(u_5)});
  assert(parsed_5 > expected_5);

  // >=
  Number parsed_6 = parse_SB("RLRR");
  std::vector<Branch> u_6 = {Branch::R, Branch::L, Branch::R};
  Number expected_6({1, std::make_unique<SingleChunkIterator>(u_6)});
  assert(parsed_6 >= expected_6);

  std::cout << "Test passed: parse SB sequence" << std::endl;
}
