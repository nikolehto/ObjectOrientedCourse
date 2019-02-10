#ifndef VariableElement_H
#define VariableElement_H

#include <sstream>
#include "catch.hpp"

/**
 * @file VariableElement.h
 * @version 2.5
 * @brief Declaration of VariableElement
 * @author Niko Lehto
 */

class VariableElement
{
private:
	int VariableElement;

public:
	VariableElement();
    VariableElement(const std::string& number);
	VariableElement(int v);
	VariableElement(const VariableElement& i);
	~VariableElement();
	int getVal() const;
	std::shared_ptr<VariableElement> clone() const;
	void setVal(int v);


	VariableElement& operator+=(const VariableElement& i);
	VariableElement& operator-=(const VariableElement& i);
	VariableElement& operator*=(const VariableElement& i);
	bool operator==(const VariableElement& i) const;

	friend VariableElement operator+(const VariableElement& a, const VariableElement& b);
	friend VariableElement operator-(const VariableElement& a, const VariableElement& b);
	friend VariableElement operator*(const VariableElement& a, const VariableElement& b);
	friend std::ostream& operator<<(std::ostream& o, const VariableElement& v);
};
#endif
