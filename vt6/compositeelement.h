#ifndef COMPOSITEELEMENT_H
#define COMPOSITEELEMENT_H

#include <sstream>
#include "catch.hpp"
#include "valuation.h"
#include "element.h"

/**
 * @file CompositeElement.h
 * @version 2.5
 * @brief Declaration of CompositeElement
 * @author Niko Lehto
 */

class CompositeElement : public Element
{
private:
	std::shared_ptr<Element> opmd1, opmd2;
    std::function<int(int,int)> op_fun;
    char op_ch;

public:
	CompositeElement(const Element& e1, const Element& e2, const std::function<int(int,int)>& op, char opc);
	CompositeElement(const CompositeElement& e);
	~CompositeElement();

	CompositeElement& operator=(const CompositeElement& m);
    bool operator==(const CompositeElement& e) const;

	virtual std::shared_ptr<Element> clone() const;
	virtual std::string toString() const;
	virtual int evaluate(const Valuation& v) const;
	virtual bool operator==(const Element& e) const;

	friend std::ostream& operator<<(std::ostream& o, const CompositeElement& v);
};
#endif
