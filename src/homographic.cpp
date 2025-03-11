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

int hom_sign(Hom &H, const std::vector<char> &u, size_t index = 0) {
  if (index >= u.size()) {
    return sign(H.a + H.b) * sign(H.c + H.d);
  }

  auto nom_sign = lin_sign(H.a, H.b);
  auto denom_sign = lin_sign(H.c, H.d);

  if (nom_sign && denom_sign) {
    return (*nom_sign) * (*denom_sign);
  }

  if (u[index] == 'R') {
    H.right();
    __attribute__((musttail)) return hom_sign(H, u, index + 1);
  } else if (u[index] == 'L') {
    H.left();
    __attribute__((musttail)) return hom_sign(H, u, index + 1);
  } else {
    throw std::runtime_error("Invalid sequence character");
  }
}

int hom_sign(Hom &H, std::unique_ptr<Iterator> &u) {
  auto nom_sign = lin_sign(H.a, H.b);
  auto denom_sign = lin_sign(H.c, H.d);

  if (nom_sign && denom_sign) {
    return (*nom_sign) * (*denom_sign);
  }

  std::optional<Branch> next = u->next();

  if (next) {
    if (*next == Branch::R) {
      H.right();
      __attribute__((musttail)) return hom_sign(H, u);
    }

    if (*next == Branch::L) {
      H.left();
      __attribute__((musttail)) return hom_sign(H, u);
    }

    throw std::runtime_error("Unreachable code path reached.");
  } else {
    return sign(H.a + H.b) * sign(H.c + H.d);
  }
}

bool is_R_emittable(const Hom &H) {
  return (H.c <= H.a && H.d < H.b) || (H.c < H.a && H.d <= H.b);
}

bool is_L_emittable(const Hom &H) {
  return (H.a <= H.c && H.b < H.d) || (H.a < H.c && H.b <= H.d);
}

HomIterator::HomIterator(Hom H, const Number &n)
    : G(H), m({n.sign, n.seq->clone()}) {

  if (n.sign == -1) {
    G.a = -G.a;
    G.c = -G.c;
  }

  m.sign = hom_sign(G, m.seq);

  if (m.sign == 1) {
    if (G.a + G.b < 0) {
      G.a = -G.a;
      G.b = -G.b;
      G.c = -G.c;
      G.d = -G.d;
    }
  }

  if (m.sign == -1) {
    if (G.a + G.b > 0) {
      G.c = -G.c;
      G.d = -G.d;
    } else {
      G.a = -G.a;
      G.b = -G.b;
    }
  }
}

std::optional<Branch> HomIterator::next() {
  if (m.sign == 0)
    return std::nullopt;

hom_emit:
  if (is_R_emittable(G)) {
    G.a = G.a - G.c;
    G.b = G.b - G.d;
    return Branch::R;
  } else if (is_L_emittable(G)) {
    G.c = G.c - G.a;
    G.d = G.d - G.b;
    return Branch::L;
  } else {
    std::optional<Branch> b = m.seq->next();
    if (b) {
      if (b == Branch::R) {
        G.right();
        goto hom_emit;
      } else {
        G.left();
        goto hom_emit;
      }
    }
    if (G.a + G.b < G.c + G.d) {
      G.down();
      return Branch::L;
    }
    if (G.a + G.b > G.c + G.d) {
      G.up();
      return Branch::R;
    }
    return std::nullopt;
  }
}

std::unique_ptr<Iterator> HomIterator::clone() {}

int HomIterator::sign() { return m.sign; }

Number hom(Hom H, Number &n) {
  Number res;

  std::unique_ptr<HomIterator> hi = std::make_unique<HomIterator>(H, n);

  res.sign = hi->sign();
  res.seq = std::move(hi);

  return res;
}
