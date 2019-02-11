#ifndef CONCRETESQUAREMATRIX_H
#define CONCRETESQUAREMATRIX_H

#include "intelement.h"
#include "valuation.h"
#include "catch.hpp"
#include "symbolicmatrix.h"
#include <sstream>
// #include <iostream> // DEBUG

/**
 * @file concretematrix.h
 * @version 2.5
 * @brief Declaration of ConcreteSquareMatrix
 * @author Niko Lehto
 */
class ConcreteSquareMatrix
{
private:
	int n;
	std::vector<std::vector<std::shared_ptr<IntElement>>> elements;
	void fromString(const std::string& s);

public:
	ConcreteSquareMatrix();
	ConcreteSquareMatrix(const std::string& s);
    ConcreteSquareMatrix(const ConcreteSquareMatrix& m);
	ConcreteSquareMatrix(ConcreteSquareMatrix&& m);
	~ConcreteSquareMatrix();

	void print(std::ostream& os) const;
	std::string toString() const;
	ConcreteSquareMatrix transpose() const;

	bool operator==(const ConcreteSquareMatrix& m) const;
	ConcreteSquareMatrix& operator=(const ConcreteSquareMatrix& m);
	ConcreteSquareMatrix& operator=(ConcreteSquareMatrix&& m);
	ConcreteSquareMatrix& operator+=(const ConcreteSquareMatrix& m);
	ConcreteSquareMatrix& operator-=(const ConcreteSquareMatrix& m);
	ConcreteSquareMatrix& operator*=(const ConcreteSquareMatrix& m);
	friend ConcreteSquareMatrix operator+(const ConcreteSquareMatrix& a, const ConcreteSquareMatrix& b);
	friend ConcreteSquareMatrix operator-(const ConcreteSquareMatrix& a, const ConcreteSquareMatrix& b);
	friend ConcreteSquareMatrix operator*(const ConcreteSquareMatrix& a, const ConcreteSquareMatrix& b);
	friend std::ostream& operator<<(std::ostream& stream, const ConcreteSquareMatrix& m);

	friend class SymbolicSquareMatrix;
};
#endif
