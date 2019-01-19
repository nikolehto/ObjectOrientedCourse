#include <sstream>
#include "intelement.h"
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"



IntElement::IntElement()
{
	intelement = 0;
}

IntElement::IntElement(int v)
{
	intelement = v;
}

IntElement::~IntElement() = default;

int IntElement::getVal() const
{
	return intelement;
}

void IntElement::setVal(int v)
{
	intelement = v;
}

IntElement& IntElement::operator+=(const IntElement& i)
{
	intelement = intelement + i.getVal();
	return *this;
}

IntElement& IntElement::operator-=(const IntElement& i)
{
	intelement = intelement - i.getVal();
	return *this;
}

IntElement& IntElement::operator*=(const IntElement& i)
{
	intelement = intelement * i.getVal();
	return *this;
}

std::ostream& operator<<(std::ostream& o, const IntElement& v)
{
	o << std::to_string(v.intelement);
	return o;
}


TEST_CASE("A", "[isValidInt]") {
	int a, b, result;
	std::stringstream out_1, out_2;

	a = 3;
	b = 5;
	result = 0;

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

}