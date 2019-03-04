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
 *  \brief Main function
 *  \return 0 on success, 1 on wrong argument
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
    // benchmark(500, 5000); // debug
    // return 0;    // debug

    if(argc < 2)
    {
        Catch::Session().run();
        return 0;
    }

    else if(std::string(argv[1]) == "--benchmark" || std::string(argv[1]) == "-b")
    {
        benchmark(700, 7000);
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


