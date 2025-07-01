// implementation of Graph Class
#include "Graph.h"
#include "MinHeap.h"
#include <algorithm>
#include <iomanip>
#include <set>
#include <chrono>

// constructor
Graph::Graph(int r, int c) : rows(r), cols(c), vertices(r * c) {
    // Allocate the adjacencyMatrix dynamically based on the size
    adjacencyMatrix = new int* [vertices];
    for (int i = 0; i < vertices; ++i) {
        adjacencyMatrix[i] = new int[vertices];
        // Initialize the matrix with max value (infinity)
        std::fill_n(adjacencyMatrix[i], vertices, INT_MAX);
    }
} // constructor ends

// destructor
Graph::~Graph() {
    // Deallocate the adjacencyMatrix
    for (int i = 0; i < vertices; ++i) {
        delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;
    adjacencyMatrix = nullptr;
} // destructor ends

// initializes adjacency graph from 2D Map
// also use it before the random connectivity function
void Graph::initializeFromMap(const Map& map) {
    auto dimensions = map.getDimensions(); // Retrieve the dimensions of the map
    int rows = dimensions.first;
    int cols = dimensions.second;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char terrain = map.getTerrain(i, j);
            int currentWeight = map.getTileWeight(terrain);

            // Calculate the index in the adjacency matrix for the current cell
            int u = i * cols + j;

            // Check and add edges for each direction if there's no wall
            // Right neighbor
            if (j + 1 < cols) {
                char rightTerrain = map.getTerrain(i, j + 1);
                int rightWeight = map.getTileWeight(rightTerrain);
                if (rightWeight != INT_MAX) {
                    int v = i * cols + (j + 1); // Index for the right cell
                    int edgeWeight = (currentWeight + rightWeight) / 2;
                    addEdge(u, v, edgeWeight);
                }
            }
            // Down neighbor
            if (i + 1 < rows) {
                char downTerrain = map.getTerrain(i + 1, j);
                int downWeight = map.getTileWeight(downTerrain);
                if (downWeight != INT_MAX) {
                    int v = (i + 1) * cols + j; // Index for the down cell
                    int edgeWeight = (currentWeight + downWeight) / 2;
                    addEdge(u, v, edgeWeight);
                }
            }
            // Left neighbor
            if (j - 1 >= 0) {
                char leftTerrain = map.getTerrain(i, j - 1);
                int leftWeight = map.getTileWeight(leftTerrain);
                if (leftWeight != INT_MAX) {
                    int v = i * cols + (j - 1); // Index for the left cell
                    int edgeWeight = (currentWeight + leftWeight) / 2;
                    addEdge(u, v, edgeWeight);
                }
            }
            // Up neighbor
            if (i - 1 >= 0) {
                char upTerrain = map.getTerrain(i - 1, j);
                int upWeight = map.getTileWeight(upTerrain);
                if (upWeight != INT_MAX) {
                    int v = (i - 1) * cols + j; // Index for the up cell
                    int edgeWeight = (currentWeight + upWeight) / 2;
                    addEdge(u, v, edgeWeight);
                }
            }
        }
    }
} // initializeFromMap ends

// generates random percentage of connectivity on vertices
// use it after using initializeFromMap, parameter(0.25) as 25% and so on
// generates random percentage of connectivity on vertices
void Graph::generateRandomConnectivity(double connectivityPercentage) {
    int totalPossibleEdges = (vertices * (vertices - 1)) / 2; // For undirected graph
    int edgesToCreate = static_cast<int>(round(totalPossibleEdges * connectivityPercentage));
    std::set<std::pair<int, int>> existingEdges;

    while (edgesToCreate > 0) {
        int vertexA = getRandomVertex();
        int vertexB = getRandomVertex();

        // Ensure we're not creating a loop and the edge doesn't already exist
        if (vertexA != vertexB) {
            auto edge = std::make_pair(std::min(vertexA, vertexB), std::max(vertexA, vertexB));
            // Check if the edge already exists
            if (existingEdges.find(edge) == existingEdges.end()) {
                addEdge(vertexA, vertexB, DEFAULT_WEIGHT);
                existingEdges.insert(edge);
                edgesToCreate--;
            }
        }
    }
} // generateRandomConnectivity ends

