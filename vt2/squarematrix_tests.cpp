#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "squarematrix.h"
#include "intelement.h"

/**
 *  @file squarematrix_tests.cpp
 *  @version 1.0
 *  @brief Test Case for SquareMatrix class
 *  @author Niko Lehto
 *  */

TEST_CASE("SquareMatrix", "[SquareMatrix]") {
	SquareMatrix a(IntElement(1), IntElement(2), IntElement(3), IntElement(4))
		, b(IntElement(2), IntElement(3), IntElement(4), IntElement(5))
		, result1(IntElement(3), IntElement(5), IntElement(7), IntElement(9))
		, result3(IntElement(10), IntElement(13), IntElement(22), IntElement(29))
		, clone_constructed_a = a
		, empty_constructed;

	REQUIRE(a == clone_constructed_a);

	std::string a_string = "[[1,2][3,4]]";
	std::string b_string = "[[2,3][4,5]]";
	std::string result3_string = "[[10,13][22,29]]";

	std::stringstream out_1, out_2, out_3, out_4;

	a += b;

	REQUIRE(a == result1);

	a -= b;

	REQUIRE(a == clone_constructed_a);

	a *= b;

	REQUIRE(a == result3);

	out_1 << b;
	out_2 << b_string;

	REQUIRE(out_1.str() == out_2.str());

	out_1.str("");
	out_2.str("");

	out_1 << a;
	out_2 << result3_string;

	REQUIRE(out_1.str() == out_2.str());

	result3.print(out_3);
	REQUIRE(out_1.str() == out_3.str());

	out_4 << result3.toString();
	REQUIRE(out_1.str() == out_4.str());

	REQUIRE(clone_constructed_a + b == result1);

	REQUIRE(result1 - b == clone_constructed_a);

	REQUIRE(clone_constructed_a * b == result3);

	REQUIRE(clone_constructed_a + empty_constructed == clone_constructed_a);
}