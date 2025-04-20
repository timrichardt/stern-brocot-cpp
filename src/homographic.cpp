#include "homographic.h"
#include "tree.h"
#include <cstdint>
#include <memory>
#include <optional>
#include <stdexcept>
#include <vector>

std::optional<int64_t> lin_sign(int64_t a, int64_t b) {
  if (a == 0 && b == 0)
    return 0;

  int sum_of_signs = sign(a) + sign(b);
  if (sum_of_signs > 0)
    return 1;
  if (sum_of_signs < 0)
    return -1;

  return std::nullopt;
}

// int hom_sign(Hom &H, const std::vector<char> &u, size_t index = 0) {
//   if (index >= u.size()) {
//     return sign(H.a + H.b) * sign(H.c + H.d);
//   }

//   auto nom_sign = lin_sign(H.a, H.b);
//   auto denom_sign = lin_sign(H.c, H.d);

//   if (nom_sign && denom_sign) {
//     return (*nom_sign) * (*denom_sign);
//   }

//   if (u[index] == 'R') {
//     H.right();
//     __attribute__((musttail)) return hom_sign(H, u, index + 1);
//   } else if (u[index] == 'L') {
//     H.left();
//     __attribute__((musttail)) return hom_sign(H, u, index + 1);
//   } else {
//     throw std::runtime_error("Invalid sequence character");
//   }
// }

int hom_sign(Hom &H, Iterator *u) {
  std::optional<Branch> next;

absorb:
  auto nom_sign = lin_sign(H.a, H.b);
  auto denom_sign = lin_sign(H.c, H.d);

  if (nom_sign && denom_sign) {
    return (*nom_sign) * (*denom_sign);
  }

  next = u->next();

  if (next) {
    if (*next == Branch::R) {
      H.right();
    }

    if (*next == Branch::L) {
      H.left();
    }
    goto absorb;
  } else {
    return sign(H.a + H.b) * sign(H.c + H.d);
  }
}

inline bool Hom::R_emittable() {
  return (c <= a && d < b) || (c < a && d <= b);
}

inline bool Hom::L_emittable() {
  return (a <= c && b < d) || (a < c && b <= d);
}

int HomIterator::hom_sign() {
  std::optional<Branch> next;

absorb:
  auto nom_sign = lin_sign(G.a, G.b);
  auto denom_sign = lin_sign(G.c, G.d);

  if (nom_sign && denom_sign) {
    return (*nom_sign) * (*denom_sign);
  }

  next = m->seq->next();

  if (next) {
    if (*next == Branch::R) {
      G.right();
    }

    if (*next == Branch::L) {
      G.left();
    }
    goto absorb;
  } else {
    return sign(G.a + G.b) * sign(G.c + G.d);
  }
}

// inline bool Hom::R_emittable() {
//   return (c <= a && d < b) || (c < a && d <= b);
// }

// inline bool Hom::L_emittable() {
//   return (a <= c && b < d) || (a < c && b <= d);
// }

HomIterator::HomIterator(Hom H, Number &n, bool clone)
    : G_init(H), G(H), m(clone ? n.clone() : &n), i(std::nullopt) {

  if (m->sign == -1) {
    G.a = -G.a;
    G.c = -G.c;
  }

  s = hom_sign();

  if (s == 0) {
    i = new NullIterator();
  }

  if (s == 1) {
    if (G.a + G.b <= 0) {
      G.a = -G.a;
      G.b = -G.b;
      G.c = -G.c;
      G.d = -G.d;
    }
  }

  if (s == -1) {
    if (G.a + G.b > 0) {
      G.c = -G.c;
      G.d = -G.d;
    } else {
      G.a = -G.a;
      G.b = -G.b;
    }
  }
}

HomIterator::~HomIterator() {}

std::optional<Branch> HomIterator::next() {
  // std::cout << "homiter next called" << std::endl;

  if (s == 0)
    return std::nullopt;

  std::optional<Branch> b;

hom_emit:
  // std::cout << G << std::endl;

  if (i) {
    return (*i)->next();
  }

  // std::cout << std::endl << G << std::endl;
  if (G.R_emittable()) {
    G.up();
    return Branch::R;
  } else if (G.L_emittable()) {
    G.down();
    return Branch::L;
  } else {
    b = m->seq->next();
    if (b) {
      if (b == Branch::R) {
        G.right();
      } else {
        G.left();
      }
      goto hom_emit;
    }

    i = fraction_to_SSB(G.a + G.b, G.c + G.d)->seq;

    goto hom_emit;
  }
}

Iterator *HomIterator::clone() { return new HomIterator(G_init, *m->clone()); }

Number *hom(Hom H, Number *n) {
  HomIterator *hi = new HomIterator(H, *n);

  return new Number(hi->s, hi);
  // return Number{hi->s, res.seq->clone()};
}
