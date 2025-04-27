#include "karmakar.hpp"

using namespace std;

std::uint64_t karmarkar_karp(vector<std::int64_t>& problem) {
    // Initialize max heap
    priority_queue<std::int64_t> maxHeap;

    size_t n = problem.size();

    // Fill max heap
    for (size_t i = 0; i < n; ++i) {
        maxHeap.push(problem[i]);
    }

    std::int64_t diff, elt_1, elt_2;

    while (maxHeap.size() > 1) {
        elt_1 = maxHeap.top();
        maxHeap.pop();
        elt_2 = maxHeap.top();
        maxHeap.pop();

        diff = elt_1 - elt_2;
        
        maxHeap.push(diff);
    }

    return maxHeap.top();
}

