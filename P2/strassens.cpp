#include "strassens.hpp"

Matrix<int> strassen_mult(const Matrix<int>& M1, const Matrix<int>& M2) {
    const size_t n = M1.getDim();
    
    // base case: switch to standard multiplication
    if(n <= CUTOFF) {
        return matrix_mult(M1, M2);
    }

    // Split matrices into quarters
    const size_t half = n / 2;
    auto A = M1.submatrix(0, 0, half);
    auto B = M1.submatrix(0, half, half);
    auto C = M1.submatrix(half, 0, half);
    auto D = M1.submatrix(half, half, half);

    auto E = M2.submatrix(0, 0, half);
    auto F = M2.submatrix(0, half, half);
    auto G = M2.submatrix(half, 0, half);
    auto H = M2.submatrix(half, half, half);


    // compute intermediaries
    Matrix<int> P1 = strassen_mult(A, matrix_sub(F, H));
    Matrix<int> P2 = strassen_mult(matrix_add(A, B), H);
    Matrix<int> P3 = strassen_mult(matrix_add(C, D), E);
    Matrix<int> P4 = strassen_mult(D, matrix_sub(G, E));
    Matrix<int> P5 = strassen_mult(matrix_add(A, D), matrix_add(E, H));
    Matrix<int> P6 = strassen_mult(matrix_sub(B, D), matrix_add(G, H));
    Matrix<int> P7 = strassen_mult(matrix_sub(C, A), matrix_add(E, F));

    // combine results
    // todo instead of making a new matrix here, just put it back in the original?
    // should work, will wait till after I test this implementatino though
    Matrix<int> M(n);
    auto C11 = M.submatrix(0, 0, half);
    auto C12 = M.submatrix(0, half, half);
    auto C21 = M.submatrix(half, 0, half);
    auto C22 = M.submatrix(half, half, half);

    matrix_add_sub_in(P5, P4, C11);
    matrix_sub_sub_in(C11, P2, C11);
    matrix_add_sub_in(C11, P6, C11);
    matrix_add_sub_in(P1, P2, C12);
    matrix_add_sub_in(P3, P4, C21);
    matrix_add_sub_in(P5, P7, C22);
    matrix_sub_sub_in(C22, P3, C22);
    matrix_add_sub_in(C22, P1, C22);

    return M;
};

size_t padding_calc(size_t dim) {
    if (dim <= CUTOFF) {
        return dim;
    }

    // simulate dividing the dimension and padding if necessary
    size_t divisions = 0;
    while (dim > CUTOFF) {
        if (dim % 2 != 0) {
            dim += 1;  
        }
        dim /= 2;
        divisions += 1;
    }

    return dim * pow(2, divisions);
};