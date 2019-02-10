#ifndef VariableElement_H
#define VariableElement_H

#include <sstream>
#include "catch.hpp"
#include "valuation.h"
#include "element.h"

/**
 * @file VariableElement.h
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

	int evaluate(const Valuation& v) const override;
	std::shared_ptr<Element> clone() const override;
	std::string toString() const override;

    char getVal() const;
	void setVal(char v);

	bool operator==(const VariableElement& i) const;

	friend std::ostream& operator<<(std::ostream& o, const VariableElement& v);
};
#endif
