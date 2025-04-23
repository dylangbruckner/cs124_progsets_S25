#include "repeated.hpp"

std::vector<int> repeatedRandom(const std::vector<std::int64_t>& input, const size_t max_iter) {
    size_t n = input.size();

    std::vector<int> S = generateRandom(n);

    for (size_t i = 0; i < max_iter; ++i) {
        std::vector<int> temp = generateRandom(n);
        
        if (calculateResidue(input, temp) < calculateResidue(input, S)) {
            S = temp;
        }
    }

    // TODO: return residue?
    return S;
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

std::uint64_t calculateResidue(const std::vector<std::int64_t>& original, const std::vector<int>& S) {
    std::int64_t residue = 0;
    size_t n = original.size();

    for (size_t i = 0; i < n; ++i) {
        residue += original[i] * S[i];
    }
    
    if (residue == std::numeric_limits<std::int64_t>::min()) {
        return static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max()) + 1;
    }
    return static_cast<std::uint64_t>(std::abs(residue));
}