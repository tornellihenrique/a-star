# A* Search Algorithm

A project for demonstrating the A* Search Algorithm used for advanced path search in the AI field.

## Introduction

A* (pronounced "A-star") is a graph traversal and path search algorithm, which is often used in many fields of computer science due to its completeness, optimality, and optimal efficiency.

Here we have two use cases of A*, one for a best path search based on a simple grid (made of 0 or 1) and a second and main one for solving the 8 puzzle, here you can see an example of it:

![8 Puzzle](https://repository-images.githubusercontent.com/479162603/40499170-5c6a-4d00-a928-88784ebc4d3e)

The puzzle is simple: You must reach the goal state starting from the initial state only by moving the blocks around the empty space.

From there, it's possible to use A* Algorithm for searching the best path for solving the puzzle. We can reach this by using Nodes, where each Node represents a state of the board that came from a Move and another Node (parent Node). If we can calculate the Heuristic for each Node, we can choose the best path for solving the puzzle using A*. Here is an example of the Algorithm:

![8 Puzzle A*](https://miro.medium.com/max/819/1*Bz0qSCPmRb509DRYpYEEkQ.jpeg)

## Getting Started

Importing the header `game.h` you can use the code in your own `main` only by doing the following:
```cpp

#include "game.h"

using namespace std;

int main() {
  int goal[SIZE][SIZE]    = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 0 } };
  int initial[SIZE][SIZE] = { { 1, 8, 2 }, { 0, 4, 3 }, { 7, 6, 5 } };
  
  Game game(Game::generateBoard(board), Game::generateBoard(goal));
  
  vector<Node*> path1 = game.solve(1); // Solves using "Manhattan" Heuristic
  vector<Node*> path2 = game.solve(2); // Solves using "Euclidean" Heuristic
  vector<Node*> path3 = game.solve(3); // Solves using "Hamming"   Heuristic
}
```

As you can see, it's possible to solve the puzzle using 3 Heuristics: "Manhattan", "Euclidean" and "Hamming". More details of them in next section.

Here is an example for printing the Nodes after solving the puzzle:
```cpp
int steps = 0;
for (auto &node : path)
{
  cout << "Move: " << node->action.second << endl;
  cout << "g(n)" << node->g << endl;
  cout << "h(n)" << node->h() << endl;
  cout << "f(n)" << node->f() << endl;

  Game::printBoard(node->board);

  cout << endl;

  steps++;
}

cout << endl
    << "Total number of steps: " << steps << endl;
```

## The Code

The source code was made using C++ for a better performance and use of object orientation.

The class `Game` represents a 8 Puzzle. In the constructor you send the initial and goal state of the board. And using the method `solve(...)` it solves the problem using the chosen Heuristic. Also, there are some other utility methods, such as `isSolved(...)`, `isSolvable(...)`, `getInvCount(...)`, `compareNodes(...)`, `boardToString(...)` and `printBoard(...)`.

The `solve` method works using the `Node`, which is a class. It works as follows:
1. A Node knows its `board` state and the `goal` one.
2. A Node points to its `parent`.
3. A Node has a `g`, which is its cost, how deep this Node is.
4. A Node has a Move (`action`), which represents the Movement that it came from. This Move contains a target board state and a `char` representing its label.
5. A Node has a Heuristc `type`. 1 for Manhattan, 2 for Euclidean and 3 for Hamming.
6. A Node has a count of how many Nodes were open for reaching it (`n`).
7. Using the method `h()` it calculates the Heuristic using the defined `type`:
    - 1 - Manhattan: Sum of Manhattan distances of the tiles from their goal positions.
    - 2 - Euclidean: Sum of Eucledian distances of the tiles from their goal positions.
    - 3 - Hamming: Sum of block's in the wrong position.
8. Using the method `f()` it calculates the sum of `g` and `h()`.
9. Using the method `path()` it returns a `vector` containing the full path from this Node until the starting Node.
10. Using the method `actions()` it returns every possible Move for that board state.

Using the Node struct, the AStarB class uses the A* Algorithm and opens every least costing Node based in the Heuristc of the queue of Nodes.
Each interaction, after chosing the Node, it's open using its possible Moves.

If at some point the current Node is the solution, it returns the full path of that Node. But if it reach the limit of Nodes (which is 181440), it returns an empty path vector. This means that this Puzzle is unsolvable.

## Tests

Now, some detailed tests using 2 solvable Puzzles and 1 unsolvable Puzzle for each Heuristic. Read `output.txt` for the full output.

### First Board:
```
1 8 2 
0 4 3 
7 6 5
```

- Testing Heuristic 'Manhtattan':
```
g(n): 9
h(n): 0
f(n): 9
1 2 3 
4 5 6 
7 8 0

Node open count: 32
Total number of steps: 10
Time taken: 0.000000
```

- Testing Heuristic 'Euclidean':
```
g(n): 9
h(n): 0
f(n): 9
1 2 3 
4 5 6 
7 8 0 

Node open count: 46
Total number of steps: 10
Time taken: 0.000000
```

- Testing Heuristic 'Hamming':
```
g(n): 9
h(n): 0
f(n): 9
1 2 3 
4 5 6 
7 8 0 

Node open count: 71
Total number of steps: 10
Time taken: 0.000000
```

### Second Board:
```
7 2 4 
5 0 6 
8 3 1 
```

- Testing Heuristic 'Manhtattan':
```
g(n): 20
h(n): 0
f(n): 20
1 2 3 
4 5 6 
7 8 0

Node open count: 745
Total number of steps: 21
Time taken: 0.000000
```

- Testing Heuristic 'Euclidean':
```
g(n): 20
h(n): 0
f(n): 20
1 2 3 
4 5 6 
7 8 0 

Node open count: 2775
Total number of steps: 21
Time taken: 0.000000
```

- Testing Heuristic 'Hamming':
```
g(n): 20
h(n): 0
f(n): 20
1 2 3 
4 5 6 
7 8 0 

Node open count: 9803
Total number of steps: 21
Time taken: 1.000000
```

### Unsolvable Board:
```
8 1 2
0 4 3 
7 6 5 
```

- Testing Heuristic 'Manhtattan':
```
Puzzle not solvable...
Time taken: 238.000000
```

- Testing Heuristic 'Euclidean':
```
Puzzle not solvable...
Time taken: 921.000000
```

- Testing Heuristic 'Hamming':
```
Puzzle not solvable...
Time taken: 233.000000
```
