// Implentation file for Map class

#include "Map.h"

// constructor
Map::Map() : size(0), rows(0), cols(0), terrainMatrix(nullptr) {
    initializeTileWeights();
    // Initialize the original terrain matrix
    //initializeOriginalTerrain();
}

// destructor
Map::~Map() {
    // Deallocate the terrain matrix
    for (int i = 0; i < rows; ++i) {
        delete[] terrainMatrix[i];
    }
    delete[] terrainMatrix;
    terrainMatrix = nullptr;

    /*
    // Deallocate the originalTerrainMatrix
    for (int i = 0; i < rows; ++i) {
        delete[] originalTerrainMatrix[i];
    }
    delete[] originalTerrainMatrix;
    */

} // ~Map ends

// initializesTileWeights, maps
void Map::initializeTileWeights() {
    // Initialize all weights to INT_MAX to represent impassable tiles
    std::fill_n(tileWeights, 128, INT_MAX); // has the private array that maps char and tileWeights

    // Assign weights to specific tile characters
    tileWeights['M'] = 10; // Mountain
    tileWeights['F'] = 6; // Forest
    tileWeights['W'] = 4; // Water
    tileWeights['P'] = 2; // Prairie
    tileWeights['R'] = 1; // Road
    // for wall tile it will INT_MAX by default since it's impassable
    // ... and so on for other tiles

} // initializeTileWeights ends

// load the terrain, reads a text file that contains the map
// first two lines (rows x columns)
void Map::loadTerrain(const string& filename) {
    // newly added, may delete if its messes everything up
    if (terrainMatrix != nullptr) {
        for (int i = 0; i < rows; ++i) {
            delete[] terrainMatrix[i];
        }
        delete[] terrainMatrix;
        terrainMatrix = nullptr;
    }
    // new line added, may delete if it messes anything up
    // Clear any previous path markings
    clearPreviousPath();

    std::ifstream file(filename);

    if (file.is_open()) {
        // Read the size of the map
        file >> rows >> cols; // assuming a square map
        // Ignore the rest of the line
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        // Dynamically allocate the terrain matrix
        terrainMatrix = new char* [rows];
        for (int i = 0; i < rows; ++i) {
            terrainMatrix[i] = new char[cols];
        }

        // Read the map data and initialze the terrain matrix
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                file >> terrainMatrix[i][j];
                // newly added, delete if it messes anything up
                // praire to 'reset' path here

            }
            // Ignore the rest of the line
            file.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        file.close();

        // potential line?
        // reset stuff? who knows
        // may need to initializeTileWeight(); for some reason
        // but may not even need it
    }
    else {
        std::cerr << "Unable to open file\n";
    }

} // loadTerrain ends

// A method to return the weight of a tile based on its character
int Map::getTileWeight(char tileChar) const {
    // returns tileWeight
    return tileWeights[tileChar];
}

// gets the terrain at given position
char Map::getTerrain(int row, int col) const {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return terrainMatrix[row][col];
    }
    else {
        // Return a character that represents an invalid or non-existent tile
        return '\0'; // Null character as an example
    }
} // getTerrain ends

// displays Map text file
void Map::displayMapText() const {

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << terrainMatrix[i][j] << ' ';
        }
        cout << endl;
    }

} // displayMap ends

// New displayMap tiles
// Display Top half tiles
// Display Bottome half tiles
void Map::displayMap() const {
    // First pass for the top halves of the tiles
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printTopHalfOfTile(terrainMatrix[i][j]);
        }
        cout << endl; // End the first line of the row
        for (int k = 0; k < cols; ++k) {
            printBottomHalfOfTile(terrainMatrix[i][k]);
        }
        cout << endl; // End the first line of the row
    }
}

// Example functions for printing the top and bottom halves of a tile
void Map::printTopHalfOfTile(char terrainType) const {
    switch (terrainType) {
    case START:
        cout << "\033[30;" << LIGHT_BLUE_BKG << "m^_^\033[m";
        break;
    case END:
        cout << "\033[30;" << LIGHT_SCARLET_RED_BKG << "mT T\033[m";
        break;
    case CHARACTER:
        cout << "\033[37;43m o \033[m";
        break;
    case FOREST:
        cout << "\033[31;42m(o)\033[m";
        break;
    case MOUNTAIN:
        cout << "\033[" << RED_TXT << ";" << LIGHT_BROWN_BKG << "m^^^\033[m";
        break;
    case PRAIRIE:
        cout << "\033[" << DARK_GREEN_TXT << ";" << LIGHT_GREEN_BKG << "m\"\"\"\033[m";
        break;
    case ROAD:
        cout << "\033[" << WHITE_TXT << ";" << BROWN_TXT << "m===\033[m";
        break;
    case WATER:
        cout << "\033[37;46m~~~\033[m";
        break;
    default:
        cout << "\033[33;45m###\033[m"; // wall
        break;
        // ... other cases ...
    }
}

