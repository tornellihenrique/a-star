#include <deque>
#include <set>

#include "node.h"

#define SIZE 3
#define MAX 181440

using namespace std;

class Game
{

public:
    int **board;
    int **goal;

    Game() {}
    Game(int **_board, int **_goal) : board(_board), goal(_goal) {}

    vector<Node *> solve(int type)
    {
        vector<Node *> border;
        border.push_back(new Node(board, goal, NULL, make_pair(board, '-'), type, 0));

        Node *node = border.back();

        set<string> seen;
        seen.insert(boardToString(node->board));

        int n = 1;
        while (!border.empty())
        {
            // Sort queue
            sort(border.begin(), border.end(), compareNodes);

            // Get last
            node = border.back();
            border.pop_back();

            // Check if is solved
            if (isSolved(node->board))
            {
                break;
            }

            // Open best Node
            for (auto &action : node->actions())
            {
                Node *child = new Node(action.first, goal, node, action, type, n);

                string targetBoard = boardToString(child->board);

                // Check if this state is already known
                if (seen.find(targetBoard) == seen.end())
                {
                    border.push_back(child);

                    seen.insert(targetBoard);
                }

                n++;
            }
        }

        return node->path();
    }

    bool isSolved(int **b) const
    {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (b[i][j] != goal[i][j])
                    return false;

        return true;
    }

    static bool compareNodes(const Node *a, const Node *b)
    {
        return a->f() > b->f();
    }

    static string boardToString(int **b)
    {
        string s;

        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                s += to_string(b[i][j]);

        return s;
    }

    static void printBoard(int **b)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                cout << b[i][j] << ' ';
            }

            cout << endl;
        }
    }

    static int **generateBoard(int b[SIZE][SIZE])
    {
        int **c = new int *[SIZE];
        for (int i = 0; i < SIZE; i++)
        {
            c[i] = new int[SIZE];
            for (int j = 0; j < SIZE; j++)
            {
                c[i][j] = b[i][j];
            }
        }

        return c;
    }
};