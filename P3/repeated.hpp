#ifndef REPEATED_HPP
#define REPEATED_HPP

#include <vector>
#include <tuple>

// random_solution
//  generates a random solution of size 'size' in the form specified by the progset documentation
//  returns a tuple containing the residual and the random solution
std::tuple<size_t, std::vector<size_t>> random_solution(size_t size, std::vector<int> nums);

// repeated_random
//  runs the repeated_random algorithm for max_iter times on input nums
//  prepartitioned is true if the solution should use a prepartitioned solution
//  returns the residue
size_t repeated_random(std::vector<int> nums, size_t max_iter, bool prepartitioned);

#endif // REPEATED_HPP
