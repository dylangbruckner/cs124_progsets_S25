#include <iostream>
#include <fstream>
#include "experiments.hpp"

// flag:
// 0 normal operations (as defined in progset description)
// 1 expirement 
// 2+ unused

const size_t MAX_ITER = 25000;
const size_t INPUT_SIZE = 100;
const size_t NUM_TRIALS = 50;

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

        if (!file.is_open() && flag != 1) {
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
                std::cout << karmarkar_karp(input) << std::endl; 
                break;
            case 1:
                std::cout << repeated_random(input, MAX_ITER, false) << std::endl;
                break;
            case 2:
                std::cout << hill_climbing(input, MAX_ITER, false) << std::endl;
                break;
            case 3:
                std::cout << simulated_annealing(input, MAX_ITER, false) << std::endl;
                break;
            case 11:
                std::cout << repeated_random(input, MAX_ITER, true) << std::endl;
                break;
            case 12:
                std::cout << hill_climbing(input, MAX_ITER, true) << std::endl;
                break;
            case 13:
                std::cout << simulated_annealing(input, MAX_ITER, true) << std::endl;
                break;
            default:
                std::cerr << "Error: Algorithm type not recognized";
                return 1;
            return 0;
        }
    } else if (flag == 1) { // experiments
        std::vector<uint64_t> residues = experiments(INPUT_SIZE, NUM_TRIALS, MAX_ITER);

        std::cout << "Residues from experiments:" << std::endl;
        std::cout << "karmarkar: " << residues[0] << std::endl;
        std::cout << "repeated: " << residues[1] << std::endl;
        std::cout << "r-prepar: " << residues[2] << std::endl;
        std::cout << "climbing: " << residues[3] << std::endl;
        std::cout << "c-prepar: " << residues[4] << std::endl;
        std::cout << "annealing: " << residues[5] << std::endl;
        std::cout << "a-prepar: " << residues[6] << std::endl;

    } else {
        std::cerr << "Flag \"" << flag << "\" not recognized"; 
        return 1;       
    }
}