#ifndef ANNEALING_HPP
#define ANNEALING_HPP

#include "repeated.hpp"

// simulated_annealing
//  runs the simulated_annealing algorithm for max_iter times on input nums
//  prepartitioned is true if the solution should use a prepartitioned solution
//  returns the residue
size_t simulated_annealing(std::vector<int>& nums, size_t max_iter, bool prepartitioned);

#endif // ANNEALING_HPP