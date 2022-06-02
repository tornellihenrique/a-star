//
//  a-star-b.hpp
//  a-star
//
//  Created by Henrique Tornelli on 01/06/22.
//

#ifndef a_star_b_hpp
#define a_star_b_hpp

#include <iostream>
#include <deque>
#include <set>
#include <vector>
#include <array>
#include <algorithm>
#include <string>
#include <cmath>
#include <stdlib.h>

using namespace std;

#define SIZE 3
#define MAX 181440

// Shortcut for move. Each move represent a state of the puzzle
typedef pair<int**, char> Move;

// Shortcur for Direction
typedef pair<char, pair<int, int> > Direction;

// Struct definition for a Node
struct Node {
    int** board;
    int** goal;
    
    Node* parent;
    int g;
    
    Move action;
    
    int type; // type = 1 for "Manhattan", type = 2 for "Euclidean" and type 3 for "Hamming"
    int n; // Node open count
    
    Node() {}
    
    Node(int** targetBoard, int** targetGoal, Node* targetParent, Move targetAction, int targetType, int targetN) :
        board(targetBoard),
        goal(targetGoal),
        parent(targetParent),
        g(targetParent != nullptr ? targetParent->g + 1 : 0),
        action(targetAction),
        type(targetType),
        n(targetN)
    {}
    
    // Calculate h using target heuristic
    int h() const
    {
        int distance = 0;
        
        if (type == 1) { // Manhattan
            
            int pR[(SIZE * SIZE) + 1];
            int pC[(SIZE * SIZE) + 1];
            
            for (int r = 0; r < SIZE; r++) {
                for (int c = 0; c < SIZE; c++) {
                    pR[board[r][c]] = r;
                    pC[board[r][c]] = c;
                }
            }
            for (int r = 0; r < SIZE; r++)
                for (int c = 0; c < SIZE; c++)
                    if (goal[r][c])
                        distance += abs(pR[goal[r][c]] - r) + abs(pC[goal[r][c]] - c);
            
//            for (int i=0; i<SIZE; i++) {
//                for (int j=0; j<SIZE; j++) {
//                    if (board[i][j] != 0) {
//                        int x = (board[i][j] - 1) / SIZE;
//                        int y = (board[i][j] - 1) % SIZE;
//
//                        distance += abs(x - i) + abs(y - j);
//                    }
//                }
//            }
        } else if (type == 2) { // Euclidean
            
            int pR[(SIZE * SIZE) + 1];
            int pC[(SIZE * SIZE) + 1];
            
            for (int r = 0; r < SIZE; r++) {
                for (int c = 0; c < SIZE; c++) {
                    pR[board[r][c]] = r;
                    pC[board[r][c]] = c;
                }
            }
            for (int r = 0; r < SIZE; r++)
                for (int c = 0; c < SIZE; c++)
                    if (goal[r][c])
                        distance += sqrt(pow(pR[goal[r][c]] - r, 2) + pow(pC[goal[r][c]] - c, 2));
            
//            for (int i=0; i<SIZE; i++) {
//                for (int j=0; j<SIZE; j++) {
//                    if (board[i][j] != 0) {
//                        int x = (board[i][j] - 1) / SIZE;
//                        int y = (board[i][j] - 1) % SIZE;
//
//                        distance += sqrt((pow(x - i, 2)) + (pow(y - j, 2)));
//                    }
//                }
//            }
        } else if (type == 3) { // Hamming
            for (int i = 0; i < SIZE; i++)
                for (int j = 0; j < SIZE; j++)
                    if (board[i][j] && board[i][j] != goal[i][j]) distance++;
        }
        
        return distance;
    }
    
    // Calculate f
    int f() const
    {
        return h() + g;
    }
    
    vector<Node*> path()
    {
        vector<Node*> p;
        p.push_back(this);
        
        Node* node = parent;
        
        while (node != nullptr) {
            p.push_back(node);
            
            node = node->parent;
        }
        
        reverse(p.begin(), p.end());
        
        return p;
    }
    
    vector<Move> actions()
    {
        vector<Move> moves;
        
        for (int i=0; i<SIZE; i++) {
            for (int j=0; j<SIZE; j++) {
                vector<Direction> directions = {
                    make_pair('R', make_pair(i, j-1)),
                    make_pair('L', make_pair(i, j+1)),
                    make_pair('D', make_pair(i-1, j)),
                    make_pair('U', make_pair(i+1, j))
                };
                
                for (auto& dir : directions) {
                    char action = dir.first;
                    int r = dir.second.first;
                    int c = dir.second.second;
                    
                    if (r >= 0 && c >= 0 && r < SIZE && c < SIZE && board[i][j] == 0) {
                        moves.push_back(make_pair(move(make_pair(i, j), make_pair(r, c)), action));
                    }
                }
            }
        }
        
        return moves;
    }
    
    int** move(pair<int, int> at, pair<int, int> to)
    {
        // Clone the current board into "copy"
        int** copy = (int**) malloc(sizeof(int*) * SIZE);
        for (int i=0; i<SIZE; i++) {
            copy[i] = (int*) malloc(sizeof(int) * SIZE);
            for (int j=0; j<SIZE; j++) {
                copy[i][j] = board[i][j];
            }
        }
        
        swap(copy[at.first][at.second], copy[to.first][to.second]);
        
        return copy;
    }
};

class AStarB {
public:
    int** board;
    int** goal;
    
    // Dummy Constructor
    AStarB() {}
    
    // Constructor. It receives the target board as parameter
    AStarB(int targetBoard[SIZE][SIZE], int targetGoal[SIZE][SIZE]);
    
    // Solves the puzzle using A* Search Algorithm with some Heuristic type (1 for "Manhattan" or 2 for "Euclidean")
    vector<Node*> solve(int type);
    
    bool isSolved(int** b) const;
    bool isSolvable(int b[SIZE][SIZE]) const;
    int getInvCount(int arr[]) const;
    
    static bool compareNodes(const Node* a, const Node* b);
    static string boardToString(int** b);
    
    // Utility for printing boards
    void printBoard(int** b) const;
};

#endif /* a_star_b_hpp */
