#include "ai.h"

AI::AI(Board *currentBoard)
{
    m_currentBoard = currentBoard;
}

Square* AI::makeMove(Board *currentBoard)
{
    QVector<Square* > *legalMoves = new QVector<Square* >;

    currentBoard->getLegalMoves(legalMoves);

    Square *square = legalMoves->first();
    currentBoard->makeMove(square->m_x, square->m_y);

    return square;
}

int AI::alphaBeta(Board *board, int depth, int alpha, int beta, bool maximizingPlayer)
{
    // TODO time parameter ...
    if (depth = 0 || board->m_gameOver)
        return evaluateBoard(board);

    QVector<Board *> possibleBoards = board->makeLegalMoves();

    if (maximizingPlayer == true)
    {


        foreach (Board *board, possibleBoards)
        {
            int newAlpha = alphaBeta(board, depth-1, alpha, beta, false);
            if (newAlpha >= alpha)
            {
                alpha = newAlpha;
            }

            if (alpha >= beta)
            {
                break;
            }
        }
        return alpha;
    }
    else if (maximizingPlayer == false)
    {
        foreach (Board *board, possibleBoards)
        {
            int newBeta = alphaBeta(board, depth-1, alpha, beta, false);
            if (newBeta <= beta)
            {
                beta = newBeta;
            }

            if (alpha >= beta)
            {
                break;
            }
        }
        return alpha;
    }

}

int AI::evaluateBoard(Board *currentBoard)
{

}
