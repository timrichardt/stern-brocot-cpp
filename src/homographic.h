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
  explicit HomIterator(Hom H, std::unique_ptr<Number> &n);
  std::optional<Branch> next() override;
  std::unique_ptr<Iterator> clone() override;
  int s;

private:
  Hom G;
	std::unique_ptr<Number> &m;
  std::optional<std::unique_ptr<Iterator>> &i;
};

std::optional<int64_t> lin_sign(int64_t a, int64_t b);
int hom_sign(Hom &H, std::unique_ptr<Iterator> &u);

std::unique_ptr<Number> hom(Hom H, std::unique_ptr<Number> &x);

#endif
