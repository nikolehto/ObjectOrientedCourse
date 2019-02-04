#include "intelement.h"
#include "catch.hpp"

/**
 *  @file intelement_tests.cpp
 *  @version 2.5
 *  @brief Test Case for IntElement class
 *  @author Niko Lehto
 *  */

/**
*  \brief Unit tests for IntElement, will run in main generated by catch.hpp
*  \return 0 if tests passes
*/
TEST_CASE("IntElement", "[isValidInt]") {

	REQUIRE_THROWS_WITH(IntElement("3,"), "Element not an integer, or it contains character");
    REQUIRE_THROWS_WITH(IntElement(",3"), "Element starts with invalid character");
    REQUIRE_THROWS_WITH(IntElement("++3"), "Element starts with invalid character");
    REQUIRE_NOTHROW(IntElement("+3"));
    REQUIRE_NOTHROW(IntElement("3"));

	int a, b, result;
	std::stringstream out_1, out_2;

	a = 3;
	b = 5;

	IntElement aie(a), bie(b), result_ie(0), result2_ie(0);

    REQUIRE_NOTHROW(std::shared_ptr<IntElement>(aie.clone()));

    std::shared_ptr<IntElement> test_ptr(aie.clone());
    REQUIRE(*test_ptr == aie);

    IntElement saie("3");

    REQUIRE(saie == a);

	a += b;
	aie += bie;

	REQUIRE(a == aie.getVal());

	a -= b;
	aie -= bie;

	REQUIRE(a == aie.getVal());

	a *= b;
	aie *= bie;

	REQUIRE(a == aie.getVal());

	out_1 << a;
	out_2 << aie;

	REQUIRE(out_1.str() == out_2.str());

	result = a + b;
	result_ie = aie + bie;

	REQUIRE(result_ie == IntElement(result));

	result = a - b;
	result_ie = aie - bie;

	REQUIRE(result_ie == IntElement(result));

	result = a * b;
	result2_ie.setVal(result);
	result_ie = aie * bie;

	REQUIRE(result_ie == result2_ie);
}
