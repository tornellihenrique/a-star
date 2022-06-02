//
//  a-star-b.cpp
//  a-star
//
//  Created by Henrique Tornelli on 01/06/22.
//

#include "a-star-b.hpp"

AStarB::AStarB(int targetBoard[SIZE][SIZE], int targetGoal[SIZE][SIZE])
{
    board = (int**) malloc(sizeof(int*) * SIZE);
    for (int i=0; i<SIZE; i++) {
        board[i] = (int*) malloc(sizeof(int) * SIZE);
        for (int j=0; j<SIZE; j++) {
            board[i][j] = targetBoard[i][j];
        }
    }
    
    goal = (int**) malloc(sizeof(int*) * SIZE);
    for (int i=0; i<SIZE; i++) {
        goal[i] = (int*) malloc(sizeof(int) * SIZE);
        for (int j=0; j<SIZE; j++) {
            goal[i][j] = targetGoal[i][j];
        }
    }
}

vector<Node*> AStarB::solve(int type)
{
    deque<Node*> queue;
    queue.push_front(new Node(board, goal, nullptr, make_pair(board, '-'), type, 0));
    
    Node* node = queue.back();
    
    set<string> seen;
    seen.insert(boardToString(node->board));
    
    int n = 1;
    while (!queue.empty() && n <= MAX) {
        // printf("Nodes: %d\n", n);
        
        // Sort queue
        vector<Node*> vec = { queue.begin(), queue.end() };
        sort(vec.begin(), vec.end(), compareNodes);
        queue = deque<Node*>(vec.begin(), vec.end());
        
        // Get first
        node = queue.front();
        queue.pop_front();
        
        // Check if it's solved
        if (isSolved(node->board)) {
            return node->path();
        }
        
        // Open Nodes for possible moves
        for (auto& action : node->actions()) {
            Node* child = new Node(action.first, goal, node, action, type, n);
            
            string targetBoard = boardToString(child->board);
            
            // Check if this state is already known
            if (seen.find(targetBoard) == seen.end()) {
                queue.push_front(child);
                seen.insert(targetBoard);
            }
            
            n++;
        }
    }
    
    return vector<Node*>();
}

bool AStarB::isSolved(int** b) const
{
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            if (b[i][j] != goal[i][j]) {
                return false;
            }
        }
    }
    
    return true;
}

bool AStarB::isSolvable(int b[SIZE][SIZE]) const
{
    int invCount = getInvCount((int *) b);
    
    return (invCount % 2 == 0);
}

int AStarB::getInvCount(int *arr) const
{
    int inv_count = 0;
    for (int i=0; i<(SIZE*SIZE) - 1; i++)
        for (int j=i+1; j<(SIZE*SIZE); j++)
            if (arr[j] && arr[i] &&  arr[i] > arr[j])
                inv_count++;
    
    return inv_count;
}

bool AStarB::compareNodes(const Node *a, const Node *b)
{
    return a->f() < b->f();
}

string AStarB::boardToString(int **b)
{
    string s = "";
    
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            s += to_string(b[i][j]);
        }
    }
    
    return s;
}

void AStarB::printBoard(int **b)
{
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            printf("%d ", b[i][j]);
        }
        
        printf("\n");
    }
}

void AStarB::printBoard(int b[SIZE][SIZE])
{
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            printf("%d ", b[i][j]);
        }
        
        printf("\n");
    }
}
