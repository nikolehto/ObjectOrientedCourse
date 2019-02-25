#ifndef TELEMENT_H
#define TELEMENT_H

#include <sstream>
#include "catch.hpp"
#include "valuation.h"
#include "element.h"

/**
 * @file telement.h
 * @version 3.0
 * @brief Declaration of TElement
 * @author Niko Lehto
 */

template <class T>
class TElement;

using IntElement = TElement<int>;
using VariableElement = TElement<char>;

template <class T>
class TElement : public Element
{
private:
	T telement;

public:
	TElement();
    TElement(const std::string& number);
	TElement(int v);
	TElement(char v);
	//TElement(char v);
	TElement(const TElement& i);
	~TElement();

	virtual int evaluate(const Valuation& v) const;
	virtual std::shared_ptr<Element> clone() const;
	virtual std::string toString() const;
	virtual bool operator==(const Element& i) const;
    virtual bool isEqual(const Element& i) const;

	T getVal() const;
	void setVal(T v);

	bool isEqual(const TElement& i) const;
	bool operator==(const TElement& i) const;

	IntElement& operator+=(const IntElement& i);
	IntElement& operator-=(const IntElement& i);
	IntElement& operator*=(const IntElement& i);

	friend IntElement operator+(const IntElement& a, const IntElement& b);
	friend IntElement operator-(const IntElement& a, const IntElement& b);
	friend IntElement operator*(const IntElement& a, const IntElement& b);
	friend std::ostream& operator<<(std::ostream& o, const VariableElement& v);
	friend std::ostream& operator<<(std::ostream& o, const IntElement& v);
};
#endif
