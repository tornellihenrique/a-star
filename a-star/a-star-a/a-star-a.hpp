//
//  a-star.hpp
//  a-star
//
//  Created by Henrique Tornelli on 01/06/22.
//

#ifndef a_star_hpp
#define a_star_hpp

#include <iostream>
#include <math.h>
#include <stack>
#include <set>
#include <float.h>

using namespace std;

#define ROW 9
#define COL 10

// Shortcut to int, int pair type
typedef pair<int, int> Pair;

// Shortcut to pair<int, pait<int, int>> type
typedef pair<double, pair<int, int> > pPair;

// Structure to hold the necessary parameters
struct cell {
    // Row and Column index of its parent
    int parentI, parentJ;
    
    // f = g + h
    double f, g, h;
};

class AStarA {
public:
    // Utility function: Check if row and column are in range
    bool isValid(int row, int col);
    
    // Utility function: Check whether the given cell is blocked or not
    bool isUnBlocked(int grid[][COL], int row, int col);
    
    // Utility function: Check whether destination cell has been reached or not
    bool isDestination(int row, int col, Pair dest);
    
    // Utility function: Calculate the 'h' heuristics.
    double calculateHValue(int row, int col, Pair dest);
    
    // Utility function: Trace the path from the source to destination
    void tracePath(cell cellDetails[][COL], Pair dest);
    
    // Function to find the shortest path between a given source cell to a destination cell according to A* Search Algorithm
    void search(int grid[][COL], Pair src, Pair dest);
};

#endif /* a_star_hpp */
