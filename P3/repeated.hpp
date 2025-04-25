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

// repeated_random
//  runs the repeated_random algorithm for max_iter times on input nums
//  prepartitioned is true if the solution should use a prepartitioned solution
//  returns the residue
std::uint64_t repeated_random(std::vector<std::int64_t>& input, const size_t max_iter, const bool prepartitioned);

// caclulate_residue (signed and unsigned version)
//  calculates the residue of numbers original with assignment S
std::int64_t calculate_residue_signed(const std::vector<std::int64_t>& original, const std::vector<int>& S);
std::uint64_t calculate_residue_unsigned(const std::vector<std::int64_t>& original, const std::vector<int>& S);

// calculate_residue_prepatition
//  calcultes the residue based on a prepartition (unsigned) per the description in the progset
std::uint64_t calculate_residue_partition(const std::vector<std::int64_t>& original, const std::vector<std::uint64_t>& P);


// abs_value_64
//  returns the absolute value of a signed 64 bit integer as unsigned. 
inline std::uint64_t abs_value_64(const std::int64_t num);

#endif // REPEATED_HPP
