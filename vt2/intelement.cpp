#include "catch.hpp"
#include "intelement.h"

/**
 *  @file intelement.cpp
 *  @brief Implementation of IntElement
 *  */
/**
 *  @class IntElement
 *  @version 1.0
 *  @brief Int-type value holder for Matrix
 *  @author Niko Lehto
 *  */

/**
 *  \brief Empty constructor
 * */
IntElement::IntElement()
{
	intelement = 0;
}

/**
 *  \brief Parameterized constructor
 *  \param [in] v int initial value for IntElement
 * */
IntElement::IntElement(int v)
{
	intelement = v;
}

/**
 *  \brief Clone constructor
 *  \param [in] i const IntElement& initial value for IntElement
 * */
IntElement::IntElement(const IntElement& i)
{
	intelement = i.getVal();
}

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
 *  \brief Brief Setter method
 *  \param [in] v int value for IntElement
 */
void IntElement::setVal(int v)
{
	intelement = v;
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
 *  \param [in] a const IntElement& value
 *  \param [in] b const IntElement& value for comparison
 *  \return true if a == b
 */
bool operator==(const IntElement& a, const IntElement& b)
{
	return a.getVal() == b.getVal();
}