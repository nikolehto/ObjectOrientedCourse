#ifndef INTELEMENT_H
#define INTELEMENT_H

#include <sstream>
#include "catch.hpp"

/**
 * @file intelement.h
 * @version 1.0
 * @brief Declaration of IntElement
 * @author Niko Lehto
 */

class IntElement
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
	std::shared_ptr<IntElement> clone() const;
	void setVal(int v);


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
