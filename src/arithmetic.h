#include "bihomographic.h"
#include "tree.h"

// Operator overload implementations

/* Number Number::operator-(const Number &other) const { return Number(); } */

/* Number Number::operator*(const Number &other) const { return Number(); } */

/* Number Number::operator/(const Number &other) const { return Number(); } */

Number add(const Number &a, const Number &b);

std::unique_ptr<Number> add(std::unique_ptr<Number> &a, std::unique_ptr<Number> &b);
