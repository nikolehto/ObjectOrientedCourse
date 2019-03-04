#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "intelement.h"
#include "squarematrix.h"
#include <chrono>

/**
 *  @file main.cpp
 *  @brief Implementation of main function
 *  */

/**
benchmark:
    multi_n = 1000, other_n 10000
    ryzen 1600

12-threads
    constructors took: 0.770173
    addition took: 1.11825
    subtraction took: 0.928209
    multiplication and transpose took: 2.34753
    benchmark took: 5.16716

single-thread
    constructors took: 4.24796
    addition took: 4.81182
    subtraction took: 4.32765
    multiplication and transpose took: 11.1886
    benchmark took: 24.578

*/

/**
*  \brief Mix of constructor and calculation operations
*  \param [in] multi_n int dimension of matrices used in multiplication bench
*  \param [in] other_n int dimension of matrices used in addition substraction benches
*/
void benchmark(int multi_n, int other_n)
{
    unsigned int threadsSupported = std::thread::hardware_concurrency();
    std::cout << "Threads detected: " << threadsSupported << std::endl;

    std::chrono::time_point<std::chrono::system_clock> t0, t1, t2;
    std::chrono::duration<double> elapsed_seconds;

    // Constructor test

    t0 = t1 = std::chrono::system_clock::now();
    SquareMatrix m_a(multi_n), m_b(multi_n);
    SquareMatrix o_a(other_n), o_b(other_n);
    SquareMatrix result;

    t2 = std::chrono::system_clock::now();
    elapsed_seconds = t2 - t1;
    std::cout << "constructors took: " << elapsed_seconds.count() << '\n';
    t1 = std::chrono::system_clock::now();

    result = o_a + o_b;
    result += o_a;
    result += o_b;
    result += result;
    result += o_a;
    result += o_b;
    result += result;

    t2 = std::chrono::system_clock::now();
    elapsed_seconds = t2 - t1;
    std::cout << "addition took: " << elapsed_seconds.count() << '\n';
    t1 = std::chrono::system_clock::now();

    result = o_a - o_b;
    result -= o_a;
    result -= o_b;
    result -= result;
    result -= o_a;
    result -= o_b;
    result -= result;

    t2 = std::chrono::system_clock::now();
    elapsed_seconds = t2 - t1;
    std::cout << "subtraction took: " << elapsed_seconds.count() << '\n';
    t1 = std::chrono::system_clock::now();

    result = m_a * m_b.transpose();
    result *= m_a;

    t2 = std::chrono::system_clock::now();
    elapsed_seconds = t2 - t1;
    std::cout << "multiplication and transpose took: " << elapsed_seconds.count() << '\n';


    t2 = std::chrono::system_clock::now();
    elapsed_seconds = t2-t0;
    std::cout << "benchmark took: " << elapsed_seconds.count() << '\n';

}

/**
 *  \brief Main function
 *  \return 0 on success, 1 on wrong argument
 */
int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        Catch::Session().run();
        return 0;
    }

    else if(std::string(argv[1]) == "--benchmark" || std::string(argv[1]) == "-b")
    {
        benchmark(1000, 10000);
        return 0;
    }

    else
    {
        std::cout << "usage: \n"
                    << "  no arguments    : run catch tests \n"
                    << "  -b  --benchmark : run benchmark \n" << std::endl;
        return 1;
    }
}


