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
  b += a + c + d;
  a += c;
  d += c;
  f += e + g + h;
  e += g;
  h += g;
};

void Bihom::rl() {
  c += a + b + d;
  a += b;
  d += b;
  g += e + f + h;
  e += f;
  h += f;
};

void Bihom::rr() {
  d += a + b + c;
  b += a;
  c += a;
  h += e + f + g;
  f += e;
  g += e;
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
  f += e;
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
  f -= b;
  g -= c;
  h -= d;
};

double Bihom::to_double() const {
  return static_cast<double>(a + b + c + d) /
         static_cast<double>(e + f + g + h);
};

int64_t Bihom::to_N() const { return (a + b + c + d) * (e + f + g + h); };

bool Bihom::operator==(const Bihom &other) const {
  return a == other.a && b == other.b && c == other.c && d == other.d &&
         e == other.e && f == other.f && g == other.g && h == other.h;
};

int8_t ssg(int64_t a, int64_t b, int64_t c, int64_t d) {
  return sign(a) + sign(b) + sign(c) + sign(d);
}

int bihom_sign(Bihom &B, std::unique_ptr<Iterator> &a,
               std::unique_ptr<Iterator> &b) {
  int8_t nom_ssg = ssg(B.a, B.b, B.c, B.d);
  int8_t denom_ssg = ssg(B.e, B.f, B.g, B.h);

  std::optional<Branch> a_b, b_b;

absorb:
  std::cout << "next sign iter" << std::endl;
  std::cout << B << std::endl;

  // 1st part, check if sign determined
  if (B.b == 0 && B.c == 0 && B.d == 0 && B.f == 0 && B.g == 0 && B.h == 0)
    return sign(B.a) * sign(B.e);

  if (B.b == 0 && B.c == 0 && B.d == 0) {
    if (nom_ssg > 2)
      return sign(B.a);
    if (denom_ssg < -2)
      return -sign(B.a);
  }

  if (B.f == 0 && B.g == 0 && B.d == 0) {
    if (denom_ssg > 2)
      return sign(B.e);
    if (nom_ssg < -2)
      return -sign(B.e);
  }

  if (nom_ssg * denom_ssg > 8)
    return 1;
  if (nom_ssg * denom_ssg < -8)
    return -1;

  // 2nd part, check how to modify the bihom map
  a_b = a->next();
  b_b = b->next();

  if (!a_b && !b_b)
    return sign(B.a + B.b + B.c + B.d) * sign(B.e + B.f + B.g + B.h);

  if (!a_b) {
    B = {0, 0, B.c + B.a, B.b + B.d, 0, 0, B.e + B.g, B.f + B.h};

    if (*b_b == Branch::R) {
      std::cout << "bR" << std::endl;
      std::cout << "B before bR" << std::endl;
      std::cout << B << std::endl;
      B.br();
      std::cout << "B after bR" << std::endl;
      std::cout << B << std::endl;
    }

    if (*b_b == Branch::L) {
      std::cout << "bL" << std::endl;
      std::cout << "B before bL" << std::endl;
      std::cout << B << std::endl;
      B.bl();
      std::cout << "B after bL" << std::endl;
      std::cout << B << std::endl;
    }

    goto absorb;
  }

  if (!b_b) {
    B = {0, B.a + B.b, 0, B.c + B.d, 0, B.e + B.f, 0, B.g + B.h};

    if (*a_b == Branch::R) {
      std::cout << "aR" << std::endl;
      B.ar();
    }

    if (*a_b == Branch::L) {
      std::cout << "aL" << std::endl;
      std::cout << "B before aL" << std::endl;
      std::cout << B << std::endl;
      B.al();
      std::cout << "B after aL" << std::endl;
      std::cout << B << std::endl;
    }

    goto absorb;
  }

  if (*a_b == Branch::R && *b_b == Branch::R) {
    std::cout << "RR" << std::endl;
    std::cout << "B before RR" << std::endl;
    std::cout << B << std::endl;
    B.rr();
    std::cout << "B after RR" << std::endl;
    std::cout << B << std::endl;
  }

  if (*a_b == Branch::R && *b_b == Branch::L) {
    std::cout << "RL" << std::endl;
    B.rl();
  }

  if (*a_b == Branch::L && *b_b == Branch::R) {
    std::cout << "LR" << std::endl;
    B.lr();
  }

  if (*a_b == Branch::L && *b_b == Branch::L) {
    std::cout << "LL" << std::endl;
    B.ll();
  }

  goto absorb;
}

std::optional<std::unique_ptr<Iterator>> bhni = std::nullopt;

