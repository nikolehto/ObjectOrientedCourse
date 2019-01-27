#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "intelement.h"
#include "catch.hpp"
#include <sstream>


/**
 * @file squarematrix.h
 * @version 2.0
 * @brief Declaration of SquareMatrix
 * @author Niko Lehto
 */
class SquareMatrix
{
private:
	int n;
	std::vector<std::vector<IntElement>> elements;
	void fromString(const std::string& s);

public:
	SquareMatrix();
	SquareMatrix(const std::string& s);
	SquareMatrix(const SquareMatrix& m);
	~SquareMatrix();

	void print(std::ostream& os) const;
	std::string toString() const;
	SquareMatrix& transpose() const;

	bool operator==(const SquareMatrix& m) const;
	SquareMatrix& operator=(const SquareMatrix& m);
	SquareMatrix& operator+=(const SquareMatrix& m);
	SquareMatrix& operator-=(const SquareMatrix& m);
	SquareMatrix& operator*=(const SquareMatrix& m);
	friend SquareMatrix operator+(const SquareMatrix& a, const SquareMatrix& b);
	friend SquareMatrix operator-(const SquareMatrix& a, const SquareMatrix& b);
	friend SquareMatrix operator*(const SquareMatrix& a, const SquareMatrix& b);
	friend std::ostream& operator<<(std::ostream& stream, const SquareMatrix& m);
};
#endif
