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
  // SingleChunkIterator sci = SingleChunkIterator(chunk);
  // size_t sci_index = index;

  return std::make_unique<SingleChunkIterator>(chunk);
}

bool Number::operator==(const Number &other) const {
  if (sign != other.sign)
    return false;

  std::optional<Branch> a, b;

// goto considered harmful my ass
get_branch:
  a = seq->next();
  b = other.seq->next();

  if (a) {
    if (b) {
      if (*a != *b) {
        return false;
      } else {
        goto get_branch;
      }
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
  return true;
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
  Number parsed_1 = parse_SB("RLR");
  std::vector<Branch> u_1 = {Branch::R, Branch::L, Branch::R};
  Number expected_1({1, std::make_unique<SingleChunkIterator>(u_1)});
  assert(parsed_1 == expected_1);

  // Number parsed_2 = parse_SB("RLR");
  // std::vector<Branch> u_2 = {Branch::R, Branch::L, Branch::R};
  // Number expected_2({-1, std::make_unique<SingleChunkIterator>(u_1)});
  // assert(parsed_2 != expected_2);

  // Number parsed_3 = parse_SB("RLRLLL");
  // std::vector<Branch> u_3 = {Branch::R, Branch::L, Branch::R};
  // Number expected_3({1, std::make_unique<SingleChunkIterator>(u_1)});
  // assert(parsed_3 != expected_3);

  std::cout << "Test passed: parse SB sequence" << std::endl;
}

HomIterator::HomIterator(Hom H, const Number &n)
    : G(H), m({n.sign, n.seq->clone()}) {}

std::optional<Branch> HomIterator::next() {}

std::unique_ptr<Iterator> HomIterator::clone() {}
