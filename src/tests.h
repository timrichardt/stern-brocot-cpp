#ifndef TESTS_H
#define TESTS_H

#include "homographic.h"
#include "tree.h"
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

// "tree.h" tests
void test_parse_SSB();
void test_number_comparators();

// "homographic.h" tests
void test_hom_sign();
void test_hom_sign_large();
void test_hom_sign_sqrt2();
void test_hom_sign_e();
void test_parse_SB();

#endif
