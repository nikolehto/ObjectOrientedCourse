#include "catch.hpp"
#include "varelement.h"

/**
 *  @file varelement.cpp
 *  @brief Implementation of VariableElement
 *  */

/**
 *  @class VariableElement
 *  @version 3.0
 *  @brief Symbolic value holder for Matrix
 *  @author Niko Lehto
 *  */

/**
 *  \brief Empty constructor
 * */
VariableElement::VariableElement()
{
	var = 0;
}

/**
 *  \brief Parameterized constructor
 *  \param [in] v char initial value for VariableElement
 * */
VariableElement::VariableElement(char v)
{
	var = v;
}

/**
 *  \brief Clone constructor
 *  \param [in] i const VariableElement& initial value for VariableElement
 * */
VariableElement::VariableElement(const VariableElement& i)
{
	var = i.getVal();
}

/**
 *  \brief String constructor
 *  \param [in] symbol const std::string& symbol as string
 * */
VariableElement::VariableElement(const std::string& symbol)
{

    // check whether text contains one char otherwise it is an error
	if (symbol.length() != 1)
	{
		throw std::invalid_argument( "Element empty or not a char" );
	}

	var = symbol[0];
}

/**
 *  \brief Default destructor
 * */
VariableElement::~VariableElement() = default;

/**
 *  \brief Getter method
 *  \return char value of VariableElement
 */
char VariableElement::getVal() const
{
	return var;
}

/**
 *  \brief Setter method
 *  \param [in] v char value for VariableElement
 */
void VariableElement::setVal(char v)
{
	var = v;
}

int VariableElement::evaluate(const Valuation& v) const
{
    if (v.count(var))
    {
        return v.at(var);
    }
    else
    {
        throw std::invalid_argument( "Symbolic variable cannot be found from given Valuation v" );
    }
}

/**
 *  \brief Write element to string
 *  \return std::string object as a string
 *  */
std::string VariableElement::toString() const
{
	std::stringstream result;
	result << *this;
	return result.str();
}

/**
 * \brief returns the pointer to a copy of var
 * \return shared_ptr containing value of VariableElement
 */
std::shared_ptr<Element> VariableElement::clone() const
{
    return std::shared_ptr<Element>(new VariableElement(*this));
}

/**
 *  \brief Write object to stream
 *  \param [in,out] o std::ostream& output stream
 *  \param [in] v const VariableElement& value to be streamed
 *  \return std::ostream reference appended by object
 */
std::ostream& operator<<(std::ostream& o, const VariableElement& v)
{
	o << std::to_string(v.var);
	return o;
}

/**
 *  \brief Overload of equal comparison
 *  \param [in] i const VariableElement& value
 *  \return true if this and i are identical
 */
bool VariableElement::operator==(const VariableElement& i) const
{
	return this->getVal() == i.getVal();
}
