#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>
#include <random>

template <typename T>
class Matrix {
    std::vector<T> data; // Data (only in root matrix)
    T* view_ptr;         // pointer to (sub-)matrix start
    size_t dim;          // only using square matrices
    size_t step;         // stride between rows (dim for root matrix)


public:
    // root matrix constructor
    Matrix(size_t size): data(size * size), view_ptr(data.data()), 
                         dim(size), step(size) {}

    // submatrix constructor
    Matrix(T* base, size_t sub_size, size_t parent_step):
        view_ptr(const_cast<T*>(base)), dim(sub_size), step(parent_step) {}

    // access element
    T& operator()(size_t row, size_t col) {
        assert(row < dim && col < dim); 
        return view_ptr[row * step + col];
    }
    T operator()(size_t row, size_t col) const {
        assert(row < dim && col < dim);
        return view_ptr[row * step + col];
    }

    // getter for dimension
    size_t getDim() const {
        return dim;
    }

    // submatrix creation
    Matrix<T> submatrix(size_t start_r, size_t start_c, size_t new_size) const {
        assert(start_r < dim && start_c < dim);
        return Matrix<T>(view_ptr + start_r * step + start_c, new_size, step);
    }

    // copies matrix
    Matrix copy() const {
        Matrix<T> copied(dim);  // Create a new matrix with the same dimension
        for (size_t i = 0; i < dim; ++i) {
            for (size_t j = 0; j < dim; ++j) {
                copied(i, j) = (*this)(i, j);  // Copy each element
            }
        }
        return copied;
    }
};

// addition and subtraction by creating new matrix
template<typename T>
Matrix<T> matrix_add(const Matrix<T>& A, const Matrix<T>& B) { 
    assert(A.getDim() == B.getDim());
    size_t n = A.getDim();
    Matrix<T> result(n);
    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < n; ++j) {
            result(i, j) = A(i, j) + B(i, j);
        }
    }
    return result;
}
template<typename T>
Matrix<T> matrix_sub(const Matrix<T>& A, const Matrix<T>& B) { 
    assert(A.getDim() == B.getDim());
    size_t n = A.getDim();
    Matrix<T> result(n);
    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < n; ++j) {
            result(i, j) = A(i, j) - B(i, j);
        }
    }
    return result;
}

// addition and subtraction straight into matrix target
template<typename T>
void matrix_add_inplace(const Matrix<T>& A, const Matrix<T>& B, Matrix<T>& Target) { 
    // assert(A.getDim() == B.getDim() == Target.getDim());
    size_t n = A.getDim();
    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < n; ++j) {
            Target(i, j) = A(i, j) + B(i, j);
        }
    }
}

template<typename T>
void matrix_sub_inplace(const Matrix<T>& A, const Matrix<T>& B, Matrix<T>& Target) { 
    // assert(A.getDim() == B.getDim() == Target.getDim());
    size_t n = A.getDim();
    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < n; ++j) {
            Target(i, j) = A(i, j) - B(i, j);
        }
    }
}

// copy matrix A to target
template<typename T>
void matrix_inplace(const Matrix<T>& A, Matrix<T>& Target) {
    assert(A.getDim() == Target.getDim());
    size_t n = A.getDim();
    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < n; ++j) {
            Target(i, j) = A(i, j);
        }
    }
}

template<typename T> 
Matrix<T> matrix_mult(const Matrix<T>& A, const Matrix<T>& B) {
    assert(A.getDim() == B.getDim());
    size_t n = A.getDim();
    Matrix<T> result(n);

    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < n; ++j) {
            T sum = T(); // Initialize sum to 0 
            for(size_t k = 0; k < n; ++k) {
                sum += A(i, k) * B(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
}
// same as above but directly into Target
template<typename T> 
void matrix_mult_in_place(const Matrix<T>& A, const Matrix<T>& B, Matrix<T>& Target) {
    // assert(A.getDim() == B.getDim() == Target.getDim());
    size_t n = A.getDim();

    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < n; ++j) {
            T sum = T(); // Initialize sum to 0 
            for(size_t k = 0; k < n; ++k) {
                sum += A(i, k) * B(k, j);
            }
            Target(i, j) = sum;
        }
    }
    return;
}

// prints matrix up to dim values
template<typename T> 
void print_matrix(const Matrix<T>& A, size_t dim) {
    for (size_t i = 0; i < dim; ++i) {
        for (size_t j = 0; j < dim; ++j) {
            std::cout << A(i, j);
        }
        std::cout << "\n";
    }
    std::cout << "\n" << std::endl;
}


// Generates a random matrix
// randomization_type flag controls number selection for each entry:
// 0: 0 or 1
// 1: 0, 1, or 2
// 2: -1, 0, or 1
template<typename T>
Matrix<T> generate_random_matrix(size_t n, int randomization_type = 0) {
    Matrix<T> m(n);
    std::random_device rd;
    std::mt19937 gen(rd());

    switch (randomization_type) {
        case 0: {
            std::uniform_int_distribution<int> dis(0, 1);
            for (size_t i = 0; i < n; ++i) {
                for (size_t j = 0; j < n; ++j) {
                    m(i, j) = static_cast<T>(dis(gen));
                }
            }
        }
        case 1: {
            std::uniform_int_distribution<int> dis(0, 2);
            for (size_t i = 0; i < n; ++i) {
                for (size_t j = 0; j < n; ++j) {
                    m(i, j) = static_cast<T>(dis(gen));
                }
            }
        }
        case 2: {
            std::uniform_int_distribution<int> dis(-1, 1);
            for (size_t i = 0; i < n; ++i) {
                for (size_t j = 0; j < n; ++j) {
                    m(i, j) = static_cast<T>(dis(gen));
                }
            }
        }
    }



    return m;
}


#endif // MATRIX_HPP