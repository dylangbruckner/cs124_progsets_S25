#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <cassert>

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
        assert(row < dim && col < dim && row >= 0 && col >= 0); 
        return view_ptr[row * step + col];
    }

    // getter for dimension
    size_t getDim() const {
        return dim;
    }

    // submatrix creation
    Matrix<T> submatrix(size_t start_r, size_t start_c, size_t new_size) const {
        assert(start_r < dim && start_c < dim && start_r >= 0 && start_c >= 0);
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

template<typename T>
Matrix<T> matrix_add(const Matrix<T>& A, const Matrix<T>& B) {  // Add const
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
Matrix<T> matrix_sub(const Matrix<T>& A, const Matrix<T>& B) {  // Add const
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

template<typename T> 
Matrix<T> matrix_mult(const Matrix<T>& A, const Matrix<T>& B) {
    assert(A.getDim() == B.getDim());
    size_t n = A.getDim();
    Matrix<T> result(n);

    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < n, ++j) {
            T sum = T(); // Initialize sum to 0 
            for(size_t k = 0; k < n, ++k) {
                sum += A(i, k) * B(k, j);
            }
            result(i, j) = sum;
        }
    }
}

#endif // MATRIX_HPP