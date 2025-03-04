#ifndef HOMOGRAPHIC_H
#define HOMOGRAPHIC_H

#include <cstdint>
#include <functional>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>
#include "tree.h"

int sgn(int64_t a);

std::optional<int64_t> lin_sign(int64_t a, int64_t b);

bool is_R_emittable(const Node &H);
bool is_L_emittable(const Node &H);
Node emit_R(const Node &H);
Node emit_L(const Node &H);

int hom_sign(const Node &H, const std::vector<char> &u, size_t index);
int hom_sign(const Node &H, ChunkedIterator &u);

Node hom_emit(const Node &H, ChunkedIterator &u);

void test_hom_sign();
void test_hom_sign_large();
void test_hom_sign_sqrt2();
void test_hom_sign_e();
void test_parse_SB();

#endif
