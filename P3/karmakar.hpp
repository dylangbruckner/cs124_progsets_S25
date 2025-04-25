#ifndef KARMAKAR_HPP
#define KARMAKAR_HPP

#include <vector>
#include <cstdint>
#include <cstdlib>
#include <limits>
#include <iostream>
#include <queue>
#include <cmath>

// karmarkar_karp
//  runs the karmarkar_karp algorithm on input nums
//  returns the residue
std::uint64_t karmarkar_karp(const std::vector<std::int64_t>& nums);

#endif // KARMAKAR_HPP