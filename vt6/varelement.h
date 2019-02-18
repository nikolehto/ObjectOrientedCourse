#ifndef VariableElement_H
#define VariableElement_H

#include <sstream>
#include "catch.hpp"
#include "valuation.h"
#include "element.h"

/**
 * @file varelement.h
 * @version 2.5
 * @brief Declaration of VariableElement
 * @author Niko Lehto
 */

class VariableElement : public Element
{
private:
	char var;

public:
	VariableElement();
    VariableElement(const std::string& number);
	VariableElement(char v);
	VariableElement(const VariableElement& i);
	~VariableElement();

	virtual int evaluate(const Valuation& v) const;
	virtual std::shared_ptr<Element> clone() const;
	virtual std::string toString() const;
	virtual bool operator==(const Element& v) const;

    char getVal() const;
	void setVal(char v);
	bool operator==(const VariableElement& v) const;


	friend std::ostream& operator<<(std::ostream& o, const VariableElement& v);
};
#endif
