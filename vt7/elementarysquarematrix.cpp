#include "elementarysquarematrix.h"

/**
 *  @file elementarysquarematrix.cpp
 *  @brief Implementation of ElementarySquareMatrix
 *  */

 /**
 *  @class ElementarySquareMatrix
 *  @version 2.5
 *  @brief Implementation for nxn dimensional ElementarySquareMatrix
 *  @author Niko Lehto
 *  */

/**
 *  \brief Empty constructor
 */
template<typename T>
ElementarySquareMatrix<T>::ElementarySquareMatrix() = default;

/**
 *  \brief Constructs a matrix from string of the form [[a<SUB>11</SUB>,...,a<SUB>1n</SUB>]...[a<SUB>n1</SUB>,...,a<SUB>nn</SUB>]]
 *  \param [in] s const std::string& string presentation of matrix in form '[[a<SUB>11</SUB>,...,<SUB>a1n</SUB>]...[a<SUB>n1</SUB>,...,<SUB>ann</SUB>]]' where in element: e<SUB>ij</SUB>, <SUB>i</SUB> refers to row and <SUB>j</SUB> refers to column
*/
template<typename T>
ElementarySquareMatrix<T>::ElementarySquareMatrix(const std::string& s)
{
    fromString(s);
}

/**
 *  \brief Clone constructor
 *  \param [in] m const ElementarySquareMatrix& object to clone
 */
template<typename T>
ElementarySquareMatrix<T>::ElementarySquareMatrix(const ElementarySquareMatrix& m)
{
    *this = m;
}

/**
 *  \brief Move constructor
 *  \param [in] m const ElementarySquareMatrix&& object contain values
 */
template<typename T>
ElementarySquareMatrix<T>::ElementarySquareMatrix(ElementarySquareMatrix&& m)
{
    *this = std::move(m);
}


/**
 *  \brief Default destructor
 */
template<typename T>
ElementarySquareMatrix<T>::~ElementarySquareMatrix() = default;


/**
 *  \brief Saves a matrix from string of the form [[a<SUB>11</SUB>,...,a<SUB>1n</SUB>]...[a<SUB>n1</SUB>,...,a<SUB>nn</SUB>]]
 *  \param [in] matrix const std::string% string presentation of matrix in form '[[a<SUB>11</SUB>,...,<SUB>a1n</SUB>]...[a<SUB>n1</SUB>,...,<SUB>ann</SUB>]]' where in element: e<SUB>ij</SUB>, <SUB>i</SUB> refers to row and <SUB>j</SUB> refers to column
 */
template<typename T>
void ElementarySquareMatrix<T>::fromString(const std::string& matrix)
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
        std::vector<std::shared_ptr<T>> temp;
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
            std::shared_ptr<T> elem_ptr = getElemPtr(token);

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

	this->n = static_cast<unsigned int>(row_dimension);
}

template<>
std::shared_ptr<Element> SymbolicSquareMatrix::getElemPtr(std::string token)
{
    std::shared_ptr<Element> elem_ptr = nullptr;
    try
    {   //{// try initialize as IntElement
        std::stoi(token);
        elem_ptr = std::make_shared<IntElement>(token);
    } // if throws, try initialize as VariableElement - do not catch
    catch (const std::invalid_argument nn)
    {
        elem_ptr = std::make_shared<VariableElement>(token);
    }

    return elem_ptr;
}

template<>
std::shared_ptr<IntElement> ConcreteSquareMatrix::getElemPtr(std::string token)
{
    std::shared_ptr<IntElement> elem_ptr = nullptr;
    try
	{
        std::stoi(token);
	}
	catch (const std::invalid_argument nn)
	{
        throw std::invalid_argument( "Element not an integer, or it contains character" );
	}
	elem_ptr = std::make_shared<IntElement>(token);
	return elem_ptr;
}

/**
 *  \brief Make transpose of the matrix
 *  \return new matrix transposed
 */
template<typename T>
ElementarySquareMatrix<T> ElementarySquareMatrix<T>::transpose() const
{
    size_t t_n = this->elements.size();
    ElementarySquareMatrix<T> transpose(*this); // probably the quickest way - only for n*n

    for(size_t x = 0; x < t_n; x++)
    {
        for(size_t y = 0; y < t_n; y++)
        {
            transpose.elements.at(y).at(x) = std::static_pointer_cast<T> (this->elements.at(x).at(y)->clone());
        }
    }

    return transpose;
}

/**
 *  \brief Write object to stream in form of [[<a<SUB>11</SUB>>,...,<a<SUB>1n</SUB>>]...[<a<SUB>n1</SUB>>,...,<a<SUB>nn</SUB>>]]
 *		where i<SUB>ij</SUB> : <SUB>i</SUB> refers to row and <SUB>j</SUB> refers to column
 *  \param [out] stream std::ostream& output stream
 */
template<typename T>
void ElementarySquareMatrix<T>::print
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
template<typename T>
std::string ElementarySquareMatrix<T>::toString() const
{
	std::stringstream result;
	result << *this;
	return result.str();
}

