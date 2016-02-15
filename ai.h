#ifndef AI_H
#define AI_H

/*
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

/**
 * @brief The AI class implements the alpha-beta pruning algorithm to find
 * the next move for the computer player. Thereby three different heuristics
 * (disc count, legal moves count, square rating), implemented in
 * the evaluation funciton, are used.
 */
class AI
{

public:
    AI(Board *board);

    void makeRandomMove();

    /**
     * @brief max maximizing funciton for the black player of the the alpha-beta pruning algorithm.
     * @param depth user defined search depth in the beginning of the recursion.
     * @param alpha maximum score that the maximizing player (black) is assured of.
     * @param beta minimum score that the minimizing player (white) is assured of.
     * @return value of the evaluation function at depth zero or at a terminal node
     * (board where current player has no more moves availabel).
     */
    double max(int depth, double alpha, double beta);
    /**
     * @brief min minimizing function for the white player of the alpha-beta pruning algorithm.
     * @param depth depth user defined search depth in the beginning of the recursion.
     * @param alpha alpha maximum score that the maximizing player (black) is assured of.
     * @param beta beta minimum score that the minimizing player (white) is assured of.
     * @return value of the evaluation function at depth zero or at a terminal node
     * (board where current player has no more moves availabel).
     */
    double min(int depth, double alpha, double beta);

    /**
     * @brief savedMove is used to get the best move, found by the alpha-beta pruning algorithm,
     * inside the GameEngine class.
     * @return
     */
    QPair<int, int> savedMove();

    /**
     * @brief m_startingDepth maximum search depth defined by the user.
     */
    int m_startingDepth;


private:
    /**
     * @brief m_board pointer to the currently used board.
     */
    Board *m_board;

    /**
     * @brief m_heuristic 2x2 matrix of the board that assigns weightings to the single board positions.
     * corners are rated higher than edges and X corners, which are considered "bad", have negative values.
     */
    static const int m_heuristic[8][8];

    /**
     * @brief evaluateBoard is used to evaluate the current board using different heuristics.
     * Three different heuristics are used: disc count, number of legal moves, and rating of board positions
     * by using the m_heuristic matrix.
     * @return evaluation value of the current board.
     */
    double evaluateBoard();

    /**
     * @brief m_savedMove stores the best found move by the alpha-beta pruning algorithm.
     */
    QPair<int, int> m_savedMove;
};

#endif // AI_H
