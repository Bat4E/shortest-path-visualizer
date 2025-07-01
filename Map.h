#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "ASCII.h"

using namespace std;

// enum for tiles
enum TerrainType {
    // CHARACTER = 'C', represents the path taken by dijkstra's shortest path, starting point and final point have their respective tiles.
    CHARACTER = 'C',
    START = 'S', // Starting point
    END = 'E', // final point
    MOUNTAIN = 'M',
    FOREST = 'F',
    PRAIRIE = 'P',
    ROAD = 'R',
    WATER = 'W' // Assuming 'W' represents water
    // Add more terrain types as needed
};

class Map {
public:
    Map();// Constructor to create a map of given size
    ~Map(); // Destructor to deallocate dynamic arrays
    void loadTerrain(const string& filename); // Load terrain from a file
    int getTileWeight(char tileChar) const; // returns a tile weight "maps"
    char getTerrain(int row, int col) const; // gets terrain char at given position
    void displayMapText() const; // Display the map on the console
    void displayMap() const; // Displays map with tiles
    // displayMap helper functions
    void printTopHalfOfTile(char terrainType) const;
    void printBottomHalfOfTile(char terrainType) const;
    int getRows() const;
    int getCols() const;
    int getSize() const; // gets map size, n by n, use only for graph class
    // Additional methods as needed
    std::pair<int, int> getDimensions() const; // Gets map dimensions (rows, columns)
    void updatePathOnMap(const int* path, int pathLength, int start, int end); // updates Map for Dijkstra
    void clearPreviousPath(); // clears previous 2D map
private:
    char** terrainMatrix; // Dynamically allocated 2D array for the terrain
    //char** originalTerrainMatrix; // Additional 2D array to store the original terrain types do I really need it?
    int size; // Size of the map
    int rows; // rows in map
    int cols; // columns in map
    int tileWeights[128]; // maps tile weights, 128 since it's more than enough
    void initializeTileWeights(); // initializes tile weights
    // New method to initialize the original terrain matrix
    //void initializeOriginalTerrain(); // am I doing it twice?
    //char getOriginalTerrain(int row, int col) const; // gets original terrain type at a given position, could use, just modify
    // Additional attributes as needed
};