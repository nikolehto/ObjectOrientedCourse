#include "squarematrix.h"
#include "catch.hpp"

/**
 *  @file squarematrix.cpp
 *  @class SquareMatrix
 *  @version 1.0
 *  @brief Implementation for 2x2 dimensional SquareMatrix 
 *  @author Niko Lehto
 *  */

/**
 *  \brief Empty constructor
 */
SquareMatrix::SquareMatrix()
{
	e11 = 0;
	e12 = 0;
	e21 = 0;
	e22 = 0;
}

/**
 *  \brief Parameterized constructor
 *  \param [in] i11 Element of matrix, format: e_{ij} where _{i} refers to row and _{j} refers to column
 *  \param [in] i12 Element of matrix, format: e_{ij} where _{i} refers to row and _{j} refers to column
 *  \param [in] i21 Element of matrix, format: e_{ij} where _{i} refers to row and _{j} refers to column
 *  \param [in] i22 Element of matrix, format: e_{ij} where _{i} refers to row and _{j} refers to column
*/
SquareMatrix::SquareMatrix(const IntElement& i11, const IntElement& i12, const IntElement& i21, const IntElement& i22)
{
	e11 = i11;
	e12 = i12;
	e21 = i21;
	e22 = i22;
} 

/**
 *  \brief Clone constructor
 *  \param [in] i SquareMatrix
 */
SquareMatrix::SquareMatrix(const SquareMatrix& i)
{
	this->e11 = i.e11;
	this->e12 = i.e12;
	this->e21 = i.e21;
	this->e22 = i.e22;
}

/**
 *  \brief Destructor
 */
SquareMatrix::~SquareMatrix() = default;

/**
 *  \brief Write object to stream in form of [[<i_{11}>,<i_{12}>][<i_{21}>,<i_{22}>]]
 *  \param [out] stream output stream
 */
void SquareMatrix::print
    (std::ostream & stream) const
{
	stream << *this;
	return;
}

/**
 *  \brief Write object to string in form of [[<i_{11}>,<i_{12}>][<i_{21}>,<i_{22}>]]
 *  \return string holding object
 *  */
std::string SquareMatrix::toString() const
{
	std::stringstream result;
	result << *this;
	return result.str();
}

/**
 *  \brief Addition assignment. Performs matrix addition by adding right-hand side into left-hand side of equation
 *  \param [in] SquareMatrix i
 *  \return Reference to left-hand side matrix added by i
 */
SquareMatrix& SquareMatrix::operator+=(const SquareMatrix& i)
{
	e11 += i.e11;
	e12 += i.e12;
	e21 += i.e21;
	e22 += i.e22;
	return *this;
}

 /**
 *  \brief Substraction assignment. Performs matrix substraction by substracting right-hand side from the left-hand side of equation
 *  \param [in] SquareMatrix i
 *  \return Reference to left-hand side matrix substracted by i
 */
SquareMatrix& SquareMatrix::operator-=(const SquareMatrix& i)
{
	e11 -= i.e11;
	e12 -= i.e12;
	e21 -= i.e21;
	e22 -= i.e22;
	return *this;
}

/**
 *  \brief Multiplication assignment. Performs matrix dot product by multiplying right-hand side into left-hand side of equation
 *  \param [in] SquareMatrix i
 *  \return Reference to left-hand side matrix multiplied by i
 */
SquareMatrix& SquareMatrix::operator*=(const SquareMatrix& i)
{
	SquareMatrix temp(*this);

	e11 = temp.e11 * i.e11 + temp.e12 * i.e21;
	e12 = temp.e11 * i.e12 + temp.e12 * i.e22;
	e21 = temp.e21 * i.e11 + temp.e22 * i.e21;
	e22 = temp.e21 * i.e12 + temp.e22 * i.e22;

	return *this;
}

/**
 *  \brief Addition. Performs matrix addition by adding a and b
 *  \param [in] SquareMatrix a
 *  \param [in] SquareMatrix b
 *  \return Addition of a and b
 */
SquareMatrix operator+(const SquareMatrix& a, const SquareMatrix& b)
{
	SquareMatrix t_a(a);
	t_a += b;
	return t_a;
}

/**
 *  \brief Substraction. Performs matrix substraction by substracting b from a
 *  \param [in] SquareMatrix a
 *  \param [in] SquareMatrix b
 *  \return Substraction of a and b
 */
SquareMatrix operator-(const SquareMatrix& a, const SquareMatrix& b)
{
	SquareMatrix t_a(a);
	t_a -= b;
	return t_a;
}

/**
 *  \brief Multiplication. Performs matrix dot-product by multiplying a and b
 *  \param [in] SquareMatrix a
 *  \param [in] SquareMatrix b
 *  \return Dot-product of a and b
 */
SquareMatrix operator*(const SquareMatrix& a, const SquareMatrix& b)
{
	SquareMatrix t_a(a);
	t_a *= b;
	return t_a;
}

/**
 *  \brief Write object to stream in form of [[<i_{11}>,<i_{12}>][<i_{21}>,<i_{22}>]]
 *  \param [in/out] stream
 *  \param [in] m 
 *  \return stream appended by object
 */
std::ostream& operator<<(std::ostream& stream, const SquareMatrix& m)
{
	stream << "[[" << m.e11 << "," << m.e12 << "][" << m.e21 << "," << m.e22 << "]]";
	return stream;
}

/**
 *  \brief Overload of equal comparison
 *  \param [in] a SquareMatrix a
 *  \param [in] b SquareMatrix b
 *  \return true if a == b
 */
bool operator==(const SquareMatrix& a, const SquareMatrix& b)
{
	return a.e11 == b.e11 && a.e12 == b.e12 && a.e21 == b.e21 && a.e22 == b.e22;
}