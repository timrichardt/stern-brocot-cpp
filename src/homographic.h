#ifndef HOMOGRAPHIC_H
#define HOMOGRAPHIC_H

#include "tree.h"
#include <functional>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

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

int hom_sign(Hom &H, std::unique_ptr<Iterator> &u);

Number hom(Hom H, Number &x);

#endif
