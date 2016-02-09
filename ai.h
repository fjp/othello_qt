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

Brute-Force Evaluation Function
The brute-force evaluation function is optimal and is used
whenever we can build the whole game search-tree. The function has two modes of execution.
One mode tries to maximize the computer’s number of extra discs in a win-condition
(or alternatively, if the computer cannot win, it tries to minimize the player’s number of extra discs).
The other mode does not care about how many discs the computer can win by,
but just whether it can win. The brute-force evaluation function kicks in at the end of the game
when the board is nearly full (the default cut-off is 14 empty squares left).
*/

#include "board/board.h"
#include "player/player.h"

class AI
{

public:
    AI(Board *currentBoard);

    Square *makeMove(Board *currentBoard);


private:
    int alphaBeta(Board *board, int depth, int alpha, int beta, bool maximizingPlayer);
    int evaluateBoard(Board *currentBoard);

    Board *m_currentBoard;
};

#endif // AI_H
