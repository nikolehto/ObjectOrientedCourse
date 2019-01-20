#include "squarematrix.h"
#include "catch.hpp"

SquareMatrix::SquareMatrix()
{
	e11 = 0;
	e12 = 0;
	e21 = 0;
	e22 = 0;
}

SquareMatrix::SquareMatrix(IntElement i11, IntElement i12, IntElement i21, IntElement i22)
{
	e11 = i11;
	e12 = i12;
	e21 = i21;
	e22 = i22;
}

SquareMatrix::SquareMatrix(IntElement& i11, IntElement& i12, IntElement& i21, IntElement& i22)
{
	e11 = i11;
	e12 = i12;
	e21 = i21;
	e22 = i22;
}

SquareMatrix::SquareMatrix(const SquareMatrix& i)
{
	*this = SquareMatrix() + i; // TODO TEST
}

SquareMatrix::~SquareMatrix() = default;

SquareMatrix& SquareMatrix::operator+=(const SquareMatrix& i)
{
	e11 += i.e11;
	e12 += i.e12;
	e21 += i.e21;
	e22 += i.e22;
	return *this;
}

SquareMatrix& SquareMatrix::operator-=(const SquareMatrix& i)
{
	e11 -= i.e11;
	e12 -= i.e12;
	e21 -= i.e21;
	e22 -= i.e22;
	return *this;
}

SquareMatrix& SquareMatrix::operator*=(const SquareMatrix& i)
{
	SquareMatrix temp(*this);

	e11 = temp.e11 * i.e11 + temp.e12 * i.e21;
	e12 = temp.e11 * i.e12 + temp.e12 * i.e22;
	e21 = temp.e21 * i.e11 + temp.e22 * i.e21;
	e22 = temp.e21 * i.e12 + temp.e22 * i.e22;

	return *this;
}

SquareMatrix operator+(const SquareMatrix& a, const SquareMatrix& b)
{
	SquareMatrix t_a(a);
	t_a += b;
	return t_a;
}

SquareMatrix operator-(const SquareMatrix& a, const SquareMatrix& b)
{
	SquareMatrix t_a(a);
	t_a -= b;
	return t_a;
}

SquareMatrix operator*(const SquareMatrix& a, const SquareMatrix& b)
{
	SquareMatrix t_a(a);
	t_a *= b;
	return t_a;
}

std::ostream& operator<<(std::ostream& o, const SquareMatrix& v)
{
	o << "[[" << v.e11 << "," << v.e12 << "][" << v.e21 << "," << v.e22 << "]]";
	return o;
}

bool operator==(const SquareMatrix& a, const SquareMatrix& b)
{
	return a.e11 == b.e11 && a.e12 == b.e12 && a.e21 == b.e21 && a.e22 == b.e22;
}