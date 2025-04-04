#include "triangle.hpp"
#include "matrix.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include "experiments.cpp"

// first argument
// 0 - reserved for autograder test
// 1 - reserved for various testing
// 2 - reserved for experimenting cutoff
// 5 - reserved for triagnle


int main(int argc, char** argv) {

    // make sure we have correct args
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <flag> <dimension> <inputfile>\n";
        return 1;
    }
    int custom = std::stoi(argv[1]);
    if (custom == 0 && argc < 4) {
        std::cout << "Not enough arguments provided" << std::endl;
        return 1;
    } 

    // autograder test
    if (custom == 0) {
        std::ifstream file(argv[3]);
        size_t dim = std::stoi(argv[2]);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << argv[3] << ".\n";
            return 1;
        }

        // fill matrices A and B
        size_t padded_size = padding_calc(dim);
        Matrix<int> A(padded_size);
        Matrix<int> B(padded_size);
        

        for (size_t i = 0; i < padded_size; ++i) {
            for (size_t j = 0; j < padded_size; ++j) {
                // add padding or add element from file
                if (i >= dim || j >= dim) {
                    A(i, j) = 0;
                } else if (!(file >> A(i, j))) throw std::runtime_error("Invalid input file");
            }
        }
        for (size_t i = 0; i < padded_size; ++i) {
            for (size_t j = 0; j < padded_size; ++j) {
                if (i >= dim || j >= dim) {
                    B(i, j) = 0;
                } else if (!(file >> B(i, j))) throw std::runtime_error("Invalid input file");
            }
        }

        Matrix<int> prod = strassen_mult_init(A, B);
        for (size_t i = 0; i < dim; ++i) {
            std::cout << prod(i, i) << "\n";
        }
    } else if (custom == 1) { // testing
        size_t MATRIX_SIZE = 5;
        int MATRIX_VAL = 1;

        size_t padded_size = padding_calc(MATRIX_SIZE);
        Matrix<int> A(padded_size);
        Matrix<int> B(padded_size);
        

        for (size_t i = 0; i < padded_size; ++i) {
            for (size_t j = 0; j < padded_size; ++j) {
                // add padding or add element from file
                if (i >= MATRIX_SIZE || j >= MATRIX_SIZE) {
                    A(i, j) = 0;
                } else A(i, j) = MATRIX_VAL;
                std::cout << A(i, j);
            }
            std::cout << "\n";
        }
        for (size_t i = 0; i < padded_size; ++i) {
            for (size_t j = 0; j < padded_size; ++j) {
                if (i >= MATRIX_SIZE || j >= MATRIX_SIZE) {
                    B(i, j) = 0;
                } else B(i, j) = MATRIX_VAL;
                std::cout << B(i, j);
            }
            std::cout << "\n";
        }
        Matrix<int> C = strassen_mult_init(A, B);
        print_matrix(C, MATRIX_SIZE);
        Matrix<int> D = matrix_mult(A, B);
        print_matrix(D, MATRIX_SIZE);
     
    } else if (custom == 2) { // Testing experimental crossover
        experiments();
    } else if (custom == 5) { // triangles
        for (int i = 1; i < 6; ++i) {
            std::cout << "probability of edge: " << CURR_PROB * i << "\n";
            std::cout << "average triangles: " << count_triangles(STANDARD_DIM, CURR_PROB * i, NUM_TRIALS) << "\n";
            std::cout << "expected average: " << N10224_CHOOSE_3 * pow(CURR_PROB * i, 3) << "\n" << "\n";
        }
        std::cout << std::endl;
    }
}

