#include "squarematrix.h"

/**
 *  @file squarematrix.cpp
 *  @brief Implementation of SquareMatrix
 *  */

 /**
 *  @class SquareMatrix
 *  @version 2.0
 *  @brief Implementation for nxn dimensional SquareMatrix
 *  @author Niko Lehto
 *  */

/**
 *  \brief Empty constructor
 */
SquareMatrix::SquareMatrix() = default;

/**
 *  \brief Constructs a matrix from string of the form [[a<SUB>11</SUB>,...,a<SUB>1n</SUB>]...[a<SUB>n1</SUB>,...,a<SUB>nn</SUB>]]
 *  \param [in] s const std::string% string presentation of matrix in form '[[a<SUB>11</SUB>,...,<SUB>a1n</SUB>]...[a<SUB>n1</SUB>,...,<SUB>ann</SUB>]]' where in element: e<SUB>ij</SUB>, <SUB>i</SUB> refers to row and <SUB>j</SUB> refers to column
*/
SquareMatrix::SquareMatrix(const std::string& s)
{
    fromString(s);
    // set n and elements
}

/**
 *  \brief Constructs a matrix from randomly generated integers
 *  \param [in] n dimension of square matrix
*/
SquareMatrix::SquareMatrix(int n)
{
    unsigned int seed = time(0);

    this->n = n;

    this->elements.reserve(n);

    unsigned int threadsSupported = std::thread::hardware_concurrency();
    if(threadsSupported == 0)
    {
        threadsSupported = 8; // anything should be fine
    }

    std::vector<std::thread> workers;
    std::mutex elementlock;

	float step = n / (float) threadsSupported;

    for(size_t worker = 0; worker < threadsSupported; worker++)
    {
		size_t worker_start = round(worker * step);
		size_t worker_stop = round(((worker+1) * step));

        workers.push_back(std::thread([&, worker_start, worker_stop]()
        {
            std::srand(seed + worker_start);
            for(size_t i = worker_start; i < worker_stop; i++)
            {
                std::vector<IntElement> intEls(n);
                std::generate(intEls.begin(), intEls.end(), std::rand);
                elementlock.lock();
                this->elements.push_back(intEls);
                elementlock.unlock();
            }
        }));

    }

    std::for_each(workers.begin(), workers.end(), [](std::thread &t)
    {
        t.join();
    });
}

/**
 *  \brief Clone constructor
 *  \param [in] i const SquareMatrix& object to clone
 */
SquareMatrix::SquareMatrix(const SquareMatrix& i)
{
    this->elements = i.elements;
    this->n = i.n;
}

/**
 *  \brief Destructor
 */
SquareMatrix::~SquareMatrix() = default;