// gets random vertex for connectivity method
int Graph::getRandomVertex() {
    static std::mt19937 rng(std::random_device{}()); // Random number generator
    std::uniform_int_distribution<int> dist(0, vertices - 1); // Distribution in range [0, vertices-1]

    return dist(rng);

} // getRandomVertex ends

// converts 2D matrix to 1D matrix
int Graph::convertTo1DIndex(int row, int col, int numCols) {
    return row * numCols + col;
} // convertTo1DIndex ends

void Graph::addEdge(int row1, int col1, int row2, int col2, int weight) {
    int index1 = convertTo1DIndex(row1, col1, cols);
    int index2 = convertTo1DIndex(row2, col2, cols);
    if (index1 >= 0 && index1 < vertices && index2 >= 0 && index2 < vertices) {
        adjacencyMatrix[index1][index2] = weight;
        adjacencyMatrix[index2][index1] = weight; // For undirected graphs
    }
    else {
        // Handle the error for invalid indices
        cerr << "Error: Indices out of bounds." << endl;
    }
} // addEdge ends

void Graph::addEdge(int u, int v, int weight) {
    if (u >= 0 && u < vertices && v >= 0 && v < vertices) {
        adjacencyMatrix[u][v] = weight;
        adjacencyMatrix[v][u] = weight; // For undirected graphs
    }
    else {
        // Handle the error for invalid indices
        cerr << "Error: Indices out of bounds." << endl;
    }
} // addEdge ends

// addEdge for vertices connectivity function
bool Graph::addEdgeForConnectivity(int u, int v, int weight) {
    // Check if the indices are within bounds and the edge does not already exist
    if (u >= 0 && u < vertices && v >= 0 && v < vertices && adjacencyMatrix[u][v] == INT_MAX) {
        adjacencyMatrix[u][v] = weight;
        adjacencyMatrix[v][u] = weight; // For undirected graphs
        return true; // Edge added successfully
    }
    return false; // Edge not added because it already exists or indices are out of bounds
} // addEdgeForConnectivity ends

// Method to get the weight of an edge between vertices u and v
int Graph::getWeight(int u, int v) const {
    // Check if the indices are within the bounds of the matrix
    if (u >= 0 && u < vertices && v >= 0 && v < vertices) {
        return adjacencyMatrix[u][v];
    }
    else {
        // Return a special value that indicates an invalid edge or out-of-bounds access
        return -1; // You can define a constant for this purpose
    }
} // getWeight ends

// Function to get the number of vertices in the graph
int Graph::getVerticesCount() const {
    return vertices;
} // ends

