#include "triangle.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// first argument
// 0 - reserved for autograder test
// 5 - reserved for triagnle


int main(int argc, char** argv) {

    // make sure we have correct args
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <flag> <dimension> <inputfile>\n";
        return 1;
    }
    int custom = std::stoi(argv[1]);
    if (custom != 0 && argc < 4) {
        std::cout << "Not enough arguments provided" << std::endl;
        return 1;
    }

    
    int dim = std::stoi(argv[2]);

    // autograder test
    if (custom == 0) {
        std::ifstream file(argv[3]);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << argv[3] << ".\n";
            return 1;
        }

        // fill matrices A and B
        Matrix<int> A(dim);
        Matrix<int> B(dim);

        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                if (!(file >> A(i, j))) throw std::runtime_error("Invalid input file");
            }
        }
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                if (!(file >> B(i, j))) throw std::runtime_error("Invalid input file");
            }
        }

        Matrix<int> prod = strassen_mult(A, B);
        for (int i = 0; i < dim; ++i) {
            std::cout << prod(i, i) << "\n";
        }
    }

    // triangle 
    if (custom == 5) {
        std::cout << "average triangles: " << count_triangles(STANDARD_DIM, CURR_PROB, NUM_TRIALS) << std::endl;
        std::cout << "expected average: " << N10224_CHOOSE_3 << std::endl;
    }


}

