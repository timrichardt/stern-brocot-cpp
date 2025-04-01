#include "arithmetic.h"
#include "bihomographic.h"
#include "homographic.h"
#include "tree.h"

Number *add(Number *a, Number *b) {
  return bihom(Bihom{0, 1, 1, 0, 0, 0, 0, 1}, a, b);
}

Number *sub(Number *a, Number *b) {
  return bihom(Bihom{0, 1, -1, 0, 0, 0, 0, 1}, a, b);
}

Number *mul(Number *a, Number *b) {
  return bihom(Bihom{1, 0, 0, 0, 0, 0, 0, 1}, a, b);
}

Number *div(Number *a, Number *b) {
  return bihom(Bihom{0, 1, 0, 0, 0, 0, 1, 0}, a, b);
}

Number *inv(Number *a) {
  return new Number(a->sign, hom(Hom{0, 1, 1, 0}, a)->seq);
}
