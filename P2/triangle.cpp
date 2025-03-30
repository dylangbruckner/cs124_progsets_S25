#include "triangle.hpp"

Matrix<int> generate_random_graph(size_t dim, float probability) {
    Matrix<int> M1(dim);

    // set up RNG 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(0.0, 1.0);

    for (size_t i = 0; i < dim; ++i) {
        for (size_t j = 0; j < dim; ++j) {
            if (distrib(gen) <= probability){
                M1(i, j) = 1;
            } else {
                M1(i, j) = 0;
            }
        }
    }

    return M1;
}

float count_triangles(size_t dim, float probability, size_t trials) {
    float count = 0.;   // total triangles across all trials

    for (size_t i = 0; i < trials; ++i) {
        const Matrix<int> M1 = generate_random_graph(dim, probability);
        const Matrix<int> M2 = M1.copy();
        const Matrix<int> M3 = M1.copy();

        Matrix<int> A3 = strassen_mult(M1, strassen_mult(M2, M3));

        for (size_t j = 0; j < dim; ++j) {
            count += A3(j, j);
        }
    }

    return (count / trials) / 6;
}