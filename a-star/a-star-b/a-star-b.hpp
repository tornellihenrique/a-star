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
#include <stdlib.h>

using namespace std;

#define SIZE 3
#define MAX 30

// Shortcut for move. Each move represent a state of the puzzle
typedef pair<int**, char> Move;

// Shortcur for Direction
typedef pair<char, pair<int, int> > Direction;

// Struct definition for a Node
struct Node {
    int** board;
    
    Node* parent;
    int g;
    
    Move action;
    
    Node() {}
    
    Node(int** targetBoard, Node* targetParent, Move targetAction) : board(targetBoard), parent(targetParent), g(targetParent != nullptr ? targetParent->g + 1 : 0), action(targetAction) {}
    
    // Calculate h using "Manhattan" heuristic
    int h() const
    {
        int distance = 0;
        
        for (int i=0; i<SIZE; i++) {
            for (int j=0; j<SIZE; j++) {
                if (board[i][j] != 0) {
                    int x = (board[i][j] - 1) / SIZE;
                    int y = (board[i][j] - 1) % SIZE;
                    
                    distance += abs(x - i) + abs(y - j);
                }
            }
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
    
    // Dummy Constructor
    AStarB() {}
    
    // Constructor. It receives the target board as parameter
    AStarB(int targetBoard[][SIZE]);
    
    // Solves the puzzle using A* Search Algorithm
    vector<Node*> solve();
    
    bool isSolved(int** b) const;
    bool isSolvable(int b[SIZE][SIZE]) const;
    int getInvCount(int arr[]) const;
    
    bool compareBoards(int** a, int** b) const;
    bool compareSeenBoards(set<int**> seen, int** b) const;
    static bool compareNodes(const Node* a, const Node* b);
    
    // Utility for printing boards
    void printBoard(int** b) const;
};

#endif /* a_star_b_hpp */
