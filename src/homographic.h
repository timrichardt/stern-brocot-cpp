#ifndef HOMOGRAPHIC_H
#define HOMOGRAPHIC_H

#include "tree.h"
#include <cstdint>
#include <functional>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

std::optional<int64_t> lin_sign(int64_t a, int64_t b);

class HomIterator : public Iterator {
public:
  explicit HomIterator(Hom &H, Number &x);
  virtual std::optional<Branch> next() override;

private:
  Hom H;
  Number x;
  int u_sign;
  std::optional<std::variant<SingleChunkIterator, ChunkedIterator>> u;
};

bool is_R_emittable(const Hom &H);
bool is_L_emittable(const Hom &H);

int hom_sign(const Hom &H, const std::vector<char> &u, size_t index);
int hom_sign(const Hom &H, Iterator &u);

void hom_emit(const Hom &H, Iterator &u);

Number hom(Hom &H, Number &x);

void test_hom_sign();
void test_hom_sign_large();
void test_hom_sign_sqrt2();
void test_hom_sign_e();
void test_parse_SB();

#endif
