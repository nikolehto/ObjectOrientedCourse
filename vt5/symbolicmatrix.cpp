#include "symbolicmatrix.h"
#include "catch.hpp"

/**
 *  @file symbolicmatrix.cpp
 *  @brief Implementation of SymbolicSquareMatrix
 *  */

 /**
 *  @class SymbolicSquareMatrix
 *  @version 2.5
 *  @brief Implementation for nxn dimensional SymbolicSquareMatrix
 *  @author Niko Lehto
 *  */

/**
 *  \brief Empty constructor
 */
SymbolicSquareMatrix::SymbolicSquareMatrix() = default;

/**
 *  \brief Constructs a matrix from string of the form [[a<SUB>11</SUB>,...,a<SUB>1n</SUB>]...[a<SUB>n1</SUB>,...,a<SUB>nn</SUB>]]
 *  \param [in] s const std::string% string presentation of matrix in form '[[a<SUB>11</SUB>,...,<SUB>a1n</SUB>]...[a<SUB>n1</SUB>,...,<SUB>ann</SUB>]]' where in element: e<SUB>ij</SUB>, <SUB>i</SUB> refers to row and <SUB>j</SUB> refers to column
*/
SymbolicSquareMatrix::SymbolicSquareMatrix(const std::string& s)
{
    fromString(s);
    // set n and elements
}

/**
 *  \brief Clone constructor
 *  \param [in] m const SymbolicSquareMatrix& object to clone
 */
SymbolicSquareMatrix::SymbolicSquareMatrix(const SymbolicSquareMatrix& m)
{
    *this = m;
}

/**
 *  \brief Move constructor
 *  \param [in] m const SymbolicSquareMatrix&& object contain values
 */
SymbolicSquareMatrix::SymbolicSquareMatrix(SymbolicSquareMatrix&& m)
{
    *this = std::move(m);
}


/**
 *  \brief Default destructor
 */
SymbolicSquareMatrix::~SymbolicSquareMatrix() = default;

/**
 *  \brief Saves a matrix from string of the form [[a<SUB>11</SUB>,...,a<SUB>1n</SUB>]...[a<SUB>n1</SUB>,...,a<SUB>nn</SUB>]]
 *  \param [in] matrix const std::string% string presentation of matrix in form '[[a<SUB>11</SUB>,...,<SUB>a1n</SUB>]...[a<SUB>n1</SUB>,...,<SUB>ann</SUB>]]' where in element: e<SUB>ij</SUB>, <SUB>i</SUB> refers to row and <SUB>j</SUB> refers to column
*/
void SymbolicSquareMatrix::fromString(const std::string& matrix)
{
	size_t len = matrix.length();

	if (len < 5) // 5 characters is shortest possible square matrix i.e. [[1]]
	{
		throw std::invalid_argument("Too few characters to be a Matrix");
	}

	if (matrix.substr(0,2) != "[[") // require start
	{
		throw std::invalid_argument("Should start \"[[\", Started \"" + matrix.substr(0,2) + "\" instead");
	}

	if (matrix.substr(len - 2, 2) != "]]") // require end
	{
        throw std::invalid_argument("Should end \"]]\", Ended \"" + matrix.substr(len - 2, 2) + "\" instead");
	}

	size_t row_start_idx, row_end_idx;
	row_start_idx = 2;
	bool matrix_ends = false;

	size_t row_dimension = 0;
	size_t column_dimension = 0;
	while(!matrix_ends)
	{
        std::vector<std::shared_ptr<Element>> temp;
		// find end of new row
		row_end_idx = matrix.find("][", row_start_idx);

		// no new row?
		if (row_end_idx == std::string::npos)
		{
			// Found matrix end?
			row_end_idx = matrix.find("]]", row_start_idx);
			if (row_end_idx == len - 2)
			{
				matrix_ends = true;

				// matrix will end, but lets check the last row
			}
			// No new row and not ended / end too soon -> invalid
			else
			{
				throw std::invalid_argument("Ends too soon, row \"][\" expected");
			}
		}

		bool rowends = false;
		size_t elem_start_idx = row_start_idx;
		size_t elem_end_idx;
		size_t current_column_dimension = 0;
		while (!rowends)
		{
			// find end of element ! Must be before end of row
			elem_end_idx = matrix.find_first_of(",", elem_start_idx);

			// no new element?
			if (elem_end_idx > row_end_idx)
			{
				elem_end_idx = row_end_idx; // assume we found last element
				rowends = true;
			}

            const std::string token(matrix.substr(elem_start_idx, elem_end_idx - elem_start_idx));
            std::shared_ptr<Element> elem_ptr = nullptr;
            try
            {// try initialize as IntElement
                elem_ptr = std::make_shared<IntElement>(token);
            }
            catch (const std::invalid_argument nn)
            {
                // if throws, try initialize as VariableElement - do not catch
                elem_ptr = std::make_shared<VariableElement>(token);
            }

			temp.push_back(std::move(elem_ptr));
			current_column_dimension++;

			elem_start_idx = elem_end_idx + 1;
		}

        row_dimension++;
		if (column_dimension == 0 || column_dimension == current_column_dimension)
		{
			column_dimension = current_column_dimension;
		}
		else
		{
		    throw std::invalid_argument("All columns did not have same dimension ");
		}
		row_start_idx = row_end_idx + 2;
		this->elements.push_back(temp);
	}

	if (row_dimension != column_dimension)
	{
		throw std::invalid_argument("Not a square matrix. Found: " + std::to_string(row_dimension) + " X " + std::to_string(column_dimension) + "matrix");
	}

	this->n = static_cast<int>(row_dimension);
}

