#ifndef REPEATED_HPP
#define REPEATED_HPP

#include <vector>
#include <tuple>
#include <random>

// generateRandom
//  generates a random solution of size 'size' in the form specified by the progset documentation
//  returns a vector containing of elements -1 or 1 pertaining to the two groups
std::vector<int> generateRandom(const size_t n);

// repeated_random
//  runs the repeated_random algorithm for max_iter times on input nums
//  prepartitioned is true if the solution should use a prepartitioned solution
//  returns the residue
size_t repeated_random(std::vector<int>& input, size_t max_iter, bool prepartitioned);

// calculateResidue
//  calculates the residue of numbers original with assignment S
int calculateResidue(const std::vector<int>& original, const std::vector<int>& S);

#endif // REPEATED_HPP
