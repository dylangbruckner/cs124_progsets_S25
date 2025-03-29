#ifndef STRASSENS.HPP
#define STRASSENS.HPP
#include "matrix.hpp"

// The cutoff for where we use normal matrix multiplication
const size_t CUTOFF = 2;
Matrix<int> strassen_mult(const Matrix<int>& M1, const Matrix<int>& M2);

#endif // STRASSENS.HPP