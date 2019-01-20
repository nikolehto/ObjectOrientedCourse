#include "squarematrix.h"
#include "catch.hpp"

SquareMatrix::SquareMatrix()
{
	e11 = 0;
	e12 = 0;
	e21 = 0;
	e22 = 0;
}

SquareMatrix::SquareMatrix(const IntElement& i11, const IntElement& i12, const IntElement& i21, const IntElement& i22)
{
	e11 = i11;
	e12 = i12;
	e21 = i21;
	e22 = i22;
}

SquareMatrix::SquareMatrix(const SquareMatrix& i)
{
	this->e11 = i.e11;
	this->e12 = i.e12;
	this->e21 = i.e21;
	this->e22 = i.e22;
}

SquareMatrix::~SquareMatrix() = default;

void SquareMatrix::print(std::ostream & stream) const
{
	stream << *this;
	return;
}

std::string SquareMatrix::toString() const
{
	std::stringstream result;
	result << *this;
	return result.str();
}

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

std::ostream& operator<<(std::ostream& stream, const SquareMatrix& m)
{
	stream << "[[" << m.e11 << "," << m.e12 << "][" << m.e21 << "," << m.e22 << "]]";
	return stream;
}

bool operator==(const SquareMatrix& a, const SquareMatrix& b)
{
	return a.e11 == b.e11 && a.e12 == b.e12 && a.e21 == b.e21 && a.e22 == b.e22;
}