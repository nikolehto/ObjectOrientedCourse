#ifndef ELEMENTARYSQUAREMATRIX_H
#define ELEMENTARYSQUAREMATRIX_H

#include "valuation.h"
#include "telement.h"
#include "compositeelement.h"
#include "catch.hpp"
#include <sstream>
// #include <iostream> // DEBUG

/**
 * @file elementarysquarematrix.h
 * @version 2.5
 * @brief Declaration of ElementarySquareMatrix
 * @author Niko Lehto
 */

template <class T>
class ElementarySquareMatrix;

using ConcreteSquareMatrix = ElementarySquareMatrix<IntElement>;
using SymbolicSquareMatrix = ElementarySquareMatrix<Element>;

template <class T>
class ElementarySquareMatrix
{
    template <class T2> friend class ElementarySquareMatrix;

private:
	unsigned int n;
	std::vector<std::vector<std::shared_ptr<T>>> elements;
	void fromString(const std::string& s);
	std::shared_ptr<T> getElemPtr(std::string token);

public:
	ElementarySquareMatrix();
	ElementarySquareMatrix(const std::string& s);
    ElementarySquareMatrix(const ElementarySquareMatrix& m);
	ElementarySquareMatrix(ElementarySquareMatrix&& m);
	~ElementarySquareMatrix();

    ConcreteSquareMatrix evaluate(const Valuation& v) const;

	ConcreteSquareMatrix& operator+=(const ConcreteSquareMatrix& m);
	ConcreteSquareMatrix& operator-=(const ConcreteSquareMatrix& m);
	ConcreteSquareMatrix& operator*=(const ConcreteSquareMatrix& m);

	void print(std::ostream& os) const;
	std::string toString() const;
	ElementarySquareMatrix transpose() const;

	bool operator==(const ElementarySquareMatrix& m) const;
	ElementarySquareMatrix& operator=(const ElementarySquareMatrix& m);
	ElementarySquareMatrix& operator=(ElementarySquareMatrix&& m);

	// ISO C++ says that these are ambiguous, even though the worst conversion for the first is better than the worst conversion for the second:|
	//friend ConcreteSquareMatrix operator+(const ConcreteSquareMatrix& a, const ConcreteSquareMatrix& b);
	//friend ConcreteSquareMatrix operator-(const ConcreteSquareMatrix& a, const ConcreteSquareMatrix& b);
	//friend ConcreteSquareMatrix operator*(const ConcreteSquareMatrix& a, const ConcreteSquareMatrix& b);

	ElementarySquareMatrix operator+(const ElementarySquareMatrix& m) const;
	ElementarySquareMatrix operator-(const ElementarySquareMatrix& m) const;
	ElementarySquareMatrix operator*(const ElementarySquareMatrix& m) const;

	template<class U>
	friend std::ostream& operator<<(std::ostream& stream, const ElementarySquareMatrix<U>& m);


};
#endif
