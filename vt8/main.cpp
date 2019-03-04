#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "intelement.h"
#include "squarematrix.h"
#include <chrono>

/**
 *  @file main.cpp
 *  @brief Implementation of main function
 *  */


void benchmark(int n)
{
    std::chrono::time_point<std::chrono::system_clock> t0, t1, t2;
    std::chrono::duration<double> elapsed_seconds;

    t0 = t1 = std::chrono::system_clock::now();
    SquareMatrix a(n), b(n), c(n);
    SquareMatrix result;

    t2 = std::chrono::system_clock::now();
    elapsed_seconds = t2 - t1;
    std::cout << "constructors took: " << elapsed_seconds.count() << '\n';
    t1 = std::chrono::system_clock::now();

    result = a + b;

    t2 = std::chrono::system_clock::now();
    elapsed_seconds = t2 - t1;
    std::cout << "addition took: " << elapsed_seconds.count() << '\n';
    t1 = std::chrono::system_clock::now();

    result *= result;

    t2 = std::chrono::system_clock::now();
    elapsed_seconds = t2 - t1;
    std::cout << "multiplication took: " << elapsed_seconds.count() << '\n';
    t1 = std::chrono::system_clock::now();

    result -= b;

    elapsed_seconds = t2 - t1;
    std::cout << "substraction took: " << elapsed_seconds.count() << '\n';

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
    int n = 600;

    benchmark(n); // debug
    return 0;    // debug

    if(argc < 2)
    {
        Catch::Session().run();
        return 0;
    }
    else if(std::string(argv[1]) == "--benchmark" || std::string(argv[1]) == "-b")
    {
        benchmark(n);
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


