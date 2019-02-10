#include "catch.hpp"
#include "intelement.h"

/**
 *  @file intelement.cpp
 *  @brief Implementation of Element
 *  */

/**
 *  @class Element
 *  @version 3.0
 *  @brief Interface for Matrix element
 *  @author Niko Lehto
 *  */


/**
 *  \brief Default destructor
 * */
IntElement::~IntElement() = default;

/**
 *  \brief Getter method
 *  \return int value of IntElement
 */
int IntElement::getVal() const
{
	return intelement;
}

/**
 *  \brief Setter method
 *  \param [in] v int value for IntElement
 */
void IntElement::setVal(int v)
{
	intelement = v;
}

/**
 * \brief returns the pointer to a copy of this using smart pointer
 * \return shared_ptr containing value of intelement
 */
std::shared_ptr<IntElement> IntElement::clone() const
{
    return std::shared_ptr<IntElement>(new IntElement(intelement));
}

/**
 *  \brief Addition assignment. Performs addition by adding right-hand side into left-hand side of equation
 *  \param [in] i const IntElement@ value to be added
 *  \return Reference to left-hand side IntElement object added by i
 */
IntElement& IntElement::operator+=(const IntElement& i)
{
	intelement = intelement + i.getVal();
	return *this;
}

/**
 *  \brief Substraction assignment. Performs substraction by substracting right-hand side into left-hand side of equation
 *  \param [in] i const IntElement@ value to be substracted
 *  \return Reference to left-hand side IntElement object substracted by i
 */
IntElement& IntElement::operator-=(const IntElement& i)
{
	intelement = intelement - i.getVal();
	return *this;
}

/**
 *  \brief Multiplication assignment. Performs multiplication by multiplying right-hand side into left-hand side of equation
 *  \param [in] i const IntElement@ value to be multiplied
 *  \return Reference to left-hand side IntElement object multiplied by i
 */
IntElement& IntElement::operator*=(const IntElement& i)
{
	intelement = intelement * i.getVal();
	return *this;
}

/**
 *  \brief Addition. Performs addition by adding a and b
 *  \param [in] a const IntElement@ value a
 *  \param [in] b const IntElement@ value b
 *  \return Sum of a and b
 */
IntElement operator+(const IntElement& a, const IntElement& b)
{
	IntElement t_a(a);
	t_a += b;
	return t_a;
}

/**
 *  \brief Substraction. Performs substraction by substracting a and b
 *  \param [in] a const IntElement@ value a
 *  \param [in] b const IntElement@ value b
 *  \return Substraction of a and b
 */
IntElement operator-(const IntElement& a, const IntElement& b)
{
	IntElement t_a(a);
	t_a -= b;
	return t_a;
}

/**
 *  \brief Multiplication. Performs multiplication by multiplying a and b
 *  \param [in] a const IntElement@ value a
 *  \param [in] b const IntElement@ value b
 *  \return Multiplication of a and b
 */
IntElement operator*(const IntElement& a, const IntElement& b)
{
	IntElement t_a(a);
	t_a *= b;
	return t_a;
}

/**
 *  \brief Write object to stream
 *  \param [in,out] o std::ostream& output stream
 *  \param [in] v const IntElement& value to be streamed
 *  \return std::ostream reference appended by object
 */
std::ostream& operator<<(std::ostream& o, const IntElement& v)
{
	o << std::to_string(v.intelement);
	return o;
}

/**
 *  \brief Overload of equal comparison
 *  \param [in] i const IntElement& value
 *  \return true if this and i are identical
 */
bool IntElement::operator==(const IntElement& i) const
{
	return this->getVal() == i.getVal();
}
