#ifndef STRASSENS_HPP
#define STRASSENS_HPP
#include "matrix.hpp"

// The cutoff for where we use normal matrix multiplication
const size_t CUTOFF = 0;

// performs matrix multiplication according to strassens algorithm
Matrix<int> strassen_mult(const Matrix<int>& M1, const Matrix<int>& M2);

// returns the minimum matrix size larger than or equal to dim
// such that dividing it two recursively will never make dim
// odd before crossing the cutoff
size_t padding_calc(size_t dim);

#endif // STRASSENS_HPP