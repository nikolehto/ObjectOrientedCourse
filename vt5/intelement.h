#ifndef INTELEMENT_H
#define INTELEMENT_H

#include <sstream>
#include "catch.hpp"
#include "valuation.h"
#include "element.h"

/**
 * @file intelement.h
 * @version 2.5
 * @brief Declaration of IntElement
 * @author Niko Lehto
 */
class IntElement : public Element
{
private:
	int intelement;

public:
	IntElement();
    IntElement(const std::string& number);
	IntElement(int v);
	IntElement(const IntElement& i);
	~IntElement();
	int getVal() const;

	void setVal(int v);
	virtual int evaluate(const Valuation& v) const;
	virtual std::shared_ptr<Element> clone() const;
	virtual std::string toString() const;

	IntElement& operator+=(const IntElement& i);
	IntElement& operator-=(const IntElement& i);
	IntElement& operator*=(const IntElement& i);
	bool operator==(const IntElement& i) const;

	friend IntElement operator+(const IntElement& a, const IntElement& b);
	friend IntElement operator-(const IntElement& a, const IntElement& b);
	friend IntElement operator*(const IntElement& a, const IntElement& b);
	friend std::ostream& operator<<(std::ostream& o, const IntElement& v);
};
#endif
