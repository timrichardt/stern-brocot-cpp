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

std::optional<int64_t> lin_sign(int64_t a, int64_t b);

bool is_R_emittable(const Hom &H);
bool is_L_emittable(const Hom &H);
Hom emit_R(const Hom &H);
Hom emit_L(const Hom &H);

int hom_sign(const Hom &H, const std::vector<char> &u, size_t index);
int hom_sign(const Hom &H, Iterator &u);

Hom hom_emit(const Hom &H, Iterator &u);

Iterator hom(const Hom& H, Number &r);

void test_hom_sign();
void test_hom_sign_large();
void test_hom_sign_sqrt2();
void test_hom_sign_e();
void test_parse_SB();

#endif
