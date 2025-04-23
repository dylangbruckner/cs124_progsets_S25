#ifndef ANNEALING_HPP
#define ANNEALING_HPP

#include "repeated.hpp"

// simulated_annealing
//  runs the simulated_annealing algorithm for max_iter times on input nums
//  prepartitioned is true if the solution should use a prepartitioned solution
//  returns the residue
size_t simulated_annealing(const std::vector<std::int64_t>& nums, const size_t max_iter, const bool prepartitioned);

#endif // ANNEALING_HPP