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
void test2(int type, int board[SIZE][SIZE], int goal[SIZE][SIZE]);

int main(int argc, const char * argv[]) {
    
    // test1(); // Another Case, ignore it
    
    int goal[SIZE][SIZE] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 0 } };
    
    int boards[3][SIZE][SIZE] = {
        // Solvable 1
        { { 1, 8, 2 }, { 0, 4, 3 }, { 7, 6, 5 } },
        
        // Solvable 2
        { { 7, 2, 4 }, { 5, 0, 6 }, { 8, 3, 1 } },
        
        // UnSolvable
        { { 8, 1, 2 }, { 0, 4, 3 }, { 7, 6, 5 } }
    };
    
    for (auto& board : boards) {
        printf("Testing new board...\n");
        
        printf("Testing Heuristic 'Manhtattan':\n\n");
        test2(1, board, goal);
        
        printf("\n\nTesting Heuristic 'Euclidean':\n\n");
        test2(2, board, goal);
        
        printf("\n\nTesting Heuristic 'Hamming':\n\n");
        test2(3, board, goal);
        
        printf("=======================================\n\n");
    }
    
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

void test2(int type, int board[SIZE][SIZE], int goal[SIZE][SIZE])
{
    // Measuring execution time
    time_t start, end;
    
    // Case B - Solving 8 Puzzle
    
    AStarB aStarB(board, goal);
    
//    if (!aStarB.isSolvable(board)) {
//        printf("Puzzle not solvable\n");
//        return;
//    }
    
    time(&start);
    
    vector<Node*> path = aStarB.solve(type);
    
    time(&end);
    
    if (path.size() == 0) {
        printf("Puzzle not solvable...\n");
    } else {
        int steps = 0;
        for (auto& node : path) {
            printf("Move: %c\n", node->action.second);
            printf("g(n): %d\n", node->g);
            printf("h(n): %d\n", node->h());
            printf("f(n): %d\n", node->f());
            printf("Node open count: %d\n", node->n);
            
            aStarB.printBoard(node->board);
            
            printf("\n");
            
            steps++;
        }
        printf("\nTotal number of steps: %d\n", steps);
    }
    
    // Calculating total time taken by the program.
    double time_taken = double(end - start);
    printf("Time taken: %lf\n", time_taken);
    
    return;
}
