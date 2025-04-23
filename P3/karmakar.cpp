#include <vector>
#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

size_t karmakar(vector<size_t>& problem) {
    // Initialize max heap
    priority_queue<size_t> maxHeap;

    size_t n = problem.size();

    // Fill max heap
    for (size_t i = 0; i < n; ++i) {
        maxHeap.push(problem[i]);
    }

    size_t diff, elt_1, elt_2;

    while (maxHeap.size() > 1) {
        elt_1 = maxHeap.top();
        maxHeap.pop();
        elt_2 = maxHeap.top();
        maxHeap.pop();

        if (elt_1 > elt_2) 
            diff = elt_1 - elt_2;
        else 
            diff = elt_2 - elt_1;
        
        maxHeap.push(diff);
    }

    return maxHeap.top();
}