/**
 *  \brief Saves a matrix from string of the form [[a<SUB>11</SUB>,...,a<SUB>1n</SUB>]...[a<SUB>n1</SUB>,...,a<SUB>nn</SUB>]]
 *  \param [in] matrix const std::string% string presentation of matrix in form '[[a<SUB>11</SUB>,...,<SUB>a1n</SUB>]...[a<SUB>n1</SUB>,...,<SUB>ann</SUB>]]' where in element: e<SUB>ij</SUB>, <SUB>i</SUB> refers to row and <SUB>j</SUB> refers to column
*/
void SquareMatrix::fromString(const std::string& matrix)
{
	size_t len = matrix.length();

	// check char validity
	size_t illegal_char = matrix.find_first_not_of("[]0123456789.,+-");
	if (illegal_char != std::string::npos)
	{
	    throw std::invalid_argument("Illegal character in matrix: \"" + matrix.substr(illegal_char,1) + "\" ");
	}

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
        std::vector<IntElement> temp;
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

            // Try to initialize as IntElement
            const std::string token(matrix.substr(elem_start_idx, elem_end_idx - elem_start_idx));
			temp.push_back(IntElement(token));
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

SquareMatrix SquareMatrix::transpose() const
{
    size_t t_n = this->elements.size();
    SquareMatrix transpose(*this); // probably the quickest way - only for n*n

    for(size_t x = 0; x < t_n; x++)
    {
        for(size_t y = 0; y < t_n; y++)
        {
            transpose.elements.at(y).at(x) = this->elements.at(x).at(y);
        }
    }

    return transpose;
}

/**
 *  \brief Write object to stream in form of [[<a<SUB>11</SUB>>,...,<a<SUB>1n</SUB>>]...[<a<SUB>n1</SUB>>,...,<a<SUB>nn</SUB>>]]
 *		where i<SUB>ij</SUB> : <SUB>i</SUB> refers to row and <SUB>j</SUB> refers to column
 *  \param [out] stream std::ostream& output stream
 */
void SquareMatrix::print
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
std::string SquareMatrix::toString() const
{
	std::stringstream result;
	result << *this;
	return result.str();
}

/**
 *  \brief Assignment
 *  \param [in] i const SquareMatrix& i
 *  \return Reference to left-hand side matrix added by i
 */
SquareMatrix& SquareMatrix::operator=(const SquareMatrix& i)
{
    this->elements = i.elements;
    this->n = i.n;
	return *this;
}

/**
 *  \brief Addition assignment. Performs matrix addition by adding right-hand side into left-hand side of equation
 *  \param [in] m const SquareMatrix& m
 *  \return Reference to left-hand side matrix added by m
 */
SquareMatrix& SquareMatrix::operator+=(const SquareMatrix& m)
{
    if(this->n != m.n)
    {
        throw std::invalid_argument("operator requires same sized matrices");
    }

    unsigned int threadsSupported = std::thread::hardware_concurrency();
    if(threadsSupported == 0)
    {
        threadsSupported = 8; // anything should be fine
    }

    std::vector<std::thread> workers;

	size_t t_n = this->elements.size();

	float step = t_n / (float) threadsSupported;

    for(size_t worker = 0; worker < threadsSupported; worker++)
    {
		size_t worker_start = round(worker * step);
		size_t worker_stop = round(((worker+1) * step));

        workers.push_back(std::thread([&, worker_start, worker_stop]()
        {
            for(size_t i = worker_start; i < worker_stop; i++)
            {
                for(size_t j = 0; j < t_n; j++)
                {
                    this->elements.at(i).at(j) += m.elements[i][j];
                }
            }
        }));

    }

    std::for_each(workers.begin(), workers.end(), [](std::thread &t)
    {
        t.join();
    });

	return *this;
}

 /**
 *  \brief Substraction assignment. Performs matrix substraction by substracting right-hand side from the left-hand side of equation
 *  \param [in] m const SquareMatrix& m
 *  \return Reference to left-hand side matrix substracted by m
 */
SquareMatrix& SquareMatrix::operator-=(const SquareMatrix& m)
{
    if(this->n != m.n)
    {
        throw std::invalid_argument("operator requires same sized matrices");
    }

    unsigned int threadsSupported = std::thread::hardware_concurrency();
    if(threadsSupported == 0)
    {
        threadsSupported = 8; // anything should be fine
    }

    std::vector<std::thread> workers;

	size_t t_n = this->elements.size();

	float step = t_n / (float) threadsSupported;

    for(size_t worker = 0; worker < threadsSupported; worker++)
    {
		size_t worker_start = round(worker * step);
		size_t worker_stop = round(((worker+1) * step));

        workers.push_back(std::thread([&, worker_start, worker_stop]()
        {
            for(size_t i = worker_start; i < worker_stop; i++)
            {
                for(size_t j = 0; j < t_n; j++)
                {
                    this->elements.at(i).at(j) -= m.elements[i][j];
                }
            }
        }));

    }

    std::for_each(workers.begin(), workers.end(), [](std::thread &t)
    {
        t.join();
    });

	return *this;
}

/**
 *  \brief Multiplication assignment. Performs matrix dot product by multiplying right-hand side into left-hand side of equation
 *  \param [in] i const SquareMatrix& i
 *  \return Reference to left-hand side matrix multiplied by i
 */
SquareMatrix& SquareMatrix::operator*=(const SquareMatrix& i)
{
    if(this->n != i.n)
    {
        throw std::invalid_argument("operator requires same sized matrices");
    }

	SquareMatrix temp = *this;

    unsigned int threadsSupported = std::thread::hardware_concurrency();
    if(threadsSupported == 0)
    {
        threadsSupported = 8; // anything should be fine
    }

    std::vector<std::thread> workers;

	size_t t_n = this->elements.size();

	float step = t_n / (float) threadsSupported;

    for(size_t worker = 0; worker < threadsSupported; worker++)
    {
		size_t worker_start = round(worker * step);
		size_t worker_stop = round(((worker+1) * step));

        workers.push_back(std::thread([&, worker_start, worker_stop]()
        {
            for(size_t in = worker_start; in < worker_stop; in++)
            {
                for(size_t j = 0; j < t_n; j++)
                {
                    IntElement sum;
                    for(size_t x = 0; x < t_n; x++)
                    {
                        sum += temp.elements.at(in).at(x) * i.elements.at(x).at(j);
                    }
                    this->elements.at(in).at(j) = sum;
                }
            }
        }));
    }

    std::for_each(workers.begin(), workers.end(), [](std::thread &t)
    {
        t.join();
    });

	return *this;
}

/**
 *  \brief Addition. Performs matrix addition by adding a and b
 *  \param [in] a const SquareMatrix&
 *  \param [in] b const SquareMatrix&
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
 *  \param [in] a const SquareMatrix&
 *  \param [in] b const SquareMatrix&
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
 *  \param [in] a const SquareMatrix&
 *  \param [in] b const SquareMatrix&
 *  \return Dot-product of a and b
 */
SquareMatrix operator*(const SquareMatrix& a, const SquareMatrix& b)
{
	SquareMatrix t_a(a);
	t_a *= b;
	return t_a;
}

/**
 *  \brief Write object to stream in form of [[<i<SUB>11</SUB>>,<i<SUB>12</SUB>>][<i<SUB>21</SUB>>,<i<SUB>22</SUB>>]]
 *  \param [in,out] stream std::ostream&
 *  \param [in] m const SquareMatrix& m
 *  \return stream appended by object
 */
std::ostream& operator<<(std::ostream& stream, const SquareMatrix& m)
{
	stream << "[";
    for(auto element : m.elements)
    {
        stream << "[";
        for(size_t ind = 0; ind < element.size(); ind++)
        {
            if(ind != element.size() - 1)
            {
                stream << element.at(ind) << ",";
            }
            else
            {
                stream << element.at(ind);
            }
        }
        stream << "]";
    }
    stream << "]";

    return stream;
}

/**
 *  \brief Overload of equal comparison
 *  \param [in] m const SquareMatrix& value for comparison
 *  \return bool true if this and m are identical
 */
bool SquareMatrix::operator==(const SquareMatrix& m) const
{
    if(this->n != m.n)
    {
        return false;
    }

    auto row_m = m.elements.begin();
    for(auto row_this : this->elements)
    {
        auto elem_m = row_m->begin();
        for(auto elem_this : row_this)
        {
            if(elem_this == *elem_m)
            {
            }
            else
            {
                return false;
            }
            elem_m++;
        }
        row_m++;
    }
    return true;
}
