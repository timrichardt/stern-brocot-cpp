#include "arithmetic.h"
#include "bihomographic.h"
#include "homographic.h"
#include "tree.h"

Number *Number::operator+(Number *&other) {
  Number *a = this;
  Number *b = other;
  // Number *res = bihom(Bihom{0, 1, 1, 0, 0, 0, 0, 1}, a, b);
  // return res;

  return add(a, other);
}

// Number Number::operator-(Number &other) {
//   return bihom(Bihom{0, 1, -1, 0, 0, 0, 0, 1}, *this, other);
// }

// Number Number::operator*(Number &other) {
//   return bihom(Bihom{1, 0, 0, 0, 0, 0, 0, 1}, *this, other);
// }

// Number Number::operator/(Number &other) {
//   return bihom(Bihom{0, 1, 0, 0, 0, 0, 1, 0}, *this, other);
// }

Number *add(Number *a, Number *b) {
  return bihom(Bihom{0, 1, 1, 0, 0, 0, 0, 1}, a, b);
}

Number *sub(Number *&a, Number *&b) {
  return bihom(Bihom{0, 1, -1, 0, 0, 0, 0, 1}, a, b);
}

Number *mul(Number *&a, Number *&b) {
  return bihom(Bihom{1, 0, 0, 0, 0, 0, 0, 1}, a, b);
}

Number *div(Number *&a, Number *&b) {
  return bihom(Bihom{0, 1, 0, 0, 0, 0, 1, 0}, a, b);
}

Number *inv(Number *&a) {
  return new Number(a->sign, hom(Hom{0, 1, 1, 0}, a)->seq);
}
