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

std::optional<int64_t> linSgn(int64_t a, int64_t b);

bool emitU(const Node &H);
bool emitD(const Node &H);
Node U(const Node &H);
Node D(const Node &H);

int homSgn(const Node &H, const std::vector<char> &u, size_t index);
int homSgn(const Node &H, ChunkedIterator &u);

Node homEmit(const Node &H, ChunkedIterator &u);

void testHomSgn();
void testHomSgnLarge();
void testHomSgnSqrt2();
void testHomSgnE();
void testParseSB();

#endif
