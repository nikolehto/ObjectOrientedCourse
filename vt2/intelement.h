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
	IntElement(int v);
	IntElement(const IntElement& i);
	~IntElement();
	int getVal() const;
	void setVal(int v);
	
	IntElement& operator+=(const IntElement& i);
	IntElement& operator-=(const IntElement& i);
	IntElement& operator*=(const IntElement& i);
	friend bool operator==(const IntElement& a, const IntElement& b);
	friend IntElement operator+(const IntElement& a, const IntElement& b);
	friend IntElement operator-(const IntElement& a, const IntElement& b);
	friend IntElement operator*(const IntElement& a, const IntElement& b);
	friend std::ostream& operator<<(std::ostream& o, const IntElement& v);
};
#endif