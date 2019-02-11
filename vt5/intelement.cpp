#include "catch.hpp"
#include "intelement.h"

/**
 *  @file intelement.cpp
 *  @brief Implementation of IntElement
 *  */

/**
 *  @class IntElement
 *  @version 2.5
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
 *  \brief String constructor
 *  \param [in] number const std::string& number as string
 * */
IntElement::IntElement(const std::string& number)
{
	size_t idx = 0;
    int value;

	try
	{
		value = std::stoi(number, &idx);
	}
	catch (const std::invalid_argument nn)
	{
		throw std::invalid_argument( "Element starts with invalid character" );
	}

	// check whether whole text is valid integer, otherwise it is an error
	if (idx != number.length())
	{
		throw std::invalid_argument( "Element not an integer, or it contains character" );
	}

	this->intelement = value;
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

int IntElement::evaluate(const Valuation& v) const
{
    return this->getVal();
}

/**
 *  \brief Write element to string
 *  \return std::string object as a string
 *  */
std::string IntElement::toString() const
{
	std::stringstream result;
	result << *this;
	return result.str();
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
std::shared_ptr<Element> IntElement::clone() const
{
    return std::shared_ptr<Element>(new IntElement(*this));
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
