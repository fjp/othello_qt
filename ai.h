#ifndef AI_H
#define AI_H

/*
Search:
As almost all game playing programs, our Othello player uses a minimax search with alpha-beta pruning.
It also uses some move ordering in order to help pruning more quickly.
The move ordering is very primitive,
and it simply tests first the placed around the disc which the opponent has just played,
since there is a somewhat larger probability that those places will be more favorable.

Evaluation Function:
We have implemented two evaluation functions used during two different stages of the game.
A heuristic evaluation function is used during the beginning and mid-game when the board
is still being filled; an optimal brute-force evaluation function is used
during the final stage of the game, when there are few moves left until the board gets full.
The default cut-off point when use of the optimal evaluation function starts
is when there are 14 empty squares left on the board.

Now, we describe each of the two evaluation functions:
Heuristic Evaluation Function
Our heuristic function returns an integer specifying the attractiveness of a potential move.
The greater the number, the more attractive a given move is.
The number returned is evaluated through three components: disc count, legal moves count,
and corner squares. We now describe each of the three components.

Disc Count
Since the goal of the game is to have more discs than the opponent,
one would think that a good evaluation function would simply compute the two players’
disc balance at each search node. In practice, we found that maximizing one’s disc
count is a very poor strategy and that we could easily beat a program using such an evaluation function.
For this reason we give very little weight to a player’s number of discs, namely a weight of 1/100;
in fact, some programs even give negative weight to disc count.

Legal Moves Count
The number of legal moves one can make is the primary evaluation component
and each legal move is counted as 1. Thus, one legal move is worth a hundred
discs—more than could be placed on the board! This is intentional—when comparing two moves,
the number of discs is irrelevant unless the number of legal moves is equal in which
case we prefer the move that results in a greater disc count.

Corner Squares
The squares in the corners of the board are strategic positions that result in great advantage
when occupied; furthermore, a disc in a corner square can never be flipped. For this reason,
we have assigned a value of 10 to each corner square,
and thus one corner square is worth 10 legal moves or 1000 discs.
*/

#include <QMap>
#include <QVector>
#include <QPair>

#include "board/board.h"
#include "player/player.h"
#include "define.h"

class AI
{

public:
    AI(Board *board);

    void makeRandomMove();

    int max(int depth, int alpha, int beta);
    int min(int depth, int alpha, int beta);

    QPair<int, int> savedMove();

    int m_startingDepth;


private:
    Board *m_board;

    static const int m_heuristic[8][8];

    //int alphaBeta(Board board, int depth, int alpha, int beta, bool maximizingPlayer);
    int evaluateBoard();

    QPair<int, int> m_savedMove;



    //Board m_currentBoard;
};

#endif // AI_H
