#define CATCH_CONFIG_RUNNER
#include "calcstack.h"
#include "catch.hpp"
#include "telement.h"
#include "compositeelement.h"
#include "elementarysquarematrix.h"
#include "element.h"
#include "valuation.h"

/**
 *  @file main.cpp
 *  @brief Implementation of main function
 *  */

/**
 *  \brief String to int
 *  \param [in] number std::string&  stream
 *  \return int value from string if success
 */
int stringToInt(const std::string& number)
{
	size_t idx = 0;
    int value;

	try
	{
		value = std::stoi(number, &idx);
	}
	catch (const std::invalid_argument nn)
	{
        throw std::invalid_argument( "Element contains zero or multiple chars, one char or integer required" );
    }

	if (idx != number.length())
	{
		throw std::invalid_argument( "Element not an integer, or it contains character" );
	}
	return value;
}


/**
 *  \brief Main function
 *  \return 0 on success, -1 on ioerror
 */
int main()
{
    Catch::Session().run();

    bool exit = false;
    Stack<SymbolicSquareMatrix> matrixStack;
    Valuation v;

    while(!exit)
    {
        std::string matrixN;

        std::cout << "Input matrix, operation or quit: ";
        if (!std::getline(std::cin, matrixN))
        {
            return -1;
        }

        if (matrixN == "quit") {
            exit = true;
            break;
        }
        else if(matrixN == "+")
        {
            if(matrixStack.len() < 2)
            {
                std::cout << "Require at least 2 matrices on stack " << std::endl;
            }
            else
            {
                SymbolicSquareMatrix sym;
                try
                {
                    sym = matrixStack.topp() + matrixStack.top();
                }
                catch (const std::invalid_argument& ex) {
                    std::cout << ex.what() << std::endl;
                    continue;
                }
                std::cout << sym;
                matrixStack.push(sym);
            }
        }
        else if(matrixN == "-")
        {
            if(matrixStack.len() < 2)
            {
                std::cout << "Require at least 2 matrices on stack " << std::endl;
            }
            else
            {
                SymbolicSquareMatrix sym;
                try
                {
                    sym = matrixStack.topp() - matrixStack.top();
                }
                catch (const std::invalid_argument& ex) {
                    std::cout << ex.what() << std::endl;
                    continue;
                }
                std::cout << sym;
                matrixStack.push(sym);
            }
        }
        else if(matrixN == "*")
        {
            if(matrixStack.len() < 2)
            {
                std::cout << "Require at least 2 matrices on stack " << std::endl;
            }
            else
            {
                SymbolicSquareMatrix sym;
                try
                {
                    sym = matrixStack.topp() * matrixStack.top();
                }
                catch (const std::invalid_argument& ex) {
                    std::cout << ex.what() << std::endl;
                    continue;
                }
                std::cout << sym;
                matrixStack.push(sym);
            }
        }

        else if(matrixN == "=")
        {
            if(matrixStack.len() < 1)
            {
                std::cout << "Require at least 1 matrices on stack " << std::endl;
            }
            else
            {
                try
                {
                    std::cout << matrixStack.top().evaluate(v) << std::endl;
                }
                catch (const std::invalid_argument& ex) {
                    std::cout << ex.what() << std::endl;
                    continue;
                }
            }
        }

        else if(matrixN.length() > 2 && matrixN.at(1) == '=')
        {
            int value;
            char c;
            try
            {
                c = matrixN.at(0);
                value = stringToInt(matrixN.substr(2));
                v[c] = value;
            }
            catch (std::invalid_argument const& ex) {
                std::cout << "Bad input" << std::endl;
                continue;
            }
        }
        else
        {
            try
            {
                matrixStack.push(SymbolicSquareMatrix(matrixN));
            }
            catch (std::invalid_argument const& ex) {
                std::cout << "Bad input" << std::endl;
                continue;
            }
        }
    }

    return 0;
}


