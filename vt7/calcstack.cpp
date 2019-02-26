#include "calcstack.h"

/**
 *  @file calcstack.cpp
 *  @brief Implementation of stack for calculator
 *  */
template <typename T>
void Stack<T>::push (T const& matrix) {
   matrices.push_back(matrix);
}

template <class T>
T Stack<T>::top () const {
   if (matrices.empty()) {
      throw std::out_of_range("Stack<>::top(): empty stack");
   }

   // return last element
   return matrices.back();
}

template <class T>
T Stack<T>::topp () const {
   if (matrices.size() < 2) {
      throw std::out_of_range("Stack<>::topp(): empty stack");
   }

   // return second last element
    return matrices.end()[-2];
}

template <class T>
size_t Stack<T>::len() const {
    return matrices.size();
}

template class Stack<SymbolicSquareMatrix>;
