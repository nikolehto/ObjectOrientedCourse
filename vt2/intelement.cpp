#include "catch.hpp"

#include "intelement.h"

IntElement::IntElement()
{
	intelement = 0;
}

IntElement::IntElement(int v)
{
	intelement = v;
}

IntElement::IntElement(const IntElement& i)
{
	intelement = i.getVal();
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

IntElement operator+(const IntElement& a, const IntElement& b)
{
	IntElement t_a(a);
	t_a += b;
	return t_a;
}

IntElement operator-(const IntElement& a, const IntElement& b)
{
	IntElement t_a(a);
	t_a -= b;
	return t_a;
}

IntElement operator*(const IntElement& a, const IntElement& b)
{
	IntElement t_a(a);
	t_a *= b;
	return t_a;
}

std::ostream& operator<<(std::ostream& o, const IntElement& v)
{
	o << std::to_string(v.intelement);
	return o;
}

bool operator==(const IntElement& a, const IntElement& b)
{
	return a.getVal() == b.getVal();
}