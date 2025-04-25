#include "hill.hpp"

std::uint64_t hill_climbing(const std::vector<std::int64_t>& input, const size_t max_iter, const bool prepartitioned) {
    size_t n = input.size();

    // random generators for moves 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> real(0.0, 1.0);
    std::uniform_int_distribution<size_t> dist(1, n);
    
    // early decleratoins
    size_t j;
    size_t k = 0;
    
    if (prepartitioned) {
        // generate random solution
        std::vector<size_t> P = generate_random_prepartition(n);
        std::uint64_t residue = calculate_residue_partition(input, P);
        std::uint64_t temp_residue;
        size_t old;

        // return 0 if our residue is already minimized
        if (!residue) {
            return 0;        
        }

        // iterate through generating a random move each time
        for (size_t i = 0; i < max_iter; ++i) {
            
            j = dist(gen);
            old = P[j];

            do {
                k = dist(gen);
            } while (k == old);

            // calculate new partition
            P[j] = k;
            temp_residue = calculate_residue_partition(input, P);

            // new residue is smaller
            if (temp_residue < residue) {
                
                // is 0, it is minimized and thus return early
                if (!temp_residue) {
                    return 0;
                }
                
                // adjust new optimal solution
                residue = temp_residue;

            } else P[j] = old; // otherwise reset value of P
        }

        return residue;
    } else {
        
        // generate random solution
        std::vector<int> S = generateRandom(n);
        // keep residue insigned for simplification of calculations
        std::int64_t residue = calculate_residue_signed(input, S);

        // return 0 if our residue is already minimized
        if (!residue) {
            return 0;        
        }

        std::int64_t temp_residue;
        std::uint64_t abs_residue = abs_value_64(residue);
        float flip;

        // iterate through generating a random move each time
        for (size_t i = 0; i < max_iter; ++i) {
            j = dist(gen);

            // flip j's group, adding/subing j twice, once to remove from old group and once to add to new group
            temp_residue = residue - input[j] * S[j] * 2;

            // with 1/2 probability flip another index
            flip = real(gen);
            if (flip > 0.5) {
                
                // get a new random index
                do {
                    k = dist(gen);
                } while (k == j);

                // flip k 
                temp_residue -= input[k] * S[k] * 2;
            }

            // new residue is smaller
            if (abs_value_64(temp_residue) < abs_residue) {
                
                // is 0, it is minimized and thus return early
                if (!temp_residue) {
                    return 0;
                }
                
                // adjust new optimal solution
                S[j] = -S[j];
                if (flip > 0.5) S[k] = -S[k];
                residue = temp_residue;
                abs_residue = abs_value_64(temp_residue);
            }
        }

        return abs_value_64(residue);
    }
}