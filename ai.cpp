#include "ai.h"

const int AI::m_heuristic[8][8] = {   { 100,   50,  50,  50,  50,  50,   50, 100, }, // 1
                                      {  50, -100, -30, -30, -30, -30, -100,  50, }, // 2
                                      {  50,  -50,   0,   0,   0,   0,  -50,  50, }, // 3
                                      {  50,  -50,   0,   0,   0,   0,  -50,  50, }, // 3
                                      {  50,  -50,   0,   0,   0,   0,  -50,  50, }, // 3
                                      {  50,  -50,   0,   0,   0,   0,  -50,  50, }, // 3
                                      {  50, -100, -50, -50, -50, -50, -100,  50, }, // 3
                                      { 100,   50,  50,  50,  50,  50,   50, 100, }, // 3
                                  };


AI::AI(Board *board)
{
    m_board = board;
    m_startingDepth = 0;
}

void AI::makeRandomMove()
{
    QMap<QPair<int,int>, QVector<QPair<int,int> > > legalMoves = m_board->getLegalMoves();

    if (m_board->legalMovesAvailable())
    {
        QPair<int,int> move = legalMoves.firstKey();
        m_board->makeMove(move.first, move.second);
    }
}

QPair<int, int> AI::savedMove()
{
    return m_savedMove;
    qDebug() << "savedMove from AI is:" << m_savedMove.first << "," << m_savedMove.second;

}


double AI::max(int depth, double alpha, double beta)
{
    QMap<QPair<int,int>, QVector<QPair<int,int> > > legalMoves;
    // if search depth is reached or maximizing player (BLACK) has no moves left the board is evaluated.
    if (depth == 0 ||  (m_board->whosTurn() == BLACK && !m_board->legalMovesAvailable()))
    {
        return evaluateBoard();
    }
    double maxValue = alpha;

    if (m_board->whosTurn() == BLACK)
    {
        legalMoves = m_board->getLegalMoves();
    }
    else
    {
        qDebug() << "get the maximizing palyer?!?!?!";
    }

    QPair<int,int> move;
    foreach (move, legalMoves.keys())
    {
        m_board->makeMove(move.first,move.second);
        double value = min(depth-1, maxValue, beta);
        m_board->undoMove();
        if (value > maxValue)
        {
            maxValue = value;
            if (maxValue >= beta)
            {
                break;
            }
            if (depth == m_startingDepth)
            {
                m_savedMove = move;
            }

        }
    }
    return maxValue;
}

double AI::min(int depth, double alpha, double beta)
{
    QMap<QPair<int,int>, QVector<QPair<int,int> > > legalMoves;
    // if search depth is reached or minimizing player (WHITE) has no moves left the board is evaluated.
    if (depth == 0 ||  (m_board->whosTurn() == WHITE && !m_board->legalMovesAvailable()))
    {
        return evaluateBoard();
    }
    double minValue = beta;
    //generiereMoeglicheZuege(spieler_min);

    if (m_board->whosTurn() == WHITE)
    {
        legalMoves = m_board->getLegalMoves();
    }
    else
    {
        qDebug() << "get the minimizing palyer?!?!?!";
    }


    QPair<int,int> move;
    foreach (move, legalMoves.keys())
    {
        m_board->makeMove(move.first,move.second);
        double value = max(depth-1, alpha, minValue);
        m_board->undoMove();
        if (value < minValue)
        {
            minValue = value;
            if (minValue <= alpha)
            {
                break;
            }
        }
    }
    return minValue;
}

double AI::evaluateBoard()
{
    double evaluation = 0;
    QMap<QPair<int,int>, QVector<QPair<int,int> > > legalMoves = m_board->getLegalMoves();

    // legal moves count
    double numberOfLegalMoves = legalMoves.count();
    double legalMovesCount = MOVESCOUNT*numberOfLegalMoves;

    // disk count
    double numberOfPlayerDisks = m_board->countPlayerDisks();
    double diskCount = DISCOUNT*numberOfPlayerDisks;

    evaluation += legalMovesCount + diskCount;


    QPair<int, int> boardPosition;
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            boardPosition = QPair<int, int>(x,y);
            if (legalMoves.contains(boardPosition))
            {
                evaluation += m_heuristic[x][y];
            }

        }
    }



    // check how many moves opponent can do after this move. (commented because too time consuming)
//    QPair<int, int> move;
//    QMap<QPair<int,int>, QVector<QPair<int,int> > > legalOpponentMoves;
//    foreach (move, legalMoves.keys())
//    {
//        m_board->makeMove(move.first,move.second);
//        legalOpponentMoves = m_board->getLegalMoves();

//        // high rating if opponent has no moves left
//        if (legalOpponentMoves.keys().isEmpty())
//            evaluation += INFTY;

//        QPair<int, int> boardPosition;
//        for (int x = 0; x < 8; x++)
//        {
//            for (int y = 0; y < 8; y++)
//            {
//                boardPosition = QPair<int, int>(x,y);
//                if (legalOpponentMoves.contains(boardPosition))
//                {
//                    // negative sign here because it is opponents turn.
//                    evaluation -= m_heuristic[x][y];
//                }
//            }
//        }
//        m_board->undoMove();
//    }



    return evaluation;

}

