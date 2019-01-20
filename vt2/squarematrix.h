#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "intelement.h"
#include "catch.hpp"
#include <sstream>

class SquareMatrix
{
private:
	IntElement e11, e12, e21, e22;

public:
	SquareMatrix();
	SquareMatrix(IntElement i11, IntElement i12, IntElement i21, IntElement i22);
	SquareMatrix(IntElement& i11, IntElement& i12, IntElement& i21, IntElement& i22);
	SquareMatrix(const SquareMatrix& i);
	~SquareMatrix();

	void print(std::ostream& stream) const;
	std::string toString() const;

	SquareMatrix& operator+=(const SquareMatrix& i);
	SquareMatrix& operator-=(const SquareMatrix& i);
	SquareMatrix& operator*=(const SquareMatrix& i);
	friend bool operator==(const SquareMatrix& a, const SquareMatrix& b);
	friend SquareMatrix operator+(const SquareMatrix& a, const SquareMatrix& b);
	friend SquareMatrix operator-(const SquareMatrix& a, const SquareMatrix& b);
	friend SquareMatrix operator*(const SquareMatrix& a, const SquareMatrix& b);
	friend std::ostream& operator<<(std::ostream& stream, const SquareMatrix& m);
};
#endif