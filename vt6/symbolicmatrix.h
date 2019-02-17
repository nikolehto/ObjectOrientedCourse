#ifndef SYMBOLICSQUAREMATRIX_H
#define SYMBOLICSQUAREMATRIX_H

#include "varelement.h"
#include "valuation.h"
#include "intelement.h"
#include "concretematrix.h"
#include "catch.hpp"
#include <sstream>
// #include <iostream> // DEBUG

/**
 * @file symbolicmatrix.h
 * @version 2.5
 * @brief Declaration of SymbolicSquareMatrix
 * @author Niko Lehto
 */

 // forward declaration
class ConcreteSquareMatrix;

class SymbolicSquareMatrix
{
private:
	unsigned int n;
	std::vector<std::vector<std::shared_ptr<Element>>> elements;
	void fromString(const std::string& s);

public:
	SymbolicSquareMatrix();
	SymbolicSquareMatrix(const std::string& s);
    SymbolicSquareMatrix(const SymbolicSquareMatrix& m);
	SymbolicSquareMatrix(SymbolicSquareMatrix&& m);
	~SymbolicSquareMatrix();

    ConcreteSquareMatrix evaluate(const Valuation& v) const;

	void print(std::ostream& os) const;
	std::string toString() const;
	SymbolicSquareMatrix transpose() const;

	bool operator==(const SymbolicSquareMatrix& m) const;
	SymbolicSquareMatrix& operator=(const SymbolicSquareMatrix& m);
	SymbolicSquareMatrix& operator=(SymbolicSquareMatrix&& m);

	friend std::ostream& operator<<(std::ostream& stream, const SymbolicSquareMatrix& m);
};
#endif
