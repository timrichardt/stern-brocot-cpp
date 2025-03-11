#include "bihomographic.h"
#include "homographic.h"
#include "tree.h"
#include <optional>
#include <vector>

void Bihom::ll() {
  a += b + c + d;
  b += d;
  c += d;
  e += f + g + h;
  f += h;
  g += h;
};

void Bihom::lr() {
  a += c;
  b += a + c + d;
  d += c;
  e += g;
  f += e + g + h;
  h += g;
};

void Bihom::rl() {
  a += b;
  c += a + b + d;
  d += b;
  e += f;
  g += e + f + h;
  h += f;
};

void Bihom::rr() {
  b += a;
  c += a;
  d += a + b + c;
  f += e;
  g += e;
  h += e + f + g;
};

void Bihom::ar() {
  c += a;
  d += b;
  g += e;
  h += f;
};

void Bihom::al() {
  a += c;
  b += d;
  e += g;
  f += h;
};

void Bihom::br() {
  b += a;
  d += c;
  e += f;
  h += g;
};

void Bihom::bl() {
  a += b;
  c += d;
  e += f;
  g += h;
};

void Bihom::up() {
  a -= e;
  b -= f;
  c -= g;
  d -= h;
};

void Bihom::down() {
  e -= a;
  b -= f;
  c -= g;
  d -= h;
};

double Bihom::to_fraction() const {};

int64_t Bihom::to_N() const {};

int64_t Bihom::det() const {};

bool Bihom::operator==(const Bihom &other) const {
  return a == other.a && b == other.b && c == other.c && d == other.d &&
         e == other.e && f == other.f && g == other.g && h == other.h;
};

int8_t ssg(int64_t a, int64_t b, int64_t c, int64_t d) {
  return sign(a) + sign(b) + sign(c) + sign(d);
}

int bihom_sign(Bihom B, std::unique_ptr<Iterator> &a,
               std::unique_ptr<Iterator> &b) {
  int8_t nom_ssg = ssg(B.a, B.b, B.d, B.e);
  int8_t denom_ssg = ssg(B.e, B.f, B.g, B.h);

  std::optional<Branch> a_b, b_b;

absorb:
  a_b = a->next();
  b_b = b->next();

  // 1st part, check if sign determined
  if (B.b == 0 && B.c == 0 && B.d == 0 && B.f == 0 && B.g == 0 && B.h == 0)
    return sign(B.a) * sign(B.b);

  if (B.b == 0 && B.c == 0 && B.d == 0) {
    if (nom_ssg > 2)
      return sign(B.a);
    if (nom_ssg < -2)
      return -sign(B.a);
  }

  if (B.f == 0 && B.g == 0 && B.d == 0) {
    if (nom_ssg > 2)
      return sign(B.e);
    if (nom_ssg < -2)
      return -sign(B.e);
  }

  if (nom_ssg * denom_ssg > 8)
    return 1;
  if (nom_ssg * denom_ssg < -8)
    return -1;

  // 2nd part, check how to modify the bihom map
  if (!a_b && !b_b)
    return sign(B.a + B.b + B.c + B.d) * sign(B.e + B.f + B.g + B.h);

  if (!a_b) {
    if (*b_b == Branch::R)
      B.br();

    if (*b_b == Branch::L)
      B.bl();

    goto absorb;
  }

  if (!b_b) {
    if (*a_b == Branch::R)
      B.ar();

    if (*a_b == Branch::L)
      B.al();

    goto absorb;
  }

  if (*a_b == Branch::R && *b_b == Branch::R)
    B.rr();

  if (*a_b == Branch::R && *b_b == Branch::L)
    B.rl();

  if (*a_b == Branch::L && *b_b == Branch::R)
    B.lr();

  if (*a_b == Branch::L && *b_b == Branch::L)
    B.ll();

  goto absorb;
}

BihomIterator::BihomIterator(Bihom B, const Number &a, const Number &b)
    : C(B), m({a.sign, a.seq->clone()}), n({b.sign, b.seq->clone()}),
      H(Hom{1, 0, 0, 1}) {
  if (m.sign == -1) {
    C.a = -C.a;
    C.b = -C.b;
    C.e = -C.e;
  }
  if (n.sign == -1) {
    C.a = -C.a;
    C.c = -C.c;
    C.e = -C.e;
  }

  std::cout << bihom_sign(C, m.seq, n.seq);
}

std::optional<Branch> BihomIterator::next() {};
std::unique_ptr<Iterator> BihomIterator::clone() {};
int BihomIterator::sign() {};
