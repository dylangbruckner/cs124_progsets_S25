#include "hill.hpp"

std::uint64_t hill_climbing(const std::vector<std::int64_t>& input, const size_t max_iter, const bool prepartitioned) {
    size_t n = input.size();

    // random generators for moves 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution extra(0.5);
    std::uniform_int_distribution<size_t> dist(1, n);
    
    if (prepartitioned) {
        // todo but i'm lazy
    } else {
        
        // generate random solution
        std::vector<int> S = generateRandom(n);
        std::uint64_t residue = calculate_residue_unsigned(input, S);
        std::uint64_t temp_residue;
        size_t j;
        size_t k;
        bool flip;

        // return 0 if our residue is already minimized
        if (!residue) {
            return 0;        
        }

        // iterate through generating a random move each time
        for (size_t i = 0; i < max_iter; ++i) {
            temp_residue = residue;
            j = dist(gen);

            // flip j's group, adding/subing j twice, once to remove from old group and once to add to new group
            temp_residue += input[j] * S[j] * 2;

            // with 1/2 probability flip another index
            flip = extra(gen);
            if (flip) {
                
                // get a new random index
                do {
                    k = dist(gen);
                } while (k == j);

                // flip k 
                temp_residue += input[k] * S[k] * 2;
            }

            // new residue is smaller
            if ((temp_residue < residue && residue > 0) || (temp_residue > residue && residue > 0)) {
                
                // is 0, it is minimized and thus return early
                if (!temp_residue) {
                    return 0;
                }
                
                // adjust new optimal solution
                S[j] = -S[j];
                if (flip) S[k] = -S[k];
                residue = temp_residue;
            }
        }

        return abs_value_64(residue);
    }
}