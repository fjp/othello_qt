#include "ai.h"

AI::AI(Board *currentBoard)
{
    m_currentBoard = currentBoard;
}

Square* AI::makeMove(Board *currentBoard)
{
    QVector<Square* > *legalMoves = new QVector<Square* >;

    currentBoard->getLegalMoves(legalMoves);




    Square *square;
    if (!legalMoves->isEmpty())
    {
        square  = legalMoves->first();
    }
    else
    {
        square = NULL;
    }
    currentBoard->makeMove(square->m_x, square->m_y);

    return square;
}


//int max(Board *board, int depth)
//{
//    QVector<Square*> *legalMoves;

//    if (board->getLegalMoves(legalMoves) == false || depth == 0)
//    {
//        return evaluateBoard();
//    }
//    int maxWert = -10000;

//    int length = legalMoves->length();

//    foreach (Square *currentMove, legalMoves) {
//        board->makeMove(currentMove->m_x, currentMove->m_y);
//        int wert = min(-spieler, depth-1);
//        macheZugRueckgaengig();
//    }

//    while (legalMoves->) {
//        int wert = min(-spieler, depth-1);
//        macheZugRueckgaengig();
//        if (wert > maxWert) {
//            maxWert = wert;
//            if (depth == gewuenschteTiefe)
//                gespeicherterZug = Zug;
//        }
//    }
//    return maxWert;
//}

//int min(int spieler, int tiefe) {
//    if (tiefe == 0 or keineZuegeMehr(spieler))
//        return bewerten();
//    int minWert = unendlich;
//    generiereMoeglicheZuege(spieler);
//    while (noch Zug da) {
//        fuehreNaechstenZugAus();
//        int wert = max(-spieler, tiefe-1);
//        macheZugRueckgaengig();
//        if (wert < minWert) {
//            minWert = wert;
//        }
//    }
//    return minWert;
//}



int AI::alphaBeta(Board *board, int depth, int alpha, int beta, bool maximizingPlayer)
{
    // TODO time parameter ...
    if (depth = 0 || board->m_gameOver)
    {
        int boardValue = evaluateBoard(board);
        //if (boardValue > maxBoardValue)

        //return ;
    }

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
    QVector<Square*> *legalMoves;
    currentBoard->getLegalMoves(legalMoves);

    int numberOfLegalMoves = legalMoves->count();

    currentBoard->countDisks();

}
