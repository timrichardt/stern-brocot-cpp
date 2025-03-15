#include "arithmetic.h"
#include "bihomographic.h"
#include "tree.h"

Number Number::operator+(Number &other) {
  Number a = Number{sign, seq->clone()};
  Number b = Number{other.sign, other.seq->clone()};

  return bihom(Bihom{0, 1, 1, 0, 0, 0, 0, 1}, a, b);
}

Number Number::operator-(Number &other) {
  return bihom(Bihom{0, 1, -1, 0, 0, 0, 0, 1}, *this, other);
}

Number Number::operator*(Number &other) {
  return bihom(Bihom{1, 0, 0, 0, 0, 0, 0, 1}, *this, other);
}

Number Number::operator/(Number &other) {
  return bihom(Bihom{0, 1, 0, 0, 0, 0, 1, 0}, *this, other);
}
