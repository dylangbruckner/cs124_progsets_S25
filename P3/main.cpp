
#include <iostream>
#include <fstream>
#include "annealing.hpp"
#include "karmakar.hpp"
#include "hill.hpp"

// flag:
// 0 normal operations (as defined in progset description)
// 1 expirement 
// 2+ unused

const size_t MAX_ITER = 25000;

int main(int argc, char** argv) {
    // make sure we have correct args
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <flag> <algorithm> <inputfile>\n";
        return 1;
    }

    int flag = std::stoi(argv[1]);

    
    if (!flag) { // normal operations

        if (argc != 4) {
            std::cerr << "Usage: " << argv[0] << " <flag> <algorithm> <inputfile>\n";
            return 1;
        }

        // get other args
        int algo = std::stoi(argv[2]);
        std::ifstream file(argv[3]);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << argv[3] << ".\n";
            return 1;
        }

        // get input numbers
        std::vector<std::int64_t> input;
        std::int64_t num;

        while (file >> num) {
            input.push_back(num);
        }

        switch (algo) {
            case 0:
                std::cout << karmarkar_karp(input); 
            case 1:
                std::cout << repeated_random(input, MAX_ITER, false);
            case 2:
                std::cout << hill_climbing(input, MAX_ITER, false);
            case 3:
                std::cout << simulated_annealing(input, MAX_ITER, false);
            case 11:
                std::cout << repeated_random(input, MAX_ITER, true);
            case 12:
                std::cout << hill_climbing(input, MAX_ITER, true);
            case 13:
                std::cout << simulated_annealing(input, MAX_ITER, true);
            default:
                std::cerr << "Error: Algorithm type not recognized";
                return 1;
            std::cout << std::endl;
            return 0;
        }
    } else if (flag == 1) { // experiments




    } else {
        std::cerr << "Flag \"" << flag << "\" not recognized"; 
        return 1;       
    }
}