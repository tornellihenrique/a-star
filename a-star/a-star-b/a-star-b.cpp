//
//  a-star-b.cpp
//  a-star
//
//  Created by Henrique Tornelli on 01/06/22.
//

#include "a-star-b.hpp"

AStarB::AStarB(int targetBoard[][SIZE])
{
    board = (int**) malloc(sizeof(int*) * SIZE);
    for (int i=0; i<SIZE; i++) {
        board[i] = (int*) malloc(sizeof(int) * SIZE);
        for (int j=0; j<SIZE; j++) {
            board[i][j] = targetBoard[i][j];
        }
    }
}

vector<Node*> AStarB::solve()
{
    deque<Node*> queue;
    queue.push_front(new Node(board, nullptr, make_pair(board, ' ')));
    
    Node* node = queue.back();
    
    set<int**> seen;
    seen.insert(node->board);
    
    while (!queue.empty()) {
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
            Node* child = new Node(action.first, node, action);
            
            // Check if this state is already known
            if (!compareSeenBoards(seen, child->board)) {
                queue.push_front(child);
                seen.insert(child->board);
            }
        }
    }
    
    return node->path();
}

bool AStarB::isSolved(int** b) const
{
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            if (i+1 == SIZE && j+1 == SIZE) {
                if (b[i][j] != 0) {
                    return false;
                }
            } else if (b[i][j] != (i * SIZE + j) + 1) {
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

bool AStarB::compareBoards(int **a, int **b) const
{
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            if (a[i][j] != b[i][j])
                return false;
        }
    }
    
    return true;
}

bool AStarB::compareSeenBoards(set<int**> seen, int** b) const
{
    for (auto& s : seen) {
        if (compareBoards(s, b))
            return true;
    }
    
    return false;
}

bool AStarB::compareNodes(const Node *a, const Node *b)
{
    return a->f() < b->f();
}

void AStarB::printBoard(int **b) const
{
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            printf("%d ", b[i][j]);
        }
        
        printf("\n");
    }
}