/**
 *  \brief Assignment
 *  \param [in] m const ElementarySquareMatrix&
 *  \return Reference to copied right-hand side matrix
 */
template<typename T>
ElementarySquareMatrix<T>& ElementarySquareMatrix<T>::operator=(const ElementarySquareMatrix<T>& m)
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
        std::vector<std::shared_ptr<T>> temp;
        for(auto& elem : row)
        {
            std::shared_ptr<T> elem2 = std::static_pointer_cast<T>(elem->clone());
            temp.push_back(elem2);
        }
        this->elements.push_back(temp);
    }
    return *this;
}

/**
 *  \brief Assignment
 *  \param [in] m ElementarySquareMatrix&&
 *  \return Reference to original right-hand side matrix
 */
template<typename T>
ElementarySquareMatrix<T>& ElementarySquareMatrix<T>::operator=(ElementarySquareMatrix&& m)
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
 *  \param [in] m const ElementarySquareMatrix& m
 *  \return stream appended by object
 */
template<typename T>
std::ostream& operator<<(std::ostream& stream, const ElementarySquareMatrix<T>& m)
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
template<typename T>
ConcreteSquareMatrix ElementarySquareMatrix<T>::evaluate(const Valuation& v) const
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
 *  \param [in] m const ElementarySquareMatrix& value for comparison
 *  \return bool true if this and m are identical
 */
