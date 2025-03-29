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
    Matrix<int> P3 = strassen_mult(matrix_add(C, D), H);
    Matrix<int> P4 = strassen_mult(D, matrix_sub(G, E));
    Matrix<int> P5 = strassen_mult(matrix_add(A, D), matrix_add(E, H));
    Matrix<int> P6 = strassen_mult(matrix_sub(B, D), matrix_add(G, H));
    Matrix<int> P7 = strassen_mult(matrix_sub(C, A), matrix_add(E, F));

    // combine results
    Matrix<int> C(n);
    auto C11 = C.submatrix(0, 0, half);
    auto C12 = C.submatrix(0, half, half);
    auto C21 = C.submatrix(half, 0, half);
    auto C22 = C.submatrix(half, half, half);

    C11 = matrix_add(matrix_sub(matrix_add(P5, P4), P2), P6);
    C12 = matrix_add(P1, P2);
    C21 = matrix_add(P3, P4);
    C22 = matrix_add(matrix_sub(P1, P3), matrix_add(P5, P7));

    return C;
}

