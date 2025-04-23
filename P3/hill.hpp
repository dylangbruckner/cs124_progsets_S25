#ifndef HILL_HPP
#define HILL_HPP

#include "repeated.hpp"

// hill_climbing
//  runs the hill climbing algorithm for max_iter times on input nums
//  prepartitioned is true if the solution should use a prepartitioned solution
//  returns the residue
size_t hill_climbing(const std::vector<std::int64_t>& nums, const size_t max_iter, const bool prepartitioned);

#endif // HILL_HPP