BihomIterator::BihomIterator(Bihom B, Number &a, Number &b)
    : C(B), m(a), n(b), hi(bhni) {

  hi = std::nullopt;

  if (m.sign == -1) {
    C.a = -C.a;
    C.b = -C.b;
    C.e = -C.e;
    C.f = -C.f;
  }
  if (n.sign == -1) {
    C.a = -C.a;
    C.c = -C.c;
    C.e = -C.e;
    C.g = -C.g;
  }

  s = bihom_sign(C, a.seq, b.seq);

  if (s == 0) {
    hi = std::make_unique<NullIterator>();
    return;
  }

  if (s == 1 && (C.a + C.b + C.c + C.d <= 0)) {
    C.a = -C.a;
    C.b = -C.b;
    C.c = -C.c;
    C.d = -C.d;
    C.e = -C.e;
    C.f = -C.f;
    C.g = -C.g;
    C.h = -C.h;
  }

  if (s == -1) {
    if (C.a + C.b + C.c + C.d <= 0) {
      C.a = -C.a;
      C.b = -C.b;
      C.c = -C.c;
      C.d = -C.d;
    } else {
      C.e = -C.e;
      C.f = -C.f;
      C.g = -C.g;
      C.h = -C.h;
    }
  }

  if (C.same_ratio()) {
    if (C.h != 0) {
      hi = fraction_to_SSB(C.d, C.h).seq;
    } else if (C.g != 0) {
      hi = fraction_to_SSB(C.c, C.g).seq;
    } else if (C.f != 0) {
      hi = fraction_to_SSB(C.b, C.f).seq;
    } else {
      hi = fraction_to_SSB(C.a, C.e).seq;
    }
  }
}

inline bool Bihom::same_ratio() {
  return a * f == b * e && b * g == c * f && c * h == d * g && a * g == c * e &&
         a * h == d * e && b * h == d * f;
}

inline bool Bihom::R_emittable() {
  return (e <= a && f <= b && g <= c && h < d) ||
         (e <= a && f <= b && g < c && h <= d) ||
         (e <= a && f < b && g <= c && h <= d) ||
         (e < a && f <= b && g <= c && h <= d);
}

inline bool Bihom::L_emittable() {
  return (a <= e && b <= f && c <= g && d < h) ||
         (a <= e && b <= f && c < g && d <= h) ||
         (a <= e && b < f && c <= g && d <= h) ||
         (a < e && b <= f && c <= g && d <= h);
}

std::optional<Branch> BihomIterator::next() {
  if (s == 0)
    return std::nullopt;

  std::optional<Branch> b_m, b_n;

absorb:
  std::cout << std::endl << C << std::endl;

  if (hi) {
    // std::cout << "a and b exhausted" << std::endl;
    return (*hi)->next();
  }

  if (C.R_emittable()) {
    // std::cout << "R emittable" << std::endl;
    // std::cout << C << std::endl;

    C.up();
    return Branch::R;
  }

  if (C.L_emittable()) {
    // std::cout << "L emittable" << std::endl;
    // std::cout << C << std::endl;

    C.down();
    return Branch::L;
  }

  b_m = m.seq->next();
  b_n = n.seq->next();

  if (!b_m && !b_n) {
    // std::cout << "a and b exhausted" << std::endl;
    // std::cout << C << std::endl;

    int64_t n = C.a + C.b + C.c + C.d;
    int64_t d = C.e + C.f + C.g + C.h;

    // std::cout << "nom   " << n << std::endl;
    // std::cout << "denom " << d << std::endl;

    hi = fraction_to_SSB(n, d).seq;

    goto absorb;
  }

  if (!b_n) {
    // std::cout << "a exhausted" << std::endl;

    // C = {0, C.a + C.b, 0, C.c + C.d, 0, C.e + C.f, 0, C.g + C.h};

    // if (*b_m == Branch::R)
    //   C.ar();
    // if (*b_m == Branch::L)
    //   C.al();

    Hom h = {C.a + C.b, C.c + C.d, C.e + C.f, C.g + C.h};
    if (*b_m == Branch::R)
      h.right();
    if (*b_m == Branch::L)
      h.left();

    hi = std::make_unique<HomIterator>(h, m);

    goto absorb;
  }

  if (!b_m) {
    // std::cout << "b exhausted" << std::endl;

    // std::cout << C << std::endl;

    // C = {0, 0, C.c + C.a, C.b + C.d, 0, 0, C.e + C.g, C.f + C.h};

    // if (*b_n == Branch::R)
    //   C.br();
    // if (*b_n == Branch::L)
    //   C.bl();

    Hom h = Hom{C.a + C.c, C.b + C.d, C.e + C.g, C.f + C.h};
    if (*b_n == Branch::R)
      h.right();
    if (*b_n == Branch::L)
      h.left();

    hi = std::make_unique<HomIterator>(h, n);

    goto absorb;
  }

  // std::cout << "need to absorb" << std::endl;

  if (*b_m == Branch::R && *b_n == Branch::R)
    C.rr();

  if (*b_m == Branch::R && *b_n == Branch::L)
    C.rl();

  if (*b_m == Branch::L && *b_n == Branch::R)
    C.lr();

  if (*b_m == Branch::L && *b_n == Branch::L)
    C.ll();

  goto absorb;
}

std::unique_ptr<Iterator> BihomIterator::clone() {
  return std::make_unique<BihomIterator>(C, m, n);
};

std::ostream &operator<<(std::ostream &os, Bihom B) {
  os << B.a << " " << B.b << " " << B.c << " " << B.d << std::endl;
  os << B.e << " " << B.f << " " << B.g << " " << B.h << std::endl;
  return os;
}

Number bihom(Bihom B, Number &&a, Number &&b) {
  Number res;

  std::unique_ptr<BihomIterator> bi = std::make_unique<BihomIterator>(B, a, b);

  res.sign = bi->s;
  res.seq = std::move(bi);

  return res;
}
