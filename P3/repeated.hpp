#ifndef REPEATED_HPP
#define REPEATED_HPP

#include <random>
#include "karmakar.hpp"

// generateRandom
//  generates a random conventional solution of size 'n' in the form specified by the progset documentation
//  returns a vector containing of elements -1 or 1 pertaining to the two groups
std::vector<int> generateRandom(const size_t n);

// generate_random_prepartition
//   generates a random prepartition solution of size 'n' in the form specified by the progset documentation
//   returns this vector
std::vector<size_t> generate_random_prepartition(const size_t n);

// todo make this function match the one in .cpp
// repeated_random
//  runs the repeated_random algorithm for max_iter times on input nums
//  prepartitioned is true if the solution should use a prepartitioned solution
//  returns the residue
std::uint64_t repeated_random(std::vector<std::int64_t>& input, const size_t max_iter, const bool prepartitioned);

// calculateResidue
//  calculates the residue of numbers original with assignment S
std::uint64_t calculateResidue(const std::vector<std::int64_t>& original, const std::vector<int>& S);

#endif // REPEATED_HPP
