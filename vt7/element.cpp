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

/**
 *  \brief Write object to stream, calls overloaded toString function
 *  \param [in,out] o std::ostream& output stream
 *  \param [in] v const Element& value to be streamed
 *  \return std::ostream reference appended by object
 */
std::ostream& operator<<(std::ostream& o, const Element& v)
{
    o << v.toString();
    return o;
}

/**
 *  \brief Equal comparison calls overloaded isEqual function
 *  \param [in] e const Element& value
 *  \return true if this and e are identical
 */
bool Element::operator==(const Element& e) const
{
    return this->isEqual(e);
}


