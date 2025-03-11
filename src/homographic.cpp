#include "tree.h"
#include "homographic.h"
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <stdexcept>

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

void hom_emit(Hom &H, Iterator &u) {
  if (is_R_emittable(H)) {
    H.a = H.a - H.c;
    H.b = H.b - H.d;
  } else if (is_L_emittable(H)) {
    H.c = H.c - H.a;
    H.d = H.d - H.b;
  } else {
    auto next = u.next();
    if (next == Branch::R) {
      H.right();
    } else {
      H.left();
    }
  }
}

// Iterator hom_sb(Hom &H, Iterator &u) {
//   Iterator r;
//   if (H.det() == 0) {
//     fraction_to_SSB((int64_t)(H.a + H.b), (int64_t)(H.c + H.d));
//   } else {
//     int sign = hom_sign(H, u);
//     switch (sign) {
//     case 0:
//       return r;
//     case 1:
//       return r;
//     case -1:
//       return r;
//     };
//   }
//   return r;
// }

HomIterator::HomIterator(Hom H, const Number &n)
	: G(H), m({n.sign, n.seq->clone()}) {

	if (n.sign == -1) {
		G.a = -G.a;
		G.c = -G.c;
	}

	m.sign = hom_sign(G, m.seq);

	std::cout << "sign: " << m.sign << std::endl;
}

std::optional<Branch> HomIterator::next() {
	
}

std::unique_ptr<Iterator> HomIterator::clone() {}