void Map::printBottomHalfOfTile(char terrainType) const {
    switch (terrainType) {
    case START:
        cout << "\033[30;" << LIGHT_BLUE_BKG << "m U \033[m";
        break;
    case END:
        cout << "\033[30;" << LIGHT_SCARLET_RED_BKG << "m ^ \033[m";
        break;
    case CHARACTER:
        cout << "\033[37;43m/D\\\033[m";
        break;
    case FOREST:
        cout << "\033[31;42m_#_\033[m";
        break;
    case MOUNTAIN:
        cout << "\033[" << RED_TXT << ";" << LIGHT_BROWN_BKG << "m^^^\033[m";
        break;
    case PRAIRIE:
        cout << "\033[" << DARK_GREEN_TXT << ";" << LIGHT_GREEN_BKG << "m\"\"\"\033[m";
        break;
    case ROAD:
        cout << "\033[" << WHITE_TXT << ";" << BROWN_TXT << "m===\033[m";
        break;
    case WATER:
        cout << "\033[37;46m~~~\033[m";
        break;
    default:
        cout << "\033[33;45m###\033[m";
        break;
        // ... other cases ...
    }
}

// Gets number of rows
int Map::getRows() const {
    return rows;
}

// Gets number of columns
int Map::getCols() const {
    return cols;
}

// get map size
int Map::getSize() const {
    return (rows * cols);
}

// getSize function returns a pair
std::pair<int, int> Map::getDimensions() const {
    return std::make_pair(rows, cols);
}

// updates the map to display Dijkstra's shortest path taken
// may not need clearPreviousPath
void Map::updatePathOnMap(const int* path, int pathLength, int start, int end) {
    // Clear any previous path if necessary
    // may not need it
    clearPreviousPath();

    // Set the starting and ending points
    terrainMatrix[start / getCols()][start % getCols()] = START;
    terrainMatrix[end / getCols()][end % getCols()] = END;

    // Update the terrainMatrix with the path tiles
    for (int i = 0; i < pathLength; ++i) {
        // for debugging
        // cout << "This is path[i] = " << path[i] << " / getCols() " << getCols() << " int row = ";
        int row = path[i] / getCols();
        // for debuggin
        // cout << row << " and that was row." << endl;
        int col = path[i] % getCols();

        // Skip the start and end tiles
        if ((row * getCols() + col) != start && (row * getCols() + col) != end && terrainMatrix[row][col] != 'X') {
            terrainMatrix[row][col] = CHARACTER;
        }
    }

    // Redraw the map to reflect the updated path
    displayMap();
} // updatePathOnMap ends

// New method to clear any previous path from the map
// may need it, if so make sure to modify the: terrainMatrix[i][j] = originalTerrainMatrix[i][j];, since i may not need the array
void Map::clearPreviousPath() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Check if the current tile is part of the path
            if (terrainMatrix[i][j] == CHARACTER || terrainMatrix[i][j] == START || terrainMatrix[i][j] == END) {
                // Reset the tile to its original terrain type
                terrainMatrix[i][j] = PRAIRIE;
            }
        }
    }
} // clearPreviousPath ends

/*
// may need it, but modify
// Method to get the original terrain type at a given position
char Map::getOriginalTerrain(int row, int col) const {
    return originalTerrainMatrix[row][col];
}
*/

// map implementation file ends


/*
// New method to initialize the original terrain matrix
// do I really need it?
void Map::initializeOriginalTerrain() {
    originalTerrainMatrix = new char* [rows];
    for (int i = 0; i < rows; ++i) {
        originalTerrainMatrix[i] = new char[cols];
        for (int j = 0; j < cols; ++j) {
            originalTerrainMatrix[i][j] = terrainMatrix[i][j];
            cout << terrainMatrix[i][j] << " LOOK! ";
        }
    }
} // initializeOriginalTerrain ends
*/