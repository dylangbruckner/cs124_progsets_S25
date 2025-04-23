#include "annealing.hpp"

std::uint64_t simulated_annealing(const std::vector<std::int64_t>& input, const size_t max_iter, const bool prepartitioned) {
    size_t n = input.size();

    // random generators for moves 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> real(0.0, 1.0);
    std::uniform_int_distribution<size_t> dist(1, n);
    
    if (prepartitioned) {
        // todo but i'm lazy
    } else {
        
        // generate random solution
        std::vector<int> S = generateRandom(n);
        std::uint64_t residue = calculate_residue_unsigned(input, S);

        // return 0 if our residue is already minimized
        if (!residue) {
            return 0;        
        }

        std::uint64_t best_residue = residue;
        std::uint64_t temp_residue;
        size_t j;
        size_t k;
        float flip;

        

        // iterate through generating a random move each time
        for (size_t i = 0; i < max_iter; ++i) {
            temp_residue = residue;
            j = dist(gen);

            // flip j's group, adding/subing j twice, once to remove from old group and once to add to new group
            temp_residue += input[j] * S[j] * 2;

            // with 1/2 probability flip another index
            flip = real(gen);
            if (flip > 0.5) {
                
                // get a new random index
                do {
                    k = dist(gen);
                } while (k == j);

                // flip k 
                temp_residue += input[k] * S[k] * 2;
            }

            // new residue is smaller or random condition is met
            if ((temp_residue < residue && residue > 0) 
             || (temp_residue > residue && residue > 0)
             || (real(gen) < exp((abs_value_64(residue)-abs_value_64(temp_residue))/T(i)))) {
                
                // is 0, it is minimized and thus return early
                if (!temp_residue) {
                    return 0;
                }
                
                // adjust new optimal solution
                S[j] = -S[j];
                if (flip > 0.5) S[k] = -S[k];
                residue = temp_residue;

                // update best_residue if necessary
                if (residue < best_residue) best_residue = residue;

            }
        }

        return abs_value_64(best_residue);
    }
}

inline double T(size_t iter) {
    const std::size_t expon = iter / 300;
    return 1e10 * std::pow(0.8, static_cast<double>(expon));
}
