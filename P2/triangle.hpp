#ifndef TRIANGLE.HPP
#define TRIANGLE.HPP


#include "strassens.hpp"
#include <random>
#include <limits>

// generates a random graph in adj list representation, where 
// each edge has probability chance of existing
Matrix<int> generate_random_graph(size_t dim, float probability);

// simulates the count trials of graphs of dimension dim for trials
float count_triangles(size_t dim, float probability, size_t trials);


#endif // TRIANGLE.HPP