/**
 *  \brief Make transpose of the matrix
 * \return new matrix transposed
 */
SymbolicSquareMatrix SymbolicSquareMatrix::transpose() const
{
    size_t t_n = this->elements.size();
    SymbolicSquareMatrix transpose(*this); // probably the quickest way - only for n*n

    for(size_t x = 0; x < t_n; x++)
    {
        for(size_t y = 0; y < t_n; y++)
        {
            transpose.elements.at(y).at(x) = this->elements.at(x).at(y)->clone();
        }
    }

    return transpose;
}

/**
 *  \brief Write object to stream in form of [[<a<SUB>11</SUB>>,...,<a<SUB>1n</SUB>>]...[<a<SUB>n1</SUB>>,...,<a<SUB>nn</SUB>>]]
 *		where i<SUB>ij</SUB> : <SUB>i</SUB> refers to row and <SUB>j</SUB> refers to column
 *  \param [out] stream std::ostream& output stream
 */
void SymbolicSquareMatrix::print
    (std::ostream& stream) const
{
	stream << *this;
	return;
}

/**
 *  \brief Write object to string in form of [[<i<SUB>11</SUB>>,<i<SUB>12</SUB>>][<i<SUB>21</SUB>>,<i<SUB>22</SUB>>]]
*		where i<SUB>ij</SUB> : <SUB>i</SUB> refers to row and <SUB>j</SUB> refers to column
 *  \return std::string object as a string
 *  */
std::string SymbolicSquareMatrix::toString() const
{
	std::stringstream result;
	result << *this;
	return result.str();
}

/**
 *  \brief Assignment
 *  \param [in] m const SymbolicSquareMatrix&
 *  \return Reference to copied right-hand side matrix
 */
SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(const SymbolicSquareMatrix& m)
{
    // self assignment is dangerous since this -> clear()
    if(this == &m)
    {
        return *this;
    }

    this->elements.clear();
    this->n = m.n;

    for(auto& row : m.elements)
    {
        std::vector<std::shared_ptr<Element>> temp;
        for(auto& elem : row)
        {
            temp.push_back(elem->clone());
        }
        this->elements.push_back(temp);
    }
    return *this;
}

/**
 *  \brief Assignment
 *  \param [in] m SymbolicSquareMatrix&&
 *  \return Reference to original right-hand side matrix
 */
SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(SymbolicSquareMatrix&& m)
{
    if(this != &m)
    {
        this->elements.clear();
        this->elements.swap(m.elements);
        this->n = m.n;
    }
    return *this;
}

/**
 *  \brief Write object to stream in form of [[<i<SUB>11</SUB>>,<i<SUB>12</SUB>>][<i<SUB>21</SUB>>,<i<SUB>22</SUB>>]]
 *  \param [in,out] stream std::ostream&
 *  \param [in] m const SymbolicSquareMatrix& m
 *  \return stream appended by object
 */
std::ostream& operator<<(std::ostream& stream, const SymbolicSquareMatrix& m)
{
    if(m.elements.size() == 0)
    {
        return stream;
    }
	stream << "[";
    for(auto& element : m.elements)
    {
        stream << "[";
        for(size_t ind = 0; ind < element.size(); ind++)
        {
            if(ind != element.size() - 1)
            {
                stream << element.at(ind)->toString() << ",";
            }
            else
            {
                stream << element.at(ind)->toString();
                //   stream << *std::static_pointer_cast<VariableElement>(element.at(ind));
            }
        }
        stream << "]";
    }
    stream << "]";

    return stream;
}

/**
 *  \brief Evaluate symbolic matrix with Valuation
 *  \param [in] v const Valuation& contains symbol values
 *  \return ConcreteSquareMatrix containing corresponding values
 */
ConcreteSquareMatrix SymbolicSquareMatrix::evaluate(const Valuation& v) const
{
    ConcreteSquareMatrix m;
    m.n = this->n;

    for(size_t i = 0; i < this->elements.size(); i++)
    {
        std::vector<std::shared_ptr<IntElement>> temp;

		for(size_t j = 0; j < this->elements.size(); j++)
		{
		    temp.push_back(std::shared_ptr<IntElement>( new IntElement(this->elements.at(i).at(j)->evaluate(v))));
		}
		m.elements.push_back(temp);
	}

    return m;
}

/**
 *  \brief Overload of equal comparison
 *  \param [in] m const SymbolicSquareMatrix& value for comparison
 *  \return bool true if this and m are identical
 */
bool SymbolicSquareMatrix::operator==(const SymbolicSquareMatrix& m) const
{
    // std::cout << "\n" << this->n << m.n;
    // std::cout << "\n" << this->elements.size() << m.elements.size();
    if(this->n != m.n || this->elements.size() != m.elements.size())
    {
        return false;
    }

    size_t t_n = this->elements.size();

    for(size_t in = 0; in < t_n; in++)
    {
        for(size_t j = 0; j < t_n; j++)
        {
            if(*std::static_pointer_cast<VariableElement>(this->elements.at(in).at(j)) == *std::static_pointer_cast<VariableElement>(m.elements.at(in).at(j)))
            {
                // std::cout << "\n" << this->elements.at(in).at(j).use_count() << " " << m.elements.at(in).at(j).use_count();
                // std::cout << "\n" << this->elements.at(in).at(j) << " " << m.elements.at(in).at(j);
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}
