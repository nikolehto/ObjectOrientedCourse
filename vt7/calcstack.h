#ifndef CALCSTACK_H
#define CALCSTACK_H

#include <sstream>
#include <vector>
#include "elementarysquarematrix.h"

/**
 * @file calcstack.h
 * @version 2.5
 * @brief Declaration of Stack for calculator
 * @author Niko Lehto
 */

// Stack class based on https://www.tutorialspoint.com/cplusplus/cpp_templates.htm
template <class T>
class Stack {
    private:
        std::vector<T> matrices;

    public:
        void push(T const&);  // push matrix
        T top() const;            // return top element
        T topp() const;           // return second top element
        size_t len() const;
};
#endif
