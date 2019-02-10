#include "catch.hpp"
#include "VariableElement.h"

/**
 *  @file VariableElement.cpp
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
	VariableElement = 0;
}

/**
 *  \brief Parameterized constructor
 *  \param [in] v int initial value for VariableElement
 * */
VariableElement::VariableElement(int v)
{
	VariableElement = v;
}

/**
 *  \brief Clone constructor
 *  \param [in] i const VariableElement& initial value for VariableElement
 * */
VariableElement::VariableElement(const VariableElement& i)
{
	VariableElement = i.getVal();
}

/**
 *  \brief String constructor
 *  \param [in] number const std::string& number as string
 * */
VariableElement::VariableElement(const std::string& number)
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

	this->VariableElement = value;
}

/**
 *  \brief Default destructor
 * */
VariableElement::~VariableElement() = default;

/**
 *  \brief Getter method
 *  \return int value of VariableElement
 */
int VariableElement::getVal() const
{
	return VariableElement;
}

/**
 *  \brief Setter method
 *  \param [in] v int value for VariableElement
 */
void VariableElement::setVal(int v)
{
	VariableElement = v;
}

/**
 * \brief returns the pointer to a copy of this using smart pointer
 * \return shared_ptr containing value of VariableElement
 */
std::shared_ptr<VariableElement> VariableElement::clone() const
{
    return std::shared_ptr<VariableElement>(new VariableElement(VariableElement));
}

/**
 *  \brief Addition assignment. Performs addition by adding right-hand side into left-hand side of equation
 *  \param [in] i const VariableElement@ value to be added
 *  \return Reference to left-hand side VariableElement object added by i
 */
VariableElement& VariableElement::operator+=(const VariableElement& i)
{
	VariableElement = VariableElement + i.getVal();
	return *this;
}

/**
 *  \brief Substraction assignment. Performs substraction by substracting right-hand side into left-hand side of equation
 *  \param [in] i const VariableElement@ value to be substracted
 *  \return Reference to left-hand side VariableElement object substracted by i
 */
VariableElement& VariableElement::operator-=(const VariableElement& i)
{
	VariableElement = VariableElement - i.getVal();
	return *this;
}

/**
 *  \brief Multiplication assignment. Performs multiplication by multiplying right-hand side into left-hand side of equation
 *  \param [in] i const VariableElement@ value to be multiplied
 *  \return Reference to left-hand side VariableElement object multiplied by i
 */
VariableElement& VariableElement::operator*=(const VariableElement& i)
{
	VariableElement = VariableElement * i.getVal();
	return *this;
}

/**
 *  \brief Addition. Performs addition by adding a and b
 *  \param [in] a const VariableElement@ value a
 *  \param [in] b const VariableElement@ value b
 *  \return Sum of a and b
 */
VariableElement operator+(const VariableElement& a, const VariableElement& b)
{
	VariableElement t_a(a);
	t_a += b;
	return t_a;
}

/**
 *  \brief Substraction. Performs substraction by substracting a and b
 *  \param [in] a const VariableElement@ value a
 *  \param [in] b const VariableElement@ value b
 *  \return Substraction of a and b
 */
VariableElement operator-(const VariableElement& a, const VariableElement& b)
{
	VariableElement t_a(a);
	t_a -= b;
	return t_a;
}

/**
 *  \brief Multiplication. Performs multiplication by multiplying a and b
 *  \param [in] a const VariableElement@ value a
 *  \param [in] b const VariableElement@ value b
 *  \return Multiplication of a and b
 */
VariableElement operator*(const VariableElement& a, const VariableElement& b)
{
	VariableElement t_a(a);
	t_a *= b;
	return t_a;
}

/**
 *  \brief Write object to stream
 *  \param [in,out] o std::ostream& output stream
 *  \param [in] v const VariableElement& value to be streamed
 *  \return std::ostream reference appended by object
 */
std::ostream& operator<<(std::ostream& o, const VariableElement& v)
{
	o << std::to_string(v.VariableElement);
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
