#include <iostream>
#include <chrono>

#include "game.h"

using namespace std;

int main()
{
	int goal[SIZE][SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

	int board[SIZE][SIZE] = {{1, 8, 2}, {0, 4, 3}, {7, 6, 5}}; // Solvable
	// int board[SIZE][SIZE] = { { 8, 1, 2 }, { 0, 4, 3 }, { 7, 6, 5 } }; // UnSolvable

	Game game(Game::generateBoard(board), Game::generateBoard(goal));

	const auto start = chrono::high_resolution_clock::now();
	vector<Node *> path = game.solve(1);
	const auto stop = chrono::high_resolution_clock::now();

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

	const auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	cout << "Time taken: " << duration.count() << " milliseconds" << endl;
}
