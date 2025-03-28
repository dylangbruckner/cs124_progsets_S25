#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

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
        view_ptr(base), dim(sub_size), step(parent_step) {}

    // access element
    T& operator()(size_t row, size_t col) {
        assert(row < dim && col < dim && row >= 0 && col >= 0); 
        return view_ptr[row * step + col];
    }

    // submatrix creation
    Matrix submatrix(size_t start_r, size_t start_c, size_t new_size) {
        assert(start_r + new_size < dim && start_c + new_size < dim
               && start_r >= 0 && start_c >= 0); 

        return Matrix(view_ptr + start_r * step + start_c, new_size, step);
    }
};

#endif // MATRIX_HPP