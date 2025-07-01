// implentation file for MinHeap class
#include "MinHeap.h"
#include <climits>
#include <iostream>

// Constructor: Initializes the heap
MinHeap::MinHeap(int cap) : size(0), capacity(cap) {
    heapArr = new std::pair<int, int>[cap];
}

// Destructor: Deallocates memory
MinHeap::~MinHeap() {
    delete[] heapArr;
}

// gets parent index
int MinHeap::parent(int i) const { return (i - 1) / 2; }

// gets left child index
int MinHeap::leftChild(int i) const { return (2 * i + 1); }

// gets right child index
int MinHeap::rightChild(int i) const { return (2 * i + 2); }

// heapify the subtree rooted with index i
void MinHeap::heapifyDown(int i) {
    int left = leftChild(i);
    int right = rightChild(i);
    int smallest = i;

    if (left < size && heapArr[left].second < heapArr[i].second)
        smallest = left;
    if (right < size && heapArr[right].second < heapArr[smallest].second)
        smallest = right;

    if (smallest != i) {
        std::swap(heapArr[i], heapArr[smallest]);
        heapifyDown(smallest);
    }
}

// heapify the heap from above
void MinHeap::heapifyUp(int i) {
    while (i != 0 && heapArr[parent(i)].second > heapArr[i].second) {
        std::swap(heapArr[i], heapArr[parent(i)]);
        i = parent(i);
    }
}

// inserts a new key 'k' with vertex 'v'
void MinHeap::insertKey(int v, int k) {
    if (size == capacity) {
        std::cout << "Overflow: Could not insertKey\n";
        return;
    }

    // First insert the new key at the end
    size++;
    int i = size - 1;
    heapArr[i] = std::make_pair(v, k);

    // Fix the min heap property if it is violated
    heapifyUp(i);
}

// extracts root which the min element
std::pair<int, int> MinHeap::extractMin() {
    if (size <= 0)
        return std::make_pair(-1, INT_MAX);
    if (size == 1) {
        size--;
        return heapArr[0];
    }

    // Store the minimum value, and remove it from the heap
    std::pair<int, int> root = heapArr[0];
    heapArr[0] = heapArr[size - 1];
    size--;
    heapifyDown(0);

    return root;
}

// decreases the key, when a shortest path is found.
// used when a shorter distance of a vertex has been found.
void MinHeap::decreaseKey(int v, int newDist) {
    // Find the vertex index 'i' in heapArr
    int i;
    for (i = 0; i < size; i++) {
        if (heapArr[i].first == v) {
            break;
        }
    }
    if (i == size) {
        std::cout << "Vertex not found\n";
        return; // Vertex not found
    }

    // Update the distance value of the vertex
    heapArr[i].second = newDist;

    // Move the updated vertex up until the MinHeap property is restored
    heapifyUp(i);
} // decreaseKey ends

bool MinHeap::isEmpty() const {
    return size == 0;
}
// minHeap.cpp ends