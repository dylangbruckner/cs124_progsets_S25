#include <iostream>
#include <vector>
#include <random>

std::vector<int> repeatedRandom(const std::vector<size_t>& input, const size_t& max_iter) {
    size_t n = input.size();

    std::vector<int> S = generateRandom(n);

    for (size_t i = 0; i < max_iter; ++i) {
        std::vector<int> temp = generateRandom(n);
        
        if (calculateResidue(input, temp, n) < calculateResidue(input, S, n)) {
            S = temp;
        }
    }

    return S;
}

std::vector<int> generateRandom(const size_t& n) {
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

int calculateResidue(const std::vector<size_t>& original, const std::vector<int>& S, const size_t& n) {
    int residue = 0;

    for (size_t i = 0; i < n; ++i) {
        residue += original[i] * S[i];
    }

    return residue;
}