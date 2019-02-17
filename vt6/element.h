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
    virtual bool operator==(const Element& e) const = 0;

    friend std::ostream& operator<<(std::ostream& o, const Element& v);
};
#endif