// Dijkstra helper function
// gets minDistance from (u,v), do I even use it? probably not
int Graph::minDistance(int dist[], bool sptSet[]) {
    // Initialize min value and min_index
    int min = INT_MAX, min_index = -1; // Initialized min_index to -1

    for (int v = 0; v < vertices; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    // It's a good idea to check if min_index is still -1 before returning
    if (min_index == -1) {
        cerr << "Error: no vertex found for minDistance" << endl;
        // Handle the error appropriately
    }

    return min_index;
} // minDistance ends

// dijkstra helper function displays
// printSolution also calls printPath, works well.
void Graph::printSolution(int dist[], int prev[], int src) {
    cout << "Vertex \t Distance from Source \t Path\n";
    for (int i = 0; i < vertices; i++) {
        if (dist[i] != INT_MAX) { // Check if a path exists
            cout << i << " \t\t" << dist[i] << " \t\t";
            printPath(i, prev);
            cout << endl;
        }
    }
} // printSolution ends

// why can't I have this function return the path so I can use it with my convert from 2D to 1D mapping function? ANd just update the map?
// dijkstra helper function with printSolution
// displays shortesPath Solution
// display the shortest path properly, works fine
void Graph::printPath(int vertex, int prev[]) {
    if (vertex == -1) {
        return; // Invalid vertex
    }
    if (prev[vertex] == -1) {
        cout << vertex; // Print the source vertex
        return;
    }
    printPath(prev[vertex], prev); // Recursively print the path to the predecessor
    cout << " -> " << vertex; // Print the current vertex
} // printPath ends

// dijkstra's algorihtm
int* Graph::dijkstra(int src) {

    MinHeap minHeap(vertices);
    int* dist = new int[vertices]; // The output array. dist[i] will hold the shortest distance from src to i
    int* prev = new int[vertices]; // The predecessor array. prev[i] will hold the previous vertex on the shortest path to i

    // Initialize all distances as INFINITE, predecessors as -1, and MinHeap with all vertices
    for (int v = 0; v < vertices; v++) {
        dist[v] = INT_MAX;
        prev[v] = -1; // Initialize all predecessors to -1
        minHeap.insertKey(v, dist[v]);
    }

    // Set distance of source vertex to 0 and update in MinHeap
    dist[src] = 0;
    prev[src] = -1; // source has no predecessor
    minHeap.decreaseKey(src, dist[src]);

    // Loop while the min heap is not empty
    while (!minHeap.isEmpty()) {
        // Extract the vertex with the minimum distance value
        std::pair<int, int> minPair = minHeap.extractMin();
        int u = minPair.first; // Vertex number

        // Update the distance value of all adjacent vertices of u
        for (int v = 0; v < vertices; v++) {
            // Relaxation (u,v,w)
            // Update dist[v] only if there is an edge from u to v, and the total weight of the path from src to v through u is smaller than the current value of dist[v]
            if (adjacencyMatrix[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + adjacencyMatrix[u][v] > 
                dist[u] && dist[u] + adjacencyMatrix[u][v] < dist[v])
            {
                dist[v] = dist[u] + adjacencyMatrix[u][v]; // Update the distance to v
                prev[v] = u; // Set the predecessor of v to u
                minHeap.decreaseKey(v, dist[v]); // Update the min heap with the new distance

                // Debugging output
                //cout << "Updated dist[" << v << "] to " << dist[v] << " from " << u << endl;
                //cout << "Predecessor of " << v << " set to " << u << endl;
            }
        }
    } // End of loop

    // print the constructed distance array and the shortest paths
    printSolution(dist, prev, src);
    // printSolution(dist, prev); // original that was tested and works had this: printSolution(dist, prev);

    delete[] dist; // free the dynamically allocated memory
    return prev; // return the predecessor array
} // dijkstra ends

// Function to get the shortest path from source to destination
// needs rework

// Function to get the shortest path from source to destination
// This version does not use std::vector
int* Graph::getShortestPath(int dest, const int prev[], int& pathLength) {
    // Allocate memory for the maximum possible path length
    int* path = new int[vertices];
    pathLength = 0; // Initialize path length

    // Temporary variable to store the current node
    int current = dest;

    // Backtrack from the destination to the source
    while (current != -1) {
        if (pathLength > 0) {
            // shifts elements to the right
            for (int i = pathLength; i > 0; --i) {
                path[i] = path[i - 1]; // Shift elements to the right
            }
        }
        path[0] = current; // Insert the current node
        ++pathLength; // Increment path length

        // Move to the predecessor
        current = prev[current];

        // Check for array overflow
        if (pathLength > vertices) {
            cerr << "Error: Path exceeds the number of vertices." << endl;
            delete[] path;
            return nullptr;
        }
    }

    // Return the path array
    return path;
} // getShortestPath ends new one

/*
int* Graph::getShortestPath(int dest, const int prev[], int& pathLength) {
    // Temporary array to store the reverse path
    int* tempPath = new int[vertices];
    int count = 0;

    // Trace the path from destination to source
    for (int at = dest; at != -1; at = prev[at]) {
        if (count >= vertices) {
            // Handle the error: count should never exceed the number of vertices
            cerr << "Error: Path is longer than the number of vertices." << endl;
            delete[] tempPath;
            return nullptr; // Return a null pointer to indicate an error
        }
        tempPath[count++] = at;
    }

    // Allocate the array for the correct path
    int* path = new int[count];
    pathLength = count; // Set the path length

    // Reverse the path into the correct order
    for (int i = 0; i < count; ++i) {
        path[i] = tempPath[count - i - 1];
    }

    delete[] tempPath; // Free the temporary array
    return path;
} // getShortestPath ends
*/
// displays adjacency undirected Graph
// displays all vertices in the adjacency matrix
// infity if not directly connected
void Graph::displayGraph() const {
    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < rows * cols; ++i) {
        for (int j = 0; j < rows * cols; ++j) {
            if (adjacencyMatrix[i][j] == INT_MAX) {
                cout << "INF ";
            }
            else {
                cout << adjacencyMatrix[i][j] << " ";
            }
        }
        cout << endl;
    }
} // display Graph ends

// displays only the connected parts of the adjacency Graph (weights)
// displays connected from here to there.
void Graph::displayConnectedGraph() const {
    cout << "Connected Parts of the Adjacency Matrix:" << endl;
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            // Skip if the weight is INT_MAX, indicating no direct connection
            if (adjacencyMatrix[i][j] != INT_MAX) {
                cout << "Edge from " << i << " to " << j << " weight: " << adjacencyMatrix[i][j] << endl;
            }
        }
    }
} // displayConnectedGraph ends

