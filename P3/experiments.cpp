#include "experiments.hpp"

std::vector<int64_t> problemInstance(const size_t& n) {
    std::random_device rd;
    std::mt19937 gen(rd());

    int64_t lower_bound = 1;
    int64_t upper_bound = 1000000000000ULL;

    std::uniform_int_distribution<int64_t> dist(lower_bound, upper_bound) ;
    
    // For testing purposes, keep track of a variable to see what largest generated number is to test uniform function
    int64_t max_num = 0;

    std::vector<int64_t> output(n);

    for (size_t i = 0; i < n; ++i) {
        output[i] = dist(gen);
        if (output[i] > max_num) {
            max_num = output[i];
        }
    }

    return output;
}

std::vector<uint64_t> experiments(const size_t n, const size_t num_trials, const size_t max_iter) {
    std::vector<uint64_t> output(7);

    for (size_t i = 0; i < num_trials; ++i) {
        std::vector<int64_t> problem = problemInstance(n);
        // Run KK
        output[0] += karmarkar_karp(problem) * (1 / num_trials);

        // Run repeated random
        output[1] += repeated_random(problem, max_iter, false) * (1 / num_trials);
        output[2] += repeated_random(problem, max_iter, true) * (1 / num_trials);

        // Run hill climbing
        output[3] += hill_climbing(problem, max_iter, false) * (1 / num_trials);
        output[4] += hill_climbing(problem, max_iter, true) * (1 / num_trials);

        // Run simulatd annealing
        output[5] += simulated_annealing(problem, max_iter, false) * (1 / num_trials);
        output[6] += simulated_annealing(problem, max_iter, true) * (1 / num_trials);
    }
    // Output it all 
    return output;
}