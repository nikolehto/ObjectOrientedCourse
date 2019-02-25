#include "catch.hpp"
#include "telement.h"

/**
 *  @file telement.cpp
 *  @brief Implementation of TElement
 *  */

/**
 *  @class TElement
 *  @version 2.5
 *  @brief Int-type value holder for Matrix
 *  @author Niko Lehto
 *  */

/**
 *  \brief Empty constructor
 * */
template<class T>
TElement<T>::TElement()
{
	telement = 0;
}

/**
 *  \brief Parameterized constructor
 *  \param [in] v int initial value for TElement
 * */
 /*
template<class T>
TElement<T>::TElement(T v)
{
	telement = v;
}
*/
/**
 *  \brief Parameterized constructor
 *  \param [in] v int initial value for TElement
 * */

template<>
IntElement::TElement(int v)
{
	telement = v;
}

/**
 *  \brief Parameterized constructor
 *  \param [in] v char initial value for TElement
 * */

template<>
VariableElement::TElement(char v)
{
	telement = v;
}


/**
 *  \brief Clone constructor
 *  \param [in] i const TElement& initial value for TElement
 * */
template<class T>
TElement<T>::TElement(const TElement& i)
{
	telement = i.getVal();
}

/**
 *  \brief String constructor
 *  \param [in] number const std::string& number as string
 * */
template<class T>
TElement<T>::TElement(const std::string& number)
{
	size_t idx = 0;
    T value;

	try
	{
	    // option 1 looks like integer
		value = std::stoi(number, &idx);
	}
	catch (const std::invalid_argument nn)
	{
	    // option 2 not integer and length is zero - return after checks and sets
        if (number.length() != 1)
        {
            throw std::invalid_argument( "Element contains zero or multiple chars, one char or integer required" );
        }

        value = number[0];
        this->telement = value;
        return;
	}

	// option 1:
	// check whether whole text is valid integer, otherwise it is an error
	if (idx != number.length())
	{
		throw std::invalid_argument( "Element not an integer, or it contains character" );
	}

	this->telement = value;
}

/**
 *  \brief Default destructor
 * */
template<class T>
TElement<T>::~TElement() = default;

/**
 *  \brief Getter method
 *  \return T value of TElement
 */
template<class T>
T TElement<T>::getVal() const
{
	return telement;
}

/**
* \brief Evaluate variable with Valuation mapping v
* \param [in] v const Valuation& contains symbol values
* \return int value or corresponding value
*/
/*
template<class T>
int TElement<T>::evaluate(const Valuation& v) const
{
    if(std::is_same<T,int>::value)
    {
        return telement;
    }
    else if (v.count(telement))
    {
        return v.at(telement);
    }
    else
    {
        throw std::invalid_argument( "Symbolic variable cannot be found from given Valuation v" );
    }
}
*/

template<>
int VariableElement::evaluate(const Valuation& v) const
{
    if (v.count(telement))
    {
        return v.at(telement);
    }
    else
    {
        throw std::invalid_argument( "Symbolic variable cannot be found from given Valuation v" );
    }
}

template<>
int IntElement::evaluate(const Valuation& v) const
{
    return telement;
}

/**
 *  \brief Write element to string
 *  \return std::string object as a string
 *  */
template<class T>
std::string TElement<T>::toString() const
{
	std::stringstream result;
	result << *this;
	return result.str();
}


/**
 *  \brief Setter method
 *  \param [in] v int value for TElement
 */
template<class T>
void TElement<T>::setVal(T v)
{
	telement = v;
}

/**
 * \brief returns the pointer to a copy of this using smart pointer
 * \return shared_ptr containing value of telement
 */
template<class T>
std::shared_ptr<Element> TElement<T>::clone() const
{
    return std::shared_ptr<Element>(new TElement(*this));
}

/**
 *  \brief Addition assignment. Performs addition by adding right-hand side into left-hand side of equation
 *  \param [in] i const IntElement& value to be added
 *  \return Reference to left-hand side IntElement object added by i
 */
template<>
IntElement& IntElement::operator+=(const IntElement& i)
{
	telement = telement + i.getVal();
	return *this;
}

/**
 *  \brief Substraction assignment. Performs substraction by substracting right-hand side into left-hand side of equation
 *  \param [in] i const IntElement& value to be substracted
 *  \return Reference to left-hand side IntElement object substracted by i
 */
template<>
IntElement& IntElement::operator-=(const IntElement& i)
{
	telement = telement - i.getVal();
	return *this;
}

/**
 *  \brief Multiplication assignment. Performs multiplication by multiplying right-hand side into left-hand side of equation
 *  \param [in] i const IntElement& value to be multiplied
 *  \return Reference to left-hand side IntElement object multiplied by i
 */
template<>
IntElement& IntElement::operator*=(const IntElement& i)
{
	telement = telement * i.getVal();
	return *this;
}

/**
 *  \brief Addition. Performs addition by adding a and b
 *  \param [in] a const IntElement& value a
 *  \param [in] b const IntElement& value b
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
 *  \param [in] a const IntElement& value a
 *  \param [in] b const IntElement& value b
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
 *  \param [in] a const IntElement& value a
 *  \param [in] b const IntElement& value b
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
 *  \param [in] v const TElement& value to be streamed
 *  \return std::ostream reference appended by object
 */
std::ostream& operator<<(std::ostream& o, const VariableElement& v)
{
	o << v.telement;
	return o;
}

/**
 *  \brief Write object to stream
 *  \param [in,out] o std::ostream& output stream
 *  \param [in] v const TElement& value to be streamed
 *  \return std::ostream reference appended by object
 */
std::ostream& operator<<(std::ostream& o, const IntElement& v)
{
	o << std::to_string(v.telement);
	return o;
}

/**
 *  \brief Equal comparison
 *  \param [in] i const TElement& value
 *  \return true if this and i are identical
 */
template<class T>
bool TElement<T>::operator==(const TElement& i) const
{
	return this->getVal() == i.getVal();
}

/**
 *  \brief Overload of equal comparison
 *  \param [in] i const Element& value
 *  \return true if this and i are identical
 */
template<class T>
bool TElement<T>::operator==(const Element& i) const
{
    std::shared_ptr<TElement> i_e;
    if(i_e = std::dynamic_pointer_cast<TElement>(i.clone()))
    {
        return *this == *i_e;
    }
    else
    {
        return false;
    }
}

template class TElement<int>;
template class TElement<char>;
