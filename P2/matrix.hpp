#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>
#include <cmath>
#include <random>

size_t padding_calc(size_t dim);
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
        return view_ptr[row * step + col];
    }
    T operator()(size_t row, size_t col) const {
        return view_ptr[row * step + col];
    }

    // getter for dimension
    size_t getDim() const {
        return dim;
    }

    // submatrix creation
    Matrix<T> submatrix(size_t start_r, size_t start_c, size_t new_size) const {
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
    size_t n = A.getDim();
    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < n; ++j) {
            Target(i, j) = A(i, j);
        }
    }
}

template<typename T> 
Matrix<T> matrix_mult(const Matrix<T>& A, const Matrix<T>& B) {
    size_t n = A.getDim();
    Matrix<T> result(n);

    for(size_t i = 0; i < n; ++i) {
        // Initialize result(i, j)
        for(size_t j = 0; j < n; ++j) {
            result(i, j) = T();
        }

        // Loop through w/ optimized caching
        for(size_t k = 0; k < n; ++k) {
            T Aik = A(i, k);
            for(size_t j = 0; j < n; ++j) {
                result(i, j) += Aik * B(k, j);
            }
        }
    }
    return result;
}

template<typename T> 
Matrix<T> matrix_mult_old(const Matrix<T>& A, const Matrix<T>& B) {
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
        // Initialize values
        for (size_t j = 0; j < n; ++j) {
            Target(i, j) = T();
        }

        // Loop through w/ optimized caching
        for(size_t k = 0; k < n; ++k) {
            T Aik = A(i, k); // Cache A(i, k)
            for(size_t j = 0; j < n; ++j) {
                Target(i, j) += Aik * B(k, j);
            }
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
     // Create padded size
    size_t padded_size = padding_calc(n);
    Matrix<T> m(padded_size);
   
    std::random_device rd;
    std::mt19937 gen(rd());

    switch (randomization_type) {
        case 0: {
            std::uniform_int_distribution<int> dis(0, 1);
            for (size_t i = 0; i < n; ++i) {
                for (size_t j = 0; j < n; ++j) {
                    if (i >= n || j >= n)
                        m(i, j) = 0;
                    else
                        m(i, j) = static_cast<T>(dis(gen));
                }
            }
        }
        case 1: {
            std::uniform_int_distribution<int> dis(0, 2);
            for (size_t i = 0; i < n; ++i) {
                for (size_t j = 0; j < n; ++j) {
                    if (i >= n || j >= n)
                        m(i, j) = 0;
                    else
                        m(i, j) = static_cast<T>(dis(gen));
                }
            }
        }
        case 2: {
            std::uniform_int_distribution<int> dis(-1, 1);
            for (size_t i = 0; i < n; ++i) {
                for (size_t j = 0; j < n; ++j) {
                    if (i >= n || j >= n)
                        m(i, j) = 0;
                    else
                        m(i, j) = static_cast<T>(dis(gen));
                }
            }
        }
    }



    return m;
}

template<typename T>
Matrix<T> generate_random_matrix_pad(size_t n, int randomization_type = 0) {
     // Create padded size
    size_t padded_size = padding_calc(n);
    Matrix<T> m(padded_size);
   
    std::random_device rd;
    std::mt19937 gen(rd());

    switch (randomization_type) {
        case 0: {
            std::uniform_int_distribution<int> dis(0, 1);
            for (size_t i = 0; i < padded_size; ++i) {
                for (size_t j = 0; j < padded_size; ++j) {
                    if (i >= n || j >= n)
                        m(i, j) = 0;
                    else
                        m(i, j) = static_cast<T>(dis(gen));
                }
            }
        }
        case 1: {
            std::uniform_int_distribution<int> dis(0, 2);
            for (size_t i = 0; i < padded_size; ++i) {
                for (size_t j = 0; j < padded_size; ++j) {
                    if (i >= n || j >= n)
                        m(i, j) = 0;
                    else
                        m(i, j) = static_cast<T>(dis(gen));
                }
            }
        }
        case 2: {
            std::uniform_int_distribution<int> dis(-1, 1);
            for (size_t i = 0; i < padded_size; ++i) {
                for (size_t j = 0; j < padded_size; ++j) {
                    if (i >= n || j >= n)
                        m(i, j) = 0;
                    else
                        m(i, j) = static_cast<T>(dis(gen));
                }
            }
        }
    }



    return m;
}

#endif // MATRIX_HPP