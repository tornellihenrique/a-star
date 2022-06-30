#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <string>

#define SIZE 3

using namespace std;

typedef pair<int **, char> Move;
typedef pair<char, pair<int, int>> Direction;

class Node
{

public:
	int **board;
	int **goal;

	Node *parent;
	int g;

	Move action;

	int type;
	int n;

	Node() {}
	Node(int **_board, int **_goal, Node *_parent, Move _action, int _type, int _n) : board(_board),
																					  goal(_goal),
																					  parent(_parent),
																					  action(_action),
																					  type(_type),
																					  n(_n)
	{
	}

	int h() const
	{
		int distance = 0;

		if (type == 1) // Manhattan
		{
			int pR[(SIZE * SIZE) + 1];
			int pC[(SIZE * SIZE) + 1];

			for (int r = 0; r < SIZE; r++)
			{
				for (int c = 0; c < SIZE; c++)
				{
					pR[board[r][c]] = r;
					pC[board[r][c]] = c;
				}
			}

			for (int r = 0; r < SIZE; r++)
				for (int c = 0; c < SIZE; c++)
					if (goal[r][c])
						distance += abs(pR[goal[r][c]] - r) + abs(pC[goal[r][c]] - c);
		}

		// ...

		return distance;
	}

	int f() const
	{
		return h() + g;
	}

	vector<Node *> path()
	{
		vector<Node *> p;

		p.push_back(this);

		Node *node = parent;

		while (node != NULL)
		{
			p.push_back(node);

			node = node->parent;
		}

		reverse(p.begin(), p.end());

		return p;
	}

	vector<Move> actions()
	{
		vector<Move> moves;

		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				vector<Direction> directions = {
					make_pair('R', make_pair(i, j - 1)),
					make_pair('L', make_pair(i, j + 1)),
					make_pair('D', make_pair(i - 1, j)),
					make_pair('U', make_pair(i + 1, j))};

				for (auto &dir : directions)
				{
					char action = dir.first;

					int r = dir.second.first;
					int c = dir.second.second;

					if (r >= 0 && c >= 0 && r < SIZE && c < SIZE && board[i][j] == 0)
					{
						moves.push_back(make_pair(move(make_pair(i, j), make_pair(r, c)), action));
					}
				}
			}
		}

		return moves;
	}

	int **move(pair<int, int> a, pair<int, int> b)
	{
		int **c = new int *[SIZE];
		for (int i = 0; i < SIZE; i++)
		{
			c[i] = new int[SIZE];
			for (int j = 0; j < SIZE; j++)
			{
				c[i][j] = board[i][j];
			}
		}

		swap(c[a.first][a.second], c[b.first][b.second]);

		return c;
	}
};
