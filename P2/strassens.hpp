#ifndef STRASSENS_HPP
#define STRASSENS_HPP
#include "matrix.hpp"

// The cutoff for where we use normal matrix multiplication
const size_t CUTOFF = 20;

// performs matrix multiplication on two padded matrices according to strassens algorithm
Matrix<int> strassen_mult_init(const Matrix<int>& M1, const Matrix<int>& M2);

// performs matrix multiplication according to strassens algorithm
Matrix<int> strassen_mult(const Matrix<int>& M1, const Matrix<int>& M2);

// returns the minimum matrix size larger than or equal to dim
// such that dividing it two recursively will never make dim
// odd before crossing the cutoff

#endif // STRASSENS_HPP