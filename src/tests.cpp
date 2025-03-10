#include "tree.h"
#include "tests.h"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

void test_parse_SSB() {
  Number parsed_1 = parse_SSB("RLR");
  std::vector<Branch> u_1 = {Branch::R, Branch::L, Branch::R};
  Number expected_1({1, std::make_unique<SingleChunkIterator>(u_1)});
  assert(parsed_1 == expected_1);

  Number parsed_2 = parse_SSB("-RLL");
  std::vector<Branch> u_2 = {Branch::R, Branch::L, Branch::L};
	Number expected_2({-1, std::make_unique<SingleChunkIterator>(u_2)});
  assert(parsed_2 == expected_2);

  Number parsed_3 = parse_SSB("0");
  std::vector<Branch> u_3 = {};
  Number expected_3({0, std::make_unique<SingleChunkIterator>(u_3)});
	  assert(parsed_3 == expected_3);
	
	std::cout << "Test passed: parse SSB sequences" << std::endl;
}

void test_number_comparators() {
  // ==
  Number lhs_1 = parse_SSB("RLR");
	Number rhs_1 = parse_SSB("RLR");
  assert(lhs_1 == rhs_1);
	assert((lhs_1 != rhs_1) == false);

  // !=
  Number lhs_2 = parse_SSB("RLL");
	Number rhs_2 = parse_SSB("RLR");
  assert(lhs_2 != rhs_2);
	assert((lhs_2 == rhs_2) == false);

  // <
  Number lhs_3 = parse_SSB("RLRL");
	Number rhs_3 = parse_SSB("RLR");
  assert(lhs_3 < rhs_3);
	assert((lhs_3 >= rhs_3) == false);

  // <=
  Number lhs_4 = parse_SSB("RLRL");
	Number rhs_4= parse_SSB("RLR");
  assert(lhs_4 <= rhs_4);
	assert((lhs_4 > rhs_4) == false);

  // >
  Number lhs_5 = parse_SSB("RLRR");
	Number rhs_5 = parse_SSB("RLR");
  assert(lhs_5 > rhs_5);
	assert((lhs_5 <= rhs_5) == false);

  // >=
  Number lhs_6 = parse_SSB("RLRR");
	Number rhs_6 = parse_SSB("RLR");
  assert(lhs_6 >= rhs_6);
	assert((lhs_6 < rhs_6) == false);

	std::cout << "Test passed: number comparators" << std::endl;
}
