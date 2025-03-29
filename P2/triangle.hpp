#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP


#include "strassens.hpp"
#include <random>
#include <limits>

const size_t N10224_CHOOSE_3 = 178433024;
const size_t STANDARD_DIM    = 1024;
const float CURR_PROB        = 0.1;
const size_t NUM_TRIALS      = 1;

// generates a random graph in adj list representation, where 
// each edge has probability chance of existing
Matrix<int> generate_random_graph(size_t dim, float probability);

// simulates the count trials of graphs of dimension dim for trials
float count_triangles(size_t dim, float probability, size_t trials);


#endif // TRIANGLE_HPP