#ifndef ELEMENT_H
#define ELEMENT_H

#include <sstream>
#include "catch.hpp"
#include "valuation.h"

/**
 * @file element.h
 * @version 3.0
 * @brief Declaration of Element
 * @author Niko Lehto
 */

class Element
{
public:
    virtual ~Element() {}

    virtual std::string toString() const = 0;
    virtual std::shared_ptr<Element> clone() const = 0;
    virtual int evaluate(const Valuation&) const = 0;

    // differs from specification:
    // used member function since matrices also uses similar method
    // does not affect anything
    virtual bool operator==(const Element& e) const = 0;

    friend std::ostream& operator<<(std::ostream& o, const Element& v);

    // spec style bool operator
    // friend bool operator==(const Element& e1, const Element& e2);
};
#endif
