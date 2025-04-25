#include "experiments.hpp"

// todo fill out the hpp file for this 

std::vector<size_t> problemInstance(const size_t& n) {
    std::random_device rd;
    std::mt19937 gen(rd());

    size_t lower_bound = 1;
    size_t upper_bound = 1000000000000ULL;

    std::uniform_int_distribution<size_t> dist(lower_bound, upper_bound) ;
    
    // For testing purposes, keep track of a variable to see what largest generated number is to test uniform function
    size_t max_num = 0;

    std::vector<size_t> output(n);

    for (size_t i = 0; i < n; ++i) {
        output[i] = dist(gen);
        if (output[i] > max_num) {
            max_num = output[i];
        }
    }

    return output;
}

std::vector<size_t> experiments(const size_t n, const size_t num_trials, const size_t max_iter) {
    std::vector<std::vector<size_t>> output(num_trials, std::vector<size_t>(4, 0));

    for (size_t i = 0; i < num_trials; ++i) {
        std::vector<size_t> problem = problemInstance(n);
        
        // Run KK

        // Run repeated random

        // Run hill climbing

        // Run simulatd annealing
    }
    // Output it all 

    // this is temporary
    std::vector<size_t> empty(0);
    return empty;
}