#ifndef HILL_HPP
#define HILL_HPP

#include "repeated.hpp"

// hill_climbing
//  runs the hill climbing algorithm for max_iter times on input nums
//  prepartitioned is true if the solution should use a prepartitioned solution
//  returns the residue
size_t hill_climbing(std::vector<int> nums, size_t max_iter, bool prepartitioned);

#endif // HILL_HPP