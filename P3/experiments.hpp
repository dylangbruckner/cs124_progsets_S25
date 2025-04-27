#ifndef EXPERIMENTS_HPP
#define EXPERIMENTS_HPP
#include "annealing.hpp"
#include "hill.hpp"

std::vector<int64_t> problemInstance(const size_t& n);
std::vector<uint64_t> experiments(const size_t n, const size_t num_trials, const size_t max_iter);

#endif // EXPERIMENTS_HPP