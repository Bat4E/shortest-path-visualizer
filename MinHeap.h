// MinHeap header files will need for Dijkstra's algorithm
#pragma once
#include <utility> // For std::pair

class MinHeap {
private:
    std::pair<int, int>* heapArr; // Dynamic array of pairs
    int size;                     // Current number of elements in the heap
    int capacity;                 // Maximum possible size of the heap

    int parent(int i) const;
    int leftChild(int i) const;
    int rightChild(int i) const;
    void heapifyDown(int i);
    void heapifyUp(int i);

public:
    MinHeap(int cap);
    ~MinHeap();
    void insertKey(int v, int k); // to insert vertices into the minHeap, s = 0
    std::pair<int, int> extractMin(); // removes vertex with the min distance
    void decreaseKey(int v, int newDist); // use to update a vertex when a shorter distance has been found
    bool isEmpty() const;
    // ... other necessary functions ...
}; // MinHeap class header file ends