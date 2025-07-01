#pragma once
#include <iostream>
#include <algorithm>
#include <climits> // for INT_MAX
#include <chrono>
#include <random>
#include "Map.h"

using namespace std;

class Graph {
private:
    int** adjacencyMatrix;
    int rows;
    int cols;
    int vertices;
    static const int DEFAULT_WEIGHT = 1; // Weight of a road
    int minDistance(int dist[], bool sptSet[]); // dijkstra helper function
public:
    Graph(int rows, int cols);
    ~Graph();
    void initializeFromMap(const Map& map); // Method to initialize the graph from a map
    void generateRandomConnectivity(double connectivityPercentage); // to achieve vertex percentage connectivity
    int convertTo1DIndex(int row, int col, int numCols); // converts 2D to 1D matrix
    void addEdge(int u, int v, int weight); // adds undirected edges
    void addEdge(int row1, int col1, int row2, int col2, int weight);
    bool addEdgeForConnectivity(int u, int v, int weight); // helper for random connectivity method
    int getRandomVertex(); // gets random vertex
    int getWeight(int u, int v) const; // gets w(u,v)
    int getVerticesCount() const; // gets the number of vertices
    int* dijkstra(int src); // dijkstra's algorithm
    int* getShortestPath(int dest, const int prev[], int& pathLength); // to use to update 2D map
    void printSolution(int dist[], int prev[], int src); // dijkstra helper function
    // void printSolution(int dist[], int prev[]); // dijkstra helper function works original
    void printPath(int vertex, int prev[]); // prints shortest path
    void displayGraph() const; // displays all vertices
    void displayConnectedGraph() const; // displays only connected vertices
    void displayConnectedGraphTable() const; // display weight like a matrix
    void displayConnectedGraphWithCoordinates(const Map& map) const; // display 2D Map coordinates

    // Additional methods as needed, such as getWeight(u, v), etc.
};
// Graph.h ends