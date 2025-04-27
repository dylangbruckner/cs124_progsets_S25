#include "repeated.hpp"

std::uint64_t repeated_random(std::vector<std::int64_t>& input, const size_t max_iter, const bool prepartitioned) {
    size_t n = input.size();
    if (prepartitioned) {
        std::vector<size_t> S = generate_random_prepartition(n);
        std::vector<size_t> temp;

        for (size_t i = 0; i < max_iter; ++i) {
            temp = generate_random_prepartition(n);

            if (calculate_residue_partition(input, temp) < calculate_residue_partition(input, S)) {
                S = temp;
            }
        }

    } else {
        std::vector<int> S = generateRandom(n);
        std::vector<int> temp;

        for (size_t i = 0; i < max_iter; ++i) {
            temp = generateRandom(n);
            
            if (calculate_residue_unsigned(input, temp) < calculate_residue_unsigned(input, S)) {
                S = temp;
            }
        }

        return calculate_residue_unsigned(input, S);
    }
}

std::vector<int> generateRandom(const size_t n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution dist(0.5);

    std::vector<int> output(n);

    for (size_t i = 0; i < n; ++i) {
        int randomValue = dist(gen) ? 1 : -1;
        output[i] = randomValue;
    }

    return output;
}

std::vector<size_t> generate_random_prepartition(const size_t n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(1, n); 

    std::vector<size_t> output(n);

    for (size_t i = 0; i < n; ++i) {
        output[i] = dist(gen);
    }

    return output;
}

std::int64_t calculate_residue_signed(const std::vector<std::int64_t>& original, const std::vector<int>& S) {
    std::int64_t residue = 0;
    size_t n = original.size();

    for (size_t i = 0; i < n; ++i) {
        residue += original[i] * S[i];
    }
    
    return residue;
}

std::uint64_t calculate_residue_unsigned(const std::vector<std::int64_t>& original, const std::vector<int>& S) {
    return abs_value_64(calculate_residue_signed(original, S));
}

std::uint64_t calculate_residue_partition(const std::vector<std::int64_t>& original, const std::vector<size_t>& P) {
    size_t n = original.size();
    std::vector<std::int64_t> A_prime(n);

    for (size_t j = 0; j < n; ++j) {
        A_prime[P[j]] = A_prime[P[j]] + original[j];
    }

    return karmarkar_karp(A_prime);
}
