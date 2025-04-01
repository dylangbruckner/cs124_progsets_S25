#include "matrix.hpp"
#include "strassens.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <chrono>
#include <compare>

void experiments() {
    size_t testDim = 2;
    for (int i = 0; i < 12; ++i) {
        testDim = (testDim * 2);
        for (int j = 0; j < 3; ++j) {
            Matrix<int> testMatrix1 = generate_random_matrix_pad<int>(testDim, j);
            Matrix<int> testMatrix2 = generate_random_matrix_pad<int>(testDim, j);
    
            auto start = std::chrono::high_resolution_clock::now();
            auto res = matrix_mult(testMatrix1, testMatrix2);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            printf("Matrix %d w/ dim %u using normal mult: %lf\n", j, testDim, duration);
    
            start = std::chrono::high_resolution_clock::now();
            res = strassen_mult_init(testMatrix1, testMatrix2);
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            printf("Matrix %d w/ dim %u using   strassens: %lf\n\n\n", j, testDim, duration);
        }
        printf("------------------------------------------------\n\n\n");
    }

    // Normal Matrix Mult Testing
    // size_t testDim = 2;
    // for (int i = 0; i < 11; ++i) {
    //     testDim = testDim * 2;
    //     for (int j = 0; j < 3; ++j) {
    //         Matrix<int> testMatrix1 = generate_random_matrix<int>(testDim, j);
    //         Matrix<int> testMatrix2 = generate_random_matrix<int>(testDim, j);
    
    //         auto start = std::chrono::high_resolution_clock::now();
    //         auto res1 = matrix_mult(testMatrix1, testMatrix2);
    //         auto end = std::chrono::high_resolution_clock::now();
    //         std::chrono::duration<double> duration = end - start;
    //         printf("Matrix %d w/ dim %u using new mult: %lf\n", j, testDim, duration);
    
    //         start = std::chrono::high_resolution_clock::now();
    //         auto res2 = matrix_mult_old(testMatrix1, testMatrix2);
    //         end = std::chrono::high_resolution_clock::now();
    //         duration = end - start;
    //         printf("Matrix %d w/ dim %u using old mult: %lf\n\n\n", j, testDim, duration);
    //     }
        
    //     printf("------------------------------------------------\n\n\n");
    // }
}


