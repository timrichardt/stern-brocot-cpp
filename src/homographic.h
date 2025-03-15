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
  ~HomIterator();
  explicit HomIterator(Hom H, Number &n);
  std::optional<Branch> next() override;
  std::unique_ptr<Iterator> clone() override;
  int s;

private:
  Hom G;
  Number &m;
  std::optional<std::unique_ptr<Iterator>> &i;
};

int hom_sign(Hom &H, std::unique_ptr<Iterator> &u);

Number hom(Hom H, Number &x);

#endif