template<typename T>
bool ElementarySquareMatrix<T>::operator==(const ElementarySquareMatrix& m) const
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
            if(this->elements.at(in).at(j)->isEqual(*(m.elements.at(in).at(j))))
            {
            //if(*std::static_pointer_cast<VariableElement>(this->elements.at(in).at(j)) == *std::static_pointer_cast<VariableElement>(m.elements.at(in).at(j)))

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

/**
 *  \brief Addition assignment. Performs matrix addition by adding right-hand side into left-hand side of equation
 *  \param [in] i const ConcreteSquareMatrix& i
 *  \return Reference to left-hand side matrix added by i
 */
template<>
ConcreteSquareMatrix& ConcreteSquareMatrix::operator+=(const ConcreteSquareMatrix& i)
{
    if(this->n != i.n)
    {
        throw std::invalid_argument("operator requires same sized matrices");
    }

    auto && row_i = i.elements.begin();
    for(auto& row_this : this->elements)
    {
        auto && elem_i = row_i->begin();
        for(auto& elem_this : row_this)
        {
            *elem_this += **elem_i;
            elem_i++;
        }
        row_i++;
    }

	return *this;
}

 /**
 *  \brief Substraction assignment. Performs matrix substraction by substracting right-hand side from the left-hand side of equation
 *  \param [in] i const ConcreteSquareMatrix& i
 *  \return Reference to left-hand side matrix substracted by i
 */
template<>
ConcreteSquareMatrix& ConcreteSquareMatrix::operator-=(const ConcreteSquareMatrix& i)
{
    if(this->n != i.n)
    {
        throw std::invalid_argument("operator requires same sized matrices");
    }

    auto && row_i = i.elements.begin();
    for(auto& row_this : this->elements)
    {
        auto && elem_i = row_i->begin();
        for(auto& elem_this : row_this)
        {
            *elem_this -= **elem_i;
            elem_i++;
        }
        row_i++;
    }

	return *this;
}

/**
 *  \brief Multiplication assignment. Performs matrix dot product by multiplying right-hand side into left-hand side of equation
 *  \param [in] i const ConcreteSquareMatrix& i
 *  \return Reference to left-hand side matrix multiplied by i
 */
template<>
ConcreteSquareMatrix& ConcreteSquareMatrix::operator*=(const ConcreteSquareMatrix& i)
{
    if(this->n != i.n)
    {
        throw std::invalid_argument("operator requires same sized matrices");
    }

	ConcreteSquareMatrix temp = *this;

	size_t t_n = this->elements.size();
    for(size_t in = 0; in < t_n; in++)
    {
        for(size_t j = 0; j < t_n; j++)
        {
            IntElement sum;
            for(size_t x = 0; x < t_n; x++)
            {
                sum += *temp.elements.at(in).at(x) * *i.elements.at(x).at(j);
            }
            this->elements.at(in).at(j) = std::static_pointer_cast<IntElement>( sum.clone() );
        }
    }
	return *this;
}

/**
 *  \brief Addition. Performs matrix addition by adding a and b
 *  \param [in] a const ConcreteSquareMatrix&
 *  \return Addition of a and b
 */
template<>
ConcreteSquareMatrix ConcreteSquareMatrix::operator+(const ConcreteSquareMatrix& a) const
{
	ConcreteSquareMatrix t(*this);
	t += a;
	return t;
}

/**
 *  \brief Substraction. Performs matrix substraction by substracting b from a
 *  \param [in] a const ConcreteSquareMatrix&
 *  \return Substraction of a and b
 */
template<>
ConcreteSquareMatrix ConcreteSquareMatrix::operator-(const ConcreteSquareMatrix& a) const
{
	ConcreteSquareMatrix t(*this);
	t -= a;
	return t;
}

/**
 *  \brief Multiplication. Performs matrix dot-product by multiplying a and b
 *  \param [in] a const ConcreteSquareMatrix&
 *  \return Dot-product of a and b
 */
template<>
ConcreteSquareMatrix ConcreteSquareMatrix::operator*(const ConcreteSquareMatrix& a) const
{
	ConcreteSquareMatrix t(*this);
	t *= a;
	return t;
}


/**
 *  \brief Performs matrix addition by summing right-hand side and left-hand side matrices
 *  \param [in] i const ElementarySquareMatrix& i
 *  \return Reference to squarematrix sum of a and b
 */
template<typename T>
ElementarySquareMatrix<T> ElementarySquareMatrix<T>::operator+(const ElementarySquareMatrix<T>& m) const
{
    if(this->n != m.n)
    {
        throw std::invalid_argument("operator requires same sized matrices");
    }

    ElementarySquareMatrix ssm;
    size_t t_n = this->elements.size();

    for(size_t x = 0; x < t_n; x++)
    {
        std::vector<std::shared_ptr<Element>> temp;
        std::shared_ptr<Element> elem_ptr = nullptr;
        for(size_t y = 0; y < t_n; y++)
        {
            elem_ptr = std::make_shared<CompositeElement>(*(this->elements.at(x).at(y)), *(m.elements.at(x).at(y)), std::plus<int>(), '+');
            temp.push_back(elem_ptr);
            //*elem_this += **elem_i;
        }

        ssm.elements.push_back(temp);
    }

    ssm.n = this->n;
	return ssm;
}

/**
 *  \brief Performs matrix substraction of right-hand side and left-hand side matrices
 *  \param [in] i const ElementarySquareMatrix& i
 *  \return Reference to squarematrix substraction of a and b
 */
template<typename T>
ElementarySquareMatrix<T> ElementarySquareMatrix<T>::operator-(const ElementarySquareMatrix<T>& m) const
{
    if(this->n != m.n)
    {
        throw std::invalid_argument("operator requires same sized matrices");
    }

    ElementarySquareMatrix ssm;
    size_t t_n = this->elements.size();

    for(size_t x = 0; x < t_n; x++)
    {
        std::shared_ptr<Element> elem_ptr = nullptr;
        std::vector<std::shared_ptr<Element>> temp;
        for(size_t y = 0; y < t_n; y++)
        {
            elem_ptr = std::make_shared<CompositeElement>(*(this->elements.at(x).at(y)), *(m.elements.at(x).at(y)), std::minus<int>(), '-');
            temp.push_back(elem_ptr);
        }

        ssm.elements.push_back(temp);
    }

    ssm.n = this->n;
	return ssm;
}

/**
 *  \brief Performs matrix multiplication of right-hand side and left-hand side matrices
 *  \param [in] m const ElementarySquareMatrix& m
 *  \return Reference to squarematrix multiplication of a and b
 */
template<typename T>
ElementarySquareMatrix<T> ElementarySquareMatrix<T>::operator*(const ElementarySquareMatrix<T>& m) const
{
    if(this->n != m.n)
    {
        throw std::invalid_argument("operator requires same sized matrices");
    }

    ElementarySquareMatrix ssm;
    size_t t_n = this->elements.size();

    for(size_t x = 0; x < t_n; x++)
    {

        std::vector<std::shared_ptr<Element>> temp;
        for(size_t y = 0; y < t_n; y++)
        {
            std::shared_ptr<Element> elem_ptr = nullptr;
            std::shared_ptr<Element> prev_ptr = nullptr;
            std::shared_ptr<Element> sum_ptr = nullptr;
            //std::vector<std::shared_ptr<Element>> toSum;

            for(size_t tx = 0; tx < t_n; tx++)
            {
                elem_ptr = std::make_shared<CompositeElement>(*(this->elements.at(x).at(tx)), *(m.elements.at(tx).at(y)), std::multiplies<int>(), '*');
                if(prev_ptr!=nullptr)
                {
                    sum_ptr = std::make_shared<CompositeElement>(*prev_ptr, *elem_ptr, std::plus<int>(), '+');
                    prev_ptr = sum_ptr;
                }
                else
                {
                    sum_ptr = elem_ptr;
                    prev_ptr = elem_ptr;
                }
            }
            //elem_ptr = std::make_shared<CompositeElement>(*(this->elements.at(x).at(y)), *(m.elements.at(x).at(y)), std::multiplies<int>(), '*');
            temp.push_back(sum_ptr);
        }
        ssm.elements.push_back(temp);
    }

    ssm.n = this->n;
	return ssm;
}


template class ElementarySquareMatrix<IntElement>;
template class ElementarySquareMatrix<Element>;
