#ifndef HOMOGRAPHIC_H
#define HOMOGRAPHIC_H

#include "tree.h"
#include <functional>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

std::optional<int64_t> lin_sign(int64_t a, int64_t b);

class HomIterator : public Iterator {
public:
  explicit HomIterator(Hom H, const Number &n);
  std::optional<Branch> next() override;
  std::unique_ptr<Iterator> clone() override;
  int sign();

private:
  Hom G;
  Number m;
};

bool is_R_emittable(const Hom &H);
bool is_L_emittable(const Hom &H);

int hom_sign(Hom &H, std::unique_ptr<Iterator> &u);

Number hom(Hom H, Number &x);

#endif
