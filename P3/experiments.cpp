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
        output[0] += karmarkar_karp(problem);

        // Run repeated random
        output[1] += repeated_random(problem, max_iter, false);
        output[2] += repeated_random(problem, max_iter, true);

        // Run hill climbing
        output[3] += hill_climbing(problem, max_iter, false);
        output[4] += hill_climbing(problem, max_iter, true);

        // Run simulatd annealing
        output[5] += simulated_annealing(problem, max_iter, false);
        output[6] += simulated_annealing(problem, max_iter, true);
    }

    for (size_t i = 0; i < 7; ++i) {
        output[i] = output[i] / num_trials;
    }
    // Output it all 
    return output;
}

std::vector<uint64_t> experiment_times(const size_t n, const size_t num_trials, const size_t max_iter) {
    std::vector<uint64_t> output(7); // This will now store total time for each algorithm in microseconds

    for (size_t i = 0; i < num_trials; ++i) {
        std::vector<int64_t> problem = problemInstance(n);

        // Karmarkar-Karp timing
        auto start = std::chrono::high_resolution_clock::now();
        karmarkar_karp(problem);
        auto end = std::chrono::high_resolution_clock::now();
        output[0] += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // Repeated Random (no prepartition)
        start = std::chrono::high_resolution_clock::now();
        repeated_random(problem, max_iter, false);
        end = std::chrono::high_resolution_clock::now();
        output[1] += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // Repeated Random (prepartition)
        start = std::chrono::high_resolution_clock::now();
        repeated_random(problem, max_iter, true);
        end = std::chrono::high_resolution_clock::now();
        output[2] += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // Hill Climbing (no prepartition)
        start = std::chrono::high_resolution_clock::now();
        hill_climbing(problem, max_iter, false);
        end = std::chrono::high_resolution_clock::now();
        output[3] += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // Hill Climbing (prepartition)
        start = std::chrono::high_resolution_clock::now();
        hill_climbing(problem, max_iter, true);
        end = std::chrono::high_resolution_clock::now();
        output[4] += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // Simulated Annealing (no prepartition)
        start = std::chrono::high_resolution_clock::now();
        simulated_annealing(problem, max_iter, false);
        end = std::chrono::high_resolution_clock::now();
        output[5] += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // Simulated Annealing (prepartition)
        start = std::chrono::high_resolution_clock::now();
        simulated_annealing(problem, max_iter, true);
        end = std::chrono::high_resolution_clock::now();
        output[6] += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }

    // Take the average over all trials
    for (size_t i = 0; i < 7; ++i) {
        output[i] /= num_trials;
    }

    return output;
}