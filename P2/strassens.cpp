#include "strassens.hpp"


// performs the recursive portion of Strassen's
// should never be called outside of this file
// to call, use strassen_mult_init 
void strassen_mult_recursion(const Matrix<int>& M1, const Matrix<int>& M2, Matrix<int>& Res, const Matrix<int>& Storage);

// make sure matrices passed into this are padded
Matrix<int> strassen_mult_init(const Matrix<int>& M1, const Matrix<int>& M2) {
    const size_t n = M1.getDim();
    
    // base case: switch to standard multiplication
    if(n <= CUTOFF) {
        return matrix_mult(M1, M2);
    }
    Matrix<int> result(n), storage(n);
    strassen_mult_recursion(M1, M2, result, storage);
    return result;
}

void strassen_mult_recursion(const Matrix<int>& M1, const Matrix<int>& M2, Matrix<int>& Res, const Matrix<int>& Storage) {
    // assert(M1.getDim() == M2.getDim()); 
    // assert(Res.getDim() == Storage.getDim());
    // assert(M1.getDim() == Res.getDim());

    const size_t n = M1.getDim();
    if(n <= CUTOFF) {
        matrix_mult_in_place(M1, M2, Res);
        return;
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

    // Split result and storage matrix into quarters
    auto RA = Res.submatrix(0, 0, half);
    auto RB = Res.submatrix(0, half, half); 
    auto RC = Res.submatrix(half, 0, half);  
    auto RD = Res.submatrix(half, half, half);

    auto SA = Storage.submatrix(0, 0, half); // M1 future calcs
    auto SB = Storage.submatrix(0, half, half); // M2 future calcs
    auto SC = Storage.submatrix(half, 0, half); // future calcs return
    auto SD = Storage.submatrix(half, half, half); // storage future calcs

    // P1
    matrix_inplace(A, SA); // A is new M1
    matrix_sub_inplace(F, H, SB); // F-H is new M2
    strassen_mult_recursion(SA, SB, RB, SD); // add P1 to top right return
    matrix_inplace(RB, RD); // add to bottom right

    // P5
    matrix_add_inplace(A, D, SA); // A + D is new M1
    matrix_add_inplace(E, H, SB); // E + H is new M2
    strassen_mult_recursion(SA, SB, RA, SD);  // add P5 to top left return
    matrix_add_inplace(RA, RD, RD); // add to bottom right

    // P2
    matrix_add_inplace(A, B, SA); // same gist as above
    matrix_inplace(H, SB);
    strassen_mult_recursion(SA, SB, SC, SD); // put into SD - must be manually moved 
    matrix_sub_inplace(RA, SC, RA);
    matrix_add_inplace(SC, RB, RB);

    // P3
    matrix_add_inplace(C, D, SA); 
    matrix_inplace(E, SB);        
    strassen_mult_recursion(SA, SB, RC, SD); // add P3 to bottom left
    matrix_sub_inplace(RD, RC, RD); 

    // P4
    matrix_inplace(D, SA);
    matrix_sub_inplace(G, E, SB);
    strassen_mult_recursion(SA, SB, SC, SD);

    matrix_add_inplace(SC, RA, RA);
    matrix_add_inplace(SC, RC, RC);

    // P6
    matrix_sub_inplace(B, D, SA);
    matrix_add_inplace(G, H, SB);
    strassen_mult_recursion(SA, SB, SC, SD);

    matrix_add_inplace(SC, RA, RA);

    // P7
    matrix_sub_inplace(C, A, SA);
    matrix_add_inplace(E, F, SB);
    strassen_mult_recursion(SA, SB, SC, SD);

    matrix_add_inplace(SC, RD, RD);

    // finished computing result, return
    return;
}

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

    matrix_add_inplace(P5, P4, C11);
    matrix_sub_inplace(C11, P2, C11);
    matrix_add_inplace(C11, P6, C11);
    matrix_add_inplace(P1, P2, C12);
    matrix_add_inplace(P3, P4, C21);
    matrix_add_inplace(P5, P7, C22);
    matrix_sub_inplace(C22, P3, C22);
    matrix_add_inplace(C22, P1, C22);

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