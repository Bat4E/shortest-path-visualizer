// FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Efrain Diaz Valdez, shortest path project

#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include "Map.h"
#include "Graph.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////// Function prototypes ///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// testConnectivity prototype
void displayConnectivityMenu();
void displayMapMenu();
void displayMenu();
int getUserChoice();
void handleUserChoice(int choice, Graph** graphs, Map* maps);
void testConnectivity(Graph& graph, int connectivityPercentage, bool runTest);

//*******************************************************************************************************************************************//
//********************** This the where the magic happens! **********************************************************************************//
//*******************************************************************************************************************************************//

int main() {
    const int totalMaps = 5;
    // Instantiate your maps and graphs here
    Map maps[totalMaps]; // Array of 5 Map objects

    // Create three Graph objects for testing with different sizes
    Graph smallGraph(2, 5); // Graph with 10 vertices
    Graph mediumGraph(10, 10); // Graph with 100 vertices
    Graph largeGraph(100, 100); // Graph with 1000 vertices

    // for part 2 connectivity
    Graph* testGraphs[] = { &smallGraph, &mediumGraph, &largeGraph };
    int graphSizes[] = { 10, 100, 1000 };

    /*
    * template
    Map MyMap6;
    MyMap6.loadTerrain("MyMap2.txt");
    cout << "Displaying big map: " << endl;
    MyMap6.displayMapText();
    cout << endl;
    MyMap6.displayMap();
    cout << endl;
    */

    // instantiating maps
    for (int i = 0; i < 5; ++i) {
        // Constructs the filename based on the map number
        std::string filename = "MyMap" + std::to_string(i + 1) + ".txt";
        cout << "Displaying " << filename << endl;
        maps[i].loadTerrain(filename); // works keep
        maps[i].displayMapText(); // displays as text file, remove later
        cout << endl; // remove later
        maps[i].displayMap(); // displays as tiles, remove later
        cout << endl; // remove later
        // ... rest of your code to initialize graphs
    }
    // getting 2D maps ready for 1D adj matrix graph
    // also initializing tiles to be ready for dijkstra
    const int NUM_MAPS = 5; // Assuming 5 maps
    Graph* myMapGraphs[NUM_MAPS]; // Array to hold pointers to Graph objects
    int mapRow, mapCol;

    for (int i = 0; i < NUM_MAPS; ++i) {
        mapRow = maps[i].getRows();
        mapCol = maps[i].getCols();
        myMapGraphs[i] = new Graph(mapRow, mapCol); // Dynamically allocate a new Graph, keep
        myMapGraphs[i]->initializeFromMap(maps[i]); // Initialize it from the map, keep
        // cout << "Displaying map " << i + 1 << " vertices and edges: " << endl; // works, delete
        // myMapGraphs[i]->displayConnectedGraphWithCoordinates(maps[i]); // works, delete
        // cout << endl; // delete
    }
    // ... (initial setup for maps and test graphs)
    bool exitProgram = false; // Flag to control the loop
    while (!exitProgram) { // Infinite loop controlled by the flag
        displayMenu();
        int choice = getUserChoice();

        if (choice == 1) {
            // Display the connectivity test menu
            displayConnectivityMenu();
            int testChoice = getUserChoice();
            if (testChoice >= 1 && testChoice <= 3) {
                // Handle choices for testing connectivity on different graph sizes
                int connectivityPercentage;
                cout << "Enter connectivity percentage for testing (e.g., 25 for 25%): ";
                cin >> connectivityPercentage;

                Graph* selectedGraph = nullptr;
                switch (testChoice) { // Corrected to use testChoice
                    case 1: selectedGraph = &smallGraph; break;
                    case 2: selectedGraph = &mediumGraph; break;
                    case 3: selectedGraph = &largeGraph; break;
                }
                // safety
                if (selectedGraph != nullptr) { // Check that the pointer is not null
                    testConnectivity(*selectedGraph, connectivityPercentage, true);
                }
                else {
                    cout << "Error: Selected graph is not available." << endl;
                } // inside if/else ends
            }
            else if (testChoice == 4) {
                continue; // Go back to the main menu
            }
        }
        else if (choice == 2) {
            // Display the map menu
            displayMapMenu();
            int mapChoice = getUserChoice();
            if (mapChoice >= 1 && mapChoice <= 5) { // Corrected to use mapChoice
                handleUserChoice(mapChoice, myMapGraphs, maps); // Pass the array of graphs and maps
            }
        }
        else if (choice == 3) {
            cout << "Exiting program." << endl;
            exitProgram = true; // Set the flag to true to exit the loop
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    // Clean up dynamically allocated memory
    for (int i = 0; i < NUM_MAPS; ++i) {
        delete myMapGraphs[i];
    }

    return 0; // This point is never reached
}



/*
* Main Before trying the new user interface!
int main() {
    // part 2 begins
    // Create a graph with 10 vertices
    // vertices = row x cols for adj matrix
    int rowConnect = 10;
    int colConnect = 10;
    Graph connectivityGraph(rowConnect, colConnect); // Assuming your Graph constructor can handle a single parameter for vertices

    // Generate 5% connectivity on the graph
    // warning 1000 vertices with 100% will take a while to run
    double connectivityPercentage = 100.0;
    connectivityGraph.generateRandomConnectivity(connectivityPercentage / 100.0);

    // Test Dijkstra's algorithm with random source and destination
    testConnectivity(connectivityGraph, connectivityPercentage, true);
    // part 2 ends

    // part 1 begins
    Map map;
    // Load and display the initial map
    map.loadTerrain("map10x10.txt");
    map.displayMapText();
    cout << endl;
    map.displayMap();
    cout << endl;

    // Initialize the graph with map dimensions
    int rows = map.getRows();
    int cols = map.getCols();
    Graph myGraph(rows, cols);
    myGraph.initializeFromMap(map);

    // Display graph details
    cout << "Displaying graph." << endl;
    myGraph.displayConnectedGraphWithCoordinates(map);
    cout << endl;

    // Convert 2D coordinates to 1D indices for Dijkstra's algorithm
    int sourceRow = 1, sourceCol = 1, numCols = 5;
    int sourceVertex = sourceRow * cols + sourceCol;
    int destRow = 5, destCol = 5;
    int destVertex = destRow * cols + destCol;

    // Run Dijkstra's algorithm
    cout << "Running Dijkstra's algorithm!" << endl;
    int* prev = myGraph.dijkstra(sourceVertex);
    if (prev == nullptr) {
        cerr << "Dijkstra's algorithm failed to find a path." << endl;
        return -1; // Or handle the error as appropriate
    }

    // Retrieve the shortest path
    int pathLength = 0;
    int* shortestPath = myGraph.getShortestPath(destVertex, prev, pathLength);
    if (shortestPath == nullptr) {
        cerr << "Failed to retrieve the shortest path." << endl;
        delete[] prev; // Clean up prev array
        return -1; // Or handle the error as appropriate
    }

    // Update and display the map with the shortest path
    map.updatePathOnMap(shortestPath, pathLength, sourceVertex, destVertex);

    // Clean up dynamically allocated memory
    delete[] prev;
    delete[] shortestPath;

    return 0;

} // main() ends revised
*/

/**************************************************************************************************************************
************************************ Helper Main Functions definitions ****************************************************
**************************************************************************************************************************/

// display Menu
void displayMenu() {
    cout << "Select an option:" << endl;
    cout << "1. Test Connectivity" << endl;
    cout << "2. Work with Maps" << endl;
    cout << "3. Exit" << endl;
} // displayMenu ends

// menu for part 2 connectivity
void displayConnectivityMenu() {
    cout << "Select the graph size for connectivity testing:" << endl;
    cout << "1. Small Graph (10 vertices)" << endl;
    cout << "2. Medium Graph (100 vertices)" << endl;
    cout << "3. Large Graph (1000 vertices)" << endl;
    cout << "4. Back to Main Menu" << endl;
} // displayConnectivityMenu ends

// displayMenu function
void displayMapMenu() {
    cout << "Please select a map to work with:" << endl;
    cout << "1. Map 1" << endl;
    cout << "2. Map 2" << endl;
    cout << "3. Map 3" << endl;
    cout << "4. Map 4" << endl;
    cout << "5. Map 5" << endl;
    cout << "6. Back to Main Menu" << endl;
} // displayMenu ends

// gets the user's choice with a cin
int getUserChoice() {
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    // Add input validation if needed
    cout << "You've chosen " << choice << endl;
    return choice;
} // getUserChoice ends

// handles the choices the user makes
// exits the program when choice is 6
// handles dijkstra for 2D Map dijkstra shortest path
void handleUserChoice(int choice, Graph** graphs, Map* maps) {
    if (choice == 6) {
        cout << "Exiting program." << endl;
        exit(0); // Use exit to leave the program
    }
    else {
        // The user has chosen a map between 1 and 5
        int mapIndex = choice - 1; // Adjust index to be zero-based
        int mapRows = maps[mapIndex].getRows();
        int mapCols = maps[mapIndex].getCols();
        cout << "Map Size is " << mapRows << "x" << mapCols << endl;
        // Handle other choices, such as running Dijkstra's algorithm
        // Prompt user for source and destination coordinates
        // make sure you know you're coordinate 2D Map
        int sourceRow, sourceCol, destRow, destCol;
        cout << "Enter source row and column for 2D Map: ";
        cin >> sourceRow >> sourceCol;
        cout << "Enter destination row and column for 2D Map: ";
        cin >> destRow >> destCol;

        // Convert 2D coordinates to 1D indices
        int sourceVertex = sourceRow * maps[mapIndex].getCols() + sourceCol;
        int destVertex = destRow * maps[mapIndex].getCols() + destCol;

        // Run Dijkstra's algorithm on the selected graph
        int* prev = graphs[mapIndex]->dijkstra(sourceVertex);
        if (prev == nullptr) {
            cerr << "Dijkstra's algorithm failed to find a path." << endl;
        }
        else {
            // Retrieve the shortest path
            int pathLength = 0;
            int* shortestPath = graphs[mapIndex]->getShortestPath(destVertex, prev, pathLength);
            if (shortestPath == nullptr) {
                cerr << "Failed to retrieve the shortest path." << endl;
            }
            else {
                // Update and display the map with the shortest path
                maps[mapIndex].updatePathOnMap(shortestPath, pathLength, sourceVertex, destVertex);
                // Display the map with the path
                //maps[mapIndex].displayMap();
            }
            // Clean up dynamically allocated memory
            delete[] prev;
            delete[] shortestPath;
        }
    }
} // handleUserChoice ends

// testConnectivity method
// parameters, adjacency graph, map to be used, desired percentage(25 etc), and true/false to run)
// source, destination vertices are randomly chosen as well..
// send true if you want to display
void testConnectivity(Graph& graph, int connectivityPercentage, bool runTest) {
    if (runTest) {
        // Generate random connectivity on the graph
        graph.generateRandomConnectivity(connectivityPercentage / 100.0);

        // Select random source and destination vertices
        int sourceVertex = graph.getRandomVertex();
        int destVertex = graph.getRandomVertex();
        // Ensure that the source and destination are not the same
        while (destVertex == sourceVertex) {
            destVertex = graph.getRandomVertex();
        }

        // Start the timer
        auto start = std::chrono::high_resolution_clock::now();

        // Run Dijkstra's algorithm on the updated graph
        int* prev = graph.dijkstra(sourceVertex); // won't show shortest path

        // Stop the timer
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        // Check if Dijkstra's algorithm succeeded
        if (prev == nullptr) {
            cerr << "Dijkstra's algorithm failed to find a path on the updated graph." << endl;
        }
        else {
            // Output the time taken and other details
            cout << "Dijkstra's algorithm took " << duration.count() << " milliseconds." << endl;
            cout << "Number of vertices: " << graph.getVerticesCount() << endl; // Assuming you have a method to get the number of vertices
            cout << "Connectivity percentage: " << connectivityPercentage << "%" << endl;

            // Clean up dynamically allocated memory
            delete[] prev;
        }
    }
} // testConnectivity ends

/*
making sure I don't mess anything up, just return to this previous code since it was somewhat working....
int main()
{
    Map map;
    // Displaying Map 1, as plain text
    map.loadTerrain("map2x2.txt");
    map.displayMapText();
    cout << endl;

    // Displaying Map 1, with Tiles
    cout << "Displaying tiles: " << endl;
    map.displayMap();
    cout << endl;

    // retrieving Map Dimensions
    int rows = map.getRows();
    int cols = map.getCols();

    // creating a Graph Object with the correct rxc vertices
    Graph myGraph(rows, cols);
    // initializing Graph with map object
    myGraph.initializeFromMap(map);

    // Displaying all vertices of Graph
    cout << "Displaying graph." << endl;
    //myGraph.displayGraph();

    // displaying only connected Graph edges in words
    // works perfectly shows the vertices
    //myGraph.displayConnectedGraph();

    // displays graph like a matrix, works I think, needs more testing, but with smaller map scale(2x2)
    //myGraph.displayConnectedGraphTable();

    // displays 2D map coordinates
    myGraph.displayConnectedGraphWithCoordinates(map);

    cout << endl;
    
    // for Dijkstra (row, col) from 2D to 1D adj matrix vertices
    // showing 2D (1,1) tile
    int sourceRow = 1; // row coordinate of the source on the 2D map
    int sourceCol = 1; // column coordinate of the source on the 2D map
    int numCols = 5; // number of columns in the 2D map

    // Convert 2D coordinates to a 1D index for the adjacency matrix
    // (row, col) = index Vertex for 1D adj Matrix
    // (1,1) =
    //  Vertex Index = (1 * 5) + 1 = 6
    int sourceVertex = sourceRow * numCols + sourceCol;

    // for dijkstra
    int destRow = 2; // row coord of destination on the 2D map
    int destCol = 3; // column coord of destination on the 2D map
    int destVertex = destRow * cols + destCol; // Convert 2D coord to a 1D index

    // testing dijkstra's algorithm
    cout << "Displaying Dijkstra!" << endl;
    int* prev = myGraph.dijkstra(sourceVertex);

    // retrieve the shortest path
    int pathLength = 0; // the total number of vertices the shortest path took....
    int* shortestPath = myGraph.getShortestPath(destVertex, prev, pathLength);

    // Update the map with the shortest path
    // this was modified, originally was just: map.updatePathOnMap(shortestPath, pathLength, sourceVertex, destVertex);
    // Check if shortestPath is not nullptr before updating the map
    if (shortestPath != nullptr) {
        // Update the map with the shortest path
        map.updatePathOnMap(shortestPath, pathLength, sourceVertex, destVertex);

        // ... Display the updated map ...
    }

    delete[] prev; // don't froget to free the memory...
    delete[] shortestPath; // Don't forget to free the memory allocated for the shortest path

    return 0;
}
*/
