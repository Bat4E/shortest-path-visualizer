# Terrain-Based Shortest Path Visualizer

A C++ application simulating shortest-path traversal through varied terrain using Dijkstra’s algorithm. Designed with custom graph structures, memory-safe programming, and console-based ASCII tile rendering—all built without STL containers.

## Features

- Dynamic 2D terrain maps rendered with colorful ASCII tiles
- Tile types: Mountain, Forest, Prairie, Road — each with weighted traversal costs
- User input for selecting source & destination coordinates
- Dijkstra’s algorithm implemented with a custom min-heap priority queue
- Object-Oriented Design: Map, Graph, Heap, and Display modules
- Dynamic memory management with zero memory leaks

## Technologies Used

- **Language:** C++
- **IDE:** Microsoft Visual Studio 2022 (MSVC)
- **Key Concepts:** Graph theory, heap structures, Dijkstra’s algorithm, file I/O, dynamic arrays
- **Constraints:** STL containers (vector, queue, priority_queue) prohibited

## File Structure

📁 Project Structure
/
├── ASCII.h / ASCII.cpp // Console color and tile rendering
├── Map.h / Map.cpp // Map parsing and terrain display
├── Graph.h / Graph.cpp // Adjacency graph + Dijkstra implementation
├── MinHeap.h / MinHeap.cpp // Heap-based priority queue
├── FinalProject.cpp // Main program and user interaction
├── /maps // Sample terrain text files
└── README.md

## How to Run

1. Clone or download the project
2. Open the `.sln` in **Visual Studio**
3. Build in Debug or Release mode
4. Run the app and follow the console prompts:
   - Choose one of the 5 sample map files
   - Enter source and destination coordinates
   - Watch Dijkstra’s path display live in the console

## Sample Map Format

Example:
5 5
P P F M R
P F F F R
M M F P R
F F P P P
R R R R R

Each letter maps to a tile type (e.g., `P` = Prairie, `M` = Mountain), and weights are configured in `Map.cpp`.

## Code Rules Followed

- All arrays allocated dynamically
- No STL containers used
- No `break` or `continue` inside loops
- Memory deallocated safely using destructors

## What I Learned

- Implementing graphs, heaps, and pathfinding algorithms without high-level abstractions
- Using OOP in a large, multi-file C++ codebase
- Reading and parsing input maps to create dynamic environments
- Designing tile-based visualization using ASCII art and system color macros
- Balancing algorithm performance with user-friendly design

---

> _“Built from scratch using only logic, heaps, and some ASCII art.”_
