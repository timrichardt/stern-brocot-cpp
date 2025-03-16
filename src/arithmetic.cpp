#include "arithmetic.h"
#include "bihomographic.h"
#include "tree.h"

// Number Number::operator+(Number &other) {
//   return bihom(Bihom{0, 1, 1, 0, 0, 0, 0, 1}, *this, other);
// }

// Number Number::operator-(Number &other) {
//   return bihom(Bihom{0, 1, -1, 0, 0, 0, 0, 1}, *this, other);
// }

// Number Number::operator*(Number &other) {
//   return bihom(Bihom{1, 0, 0, 0, 0, 0, 0, 1}, *this, other);
// }

// Number Number::operator/(Number &other) {
//   return bihom(Bihom{0, 1, 0, 0, 0, 0, 1, 0}, *this, other);
// }

std::unique_ptr<Number> add(std::unique_ptr<Number> &a, std::unique_ptr<Number> &b) {
  return bihom(Bihom{0, 1, 1, 0, 0, 0, 0, 1}, a, b);
}

