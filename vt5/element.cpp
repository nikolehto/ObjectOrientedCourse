#include "catch.hpp"
#include "element.h"

/**
 *  @file element.cpp
 *  @brief Implementation of Element
 *  */

/**
 *  @class Element
 *  @version 3.0
 *  @brief Interface for Matrix element
 *  @author Niko Lehto
 *  */

 std::ostream& operator<<(std::ostream& o, const Element& v)
 {
    o << v.toString();
    return o;
 }
