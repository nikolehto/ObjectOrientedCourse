#include "issqmatrix.h"
#include <string>
#include <iostream>
#include <vector>

bool isNumber(const std::string& number)
{
	size_t idx = 0;

	long double temp;
	try
	{
		temp = std::stold(number, &idx);
	}
	catch (std::invalid_argument nn)
	{
		return false;
	}

	if (idx != number.length())
	{
		return false;
	}

	return true;
}

bool isSquareMatrix(const std::string& matrix)
{
	size_t len = matrix.length();	

	// check char validity
	if (matrix.find_first_not_of("[]0123456789.,+-") != std::string::npos)
	{
		std::cout << "Illegal character \n";
		return false;
	}

	if (len < 5) // 5 characters is shortest possible square matrix i.e. [[1]]
	{
		std::cout << "Too few characters to be a Matrix \n";
		return false;
	}

	if (matrix.substr(0,2) != "[[") // require start 
	{
		std::cout << "Should start [[ \n";
		return false;
	}

	if (matrix.substr(len - 2, 2) != "]]") // require end
	{
		std::cout << "Should end ]]\n" << matrix.substr(len - 2, 2) << " found \n";
		return false;
	}

	size_t row_start_idx, row_end_idx;
	row_start_idx = 2;
	bool matrix_ends = false;

	size_t row_dimension = 0;
	size_t column_dimension = -1;
	while(!matrix_ends)
	{
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
				std::cout << "Row expected, not found..";
				return false; 
			}
		}

		row_dimension++;

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

			if (!isNumber(matrix.substr(elem_start_idx, elem_end_idx - elem_start_idx)))
			{
				std::cout << "Element not a number.." << matrix.substr(elem_start_idx, elem_end_idx - 1 - elem_start_idx) << "\n";
				return false; 
			}
			current_column_dimension++;

			elem_start_idx = elem_end_idx + 1;
		}
		if (column_dimension == -1 || column_dimension == current_column_dimension)
		{
			column_dimension = current_column_dimension;
		}
		else
		{
			std::cout << "All columns should have same dimension.. ";
			return false;
		}

		row_start_idx = row_end_idx + 2;
	}

	if (row_dimension != column_dimension)
	{
		std::cout << "Not a square matrix.. " << "Found " << row_dimension << " X " << column_dimension << "matrix \n" ;
		return false;
	}

	std::cout << "Found " << row_dimension << " X " << column_dimension << "matrix \n";
	return true;
}

int main()
{
	std::vector<std::string> corrects = {};
	std::vector<std::string> invalids = {};

	corrects.push_back("[[1]]"); // 1x1
	corrects.push_back("[[1,2][5,6]]"); // 2x2
	corrects.push_back("[[1,2,5][3,4,6][5,6,7]]"); // 3x3 
	corrects.push_back("[[61161,233333,1][315151,441241,3][1,51661,67777772222222222777222222777777767777777777777777777777777777777777345777777767777777777777777777777777777777777345777777777777345]]"); // 3x3 long numbers
	corrects.push_back("[[1.1,2,+0.31][-13,-1.4,6.01][5.11,.5,-.7]]"); // negative and float numners
	invalids.push_back("a[2]]");
	invalids.push_back("[[1,2,5][3,4,6]]"); // 3x2
	invalids.push_back("[[1,2][3,4][1,2]]");	// 2x3
	invalids.push_back("[[1,2,4][3,4,1][1,2]]");	// ?x3 fault at end
	invalids.push_back("[[1,2][1,2,4][3,4,1]]");    // ?x3 fault at start
	invalids.push_back("[[1.1,2,0.31][-13,-1.4,6.01][5.11,1.5.2,-.7]]"); // double dot
	invalids.push_back("[[1.1,2,0.31][1-3,-1.4,6.01][5.11,1.5,-.7]]"); // minus sign wrong place
	invalids.push_back("[[1.1,2,0.31][1-3,1.4,6.01][5.11,1.5,-.7]]"); // minus sign wrong place
	invalids.push_back("[[1.1,2,0.3e][1-3,1.4,6.01][5.11,1.5,-.7]]"); // illegal character

	std::cout << "test corrects: \n\n";
	for (std::string c : corrects)
	{
		std::cout << c << " : " << isSquareMatrix(c) << "\n\n";
	}

	std::cout << "test invalids: \n\n";
	for (std::string c : invalids)
	{
		std::cout << c << " : " << isSquareMatrix(c) << "\n\n";
	}

	std::cout << "quit \n";
}