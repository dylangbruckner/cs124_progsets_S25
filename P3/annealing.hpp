#ifndef ANNEALING_HPP
#define ANNEALING_HPP

#include "repeated.hpp"
#include <cmath>

// simulated_annealing
//  runs the simulated_annealing algorithm for max_iter times on input
//  prepartitioned is true if the solution should use a prepartitioned solution
//  returns the residue
std::uint64_t simulated_annealing(const std::vector<std::int64_t>& input, const size_t max_iter, const bool prepartitioned);

// T
//  implements the T function per the problem set description
inline double T(size_t iter);

#endif // ANNEALING_HPP