#include "tree.h"
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

HomIterator::HomIterator(Hom H, const Number &n)
    : G(H), m({n.sign, n.seq->clone()}) {}

std::optional<Branch> HomIterator::next() {}

std::unique_ptr<Iterator> HomIterator::clone() {}
