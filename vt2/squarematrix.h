#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "intelement.h"
#include "catch.hpp"
#include <sstream>


/**
 * @file squarematrix.h
 * @version 1.0
 * @brief Declaration of SquareMatrix
 * @author Niko Lehto
 */
class SquareMatrix
{
private:
	IntElement e11, e12, e21, e22; 
    
public:
	SquareMatrix();
	SquareMatrix(const IntElement& i11, const IntElement& i12, const IntElement& i21, const IntElement& i22);
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