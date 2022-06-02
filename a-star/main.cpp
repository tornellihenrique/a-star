//
//  main.cpp
//  a-star
//
//  A C++ Program to implement A* Search ALgorithm
//
//  Created by Henrique Tornelli on 01/06/22.
//

#include <iostream>

#include "a-star-a.hpp"
#include "a-star-b.hpp"

using namespace std;

void test1();
void test2();

int main(int argc, const char * argv[]) {
    
    // test1();
    
    test2();
    
    return 0;
}

void test1()
{
    // Case A - Finding path to destination based in Grid
    
    /*
     Description of the Grid:
     
     1--> The cell is not blocked
     0--> The cell is blocked
     */
    
    int grid[ROW][COL]
    = { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
        { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } };
    
    // Source is the left-most bottom-most corner
    Pair src = make_pair(8, 0);
    
    // Destination is the left-most top-most corner
    Pair dest = make_pair(0, 0);
    
    AStarA astara;
    astara.search(grid, src, dest);
}

void test2()
{
    // Case B - Solving 8 Puzzle
    
    // Solvable
    int board[SIZE][SIZE]
    = { { 1, 8, 2 },
        { 0, 4, 3 },
        { 7, 6, 5 } };
    
    // UnSolvable
//    int board[SIZE][SIZE]
//    = { { 8, 1, 2 },
//        { 0, 4, 3 },
//        { 7, 6, 5 } };
    
    AStarB aStarB(board);
    
    if (!aStarB.isSolvable(board)) {
        printf("Puzzle not solvable\n");
        return;
    }
    
    vector<Node*> path = aStarB.solve();
    
    int steps = 0;
    
    for (auto& node : path) {
        printf("%c\n", node->action.second);
        aStarB.printBoard(node->board);
        printf("\n");
        steps++;
    }
    
    printf("\nTotal number of steps: %d\n", steps);
    
    return;
}
