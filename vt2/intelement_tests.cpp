#include "intelement.h"
#include "catch.hpp"

TEST_CASE("A", "[isValidInt]") {
	int a, b, result;
	std::stringstream out_1, out_2;

	a = 3;
	b = 5;

	IntElement aie(a), bie(b), result_ie(0);

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
	result_ie = aie * bie;

	REQUIRE(result_ie == IntElement(result));
}