// displays 2D Coordinates as well
void Graph::displayConnectedGraphWithCoordinates(const Map& map) const {
    int cols = map.getDimensions().second; // Assuming you have a method to get the number of columns

    cout << "Connected Parts of the Adjacency Matrix with 2D Map Coordinates:" << endl;
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            if (adjacencyMatrix[i][j] != INT_MAX) {
                // Convert 1D indices back to 2D coordinates
                int row1 = i / cols;
                int col1 = i % cols;
                int row2 = j / cols;
                int col2 = j % cols;

                cout << "Edge from (" << row1 << ", " << col1 << ") to (" << row2 << ", " << col2 << ") weight: " << adjacencyMatrix[i][j] << endl;
            }
        }
    }
}

void Graph::displayConnectedGraphTable() const {
    cout << "Connected Weights of the Adjacency Matrix Table:" << endl;
    cout << "|   |";
    // Print the column headers
    for (int col = 0; col < vertices; ++col) {
        cout << setw(3) << col << " |";
    }
    cout << endl << "|---|";
    // Print the separator for the column headers
    for (int col = 0; col < vertices; ++col) {
        cout << "----|";
    }
    cout << endl;

    // Print the rows
    for (int row = 0; row < vertices; ++row) {
        cout << "|" << setw(3) << row << " |";
        for (int col = 0; col < vertices; ++col) {
            // Display the weight if there is a connection
            if (adjacencyMatrix[row][col] != INT_MAX) {
                cout << setw(3) << adjacencyMatrix[row][col] << " |";
            }
            else {
                cout << " INF |"; // Display INF if there is no direct connection
            }
        }
        cout << endl;
    }
} // displayConnectedGraphTable ends
// graph.cpp ends


/*
Change back if the other addEdges give you errors because I added error handling, worked fine before that.
void Graph::addEdge(int row1, int col1, int row2, int col2, int weight) {
    int index1 = convertTo1DIndex(row1, col1, cols); // cols is the number of columns in the map
    int index2 = convertTo1DIndex(row2, col2, cols);
    adjacencyMatrix[index1][index2] = weight;
    adjacencyMatrix[index2][index1] = weight; // For undirected graphs
}

// addEdge for undirected Graph
void Graph::addEdge(int u, int v, int weight) {
    // Assuming a directed graph, add an edge from u to v with the given weight
    adjacencyMatrix[u][v] = weight;
    adjacencyMatrix[v][u] = weight;
} // addEdge ends
*/


/*
// Dijkstra helper function
// prints shortest path? works tested
void Graph::printSolution(int dist[], int prev[]) {
    cout << "Vertex \t Distance from Source \t Path\n";
    for (int i = 0; i < vertices; i++) {
        cout << i << " \t\t" << dist[i] << " \t\t";
        printPath(i, prev);
        cout << endl;
    }
}// printSolutionTested ends
*/

/*
// prints shortest path (predecessor path) for Dijkstra works with tested printSolution
void Graph::printPath(int vertex, int prev[]) {
    if (vertex == -1 || prev[vertex] == -1) {
        // If vertex is the source or a cycle is detected
        return;
    }
    printPath(prev[vertex], prev); // Recursively print the path to the predecessor
    cout << vertex << " "; // Print the current vertex
}// printPath ends
*/