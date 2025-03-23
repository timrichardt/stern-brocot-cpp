#include "src/arithmetic.h"
#include "src/bihomographic.h"
#include "src/tests.h"
#include "src/tree.h"
#include <iostream>

int main() {
  std::cout << "Tests: ----------------" << std::endl;
  test_parse_SSB();
  test_number_comparators();
  test_hom_sign();
  test_hom_sign_large();
  test_hom_sign_sqrt2();
  test_hom_sign_e();
  test_hom();
  test_bihom_sign();
  test_bihom();
  test_arithmetic_binary();
  std::cout << "-----------------------" << std::endl;

	Number* e1 = new Number(1, make_e());
	Number* e2 = new Number(1, make_e());
	Number* e3 = new Number(1, make_e());
	Number* phi = new Number(1, make_phi());
	Number* r = add(e1, e2);
	Number* s = add(r, phi);
	Number* t = add(s, e3);

	Number* o = take(100, t);
	
	std::cout << o->to_double() << std::endl;
  
  return 0;
}
