#include "board.h"

const int Board::m_direction[8][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

Board::Board(QObject *parent, int numberOfHumans) : QObject(parent),
    m_boardMatrix(BOARD_SIZE, QVector<State >(BOARD_SIZE))

{
    m_boardStack = new QStack<Board *>; // init play history with 60 boards

    m_numberOfActualMoves = 0;
    m_numberOfTotalMoves = 0;
    m_movesAvailable = true;
    newBoard(numberOfHumans);
}

Board::Board(const Board &board)
{

    m_currentPlayer = board.m_currentPlayer;
    m_opponentPlayer = board.m_opponentPlayer;

    // same board stack for whole game.
    m_boardStack = board.m_boardStack;

    m_gameOver = board.m_gameOver;


    for (int x = 0; x < BOARD_SIZE; x++)
    {
        m_boardMatrix.resize(8);
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            m_boardMatrix[x].resize(8);
        }
    }

    // copy the board matrix
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            m_boardMatrix[x][y] = board.m_boardMatrix.at(x).at(y);
        }
    }
}

State Board::getState(int x, int y) const
{
    return m_boardMatrix.at(x).at(y);
}

void Board::setAllowed(QMap<QPair<int, int>, QVector<QPair<int, int> > > legalMoves)
{
    // update the board
    QPair<int, int> point;
    foreach (point, legalMoves.keys())
    {
        m_boardMatrix[point.first][point.second] = ALLOWED;
    }


}

void Board::newBoard(int numberOfHumans)
{
    if (numberOfHumans == 2)
    {
        m_currentPlayer = new Player(this, BLACK, HUMAN);
        m_opponentPlayer = new Player(this, WHITE, HUMAN);
    }
    else if (numberOfHumans == 1)
    {
        // TODO let palyer choose color
        m_currentPlayer = new Player(this, BLACK, COMPUTER);
        m_opponentPlayer = new Player(this, WHITE, HUMAN);
    }

    m_numberOfActualMoves = 0;
    m_numberOfTotalMoves = 0;

    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {

            m_boardMatrix[x][y] = BOARD;
        }
    }

    m_boardMatrix[3][3] = WHITE;
    m_boardMatrix[3][4] = BLACK;
    m_boardMatrix[4][3] = BLACK;
    m_boardMatrix[4][4] = WHITE;


    setAllowed(getLegalMoves());
    emit signalBoardChanged();

    m_numberOfBlackDisks = 2;
    m_numberOfWhiteDisks = 2;
    m_numberOfDisks = 4;

    m_gameOver = false;

    storeBoardOnStack();
}

void Board::storeBoardOnStack()
{
    Board *boardToStore = new Board(*this);
    m_boardStack->append(boardToStore);
    qDebug() << "boardStack size is" << m_boardStack->size();
}

void Board::togglePlayer()
{
    Player *dummyPlayer;
    dummyPlayer = m_currentPlayer;
    m_currentPlayer = m_opponentPlayer;
    m_opponentPlayer = dummyPlayer;
}

void Board::makePass()
{
    if (m_currentPlayer->m_color == BLACK)
    {
        // TODO emit
        //updateInfoText("Black passed, it's White's turn");
    }
    else if (m_currentPlayer->m_color == WHITE)
    {
        // TODO emit
        //updateInfoText("White passed, it's Black's turn");
    }
    m_numberOfTotalMoves++;
    togglePlayer();

}

void Board::countDisks(void)
{
    m_numberOfBlackDisks = 0;
    m_numberOfWhiteDisks = 0;
    m_numberOfDisks = 0;


    State currentOwner;
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            currentOwner = getState(x, y);
            if (currentOwner == BLACK)
            {
                m_numberOfBlackDisks++;
                m_numberOfDisks++;
            }
            else if (currentOwner == WHITE)
            {
                m_numberOfWhiteDisks++;
                m_numberOfDisks++;
            }
        }
    }
}

bool Board::legalMove(int x, int y)
{
    qDebug() << "--------------------------- Check new legal Move at -------------------------------";
    // check if inside board
    if(!onBoard(x, y))
    {
        return false;
    }
    // check if pressed square is occupied by player
    if (getState(x, y) == BLACK || getState(x, y) == WHITE)
    {
        return false;
    }
    qDebug() << "Board(" << x << "," << y << ") is not occupied" << "Square State" << m_boardMatrix[x][y];
    // test left for possible flips
    bool moveLegal = false;
    for(int dir = 0; dir < BOARD_SIZE; dir++)
    {
        int dx = m_direction[dir][0];
        int dy = m_direction[dir][1];
        int tx = x + 2*dx;
        int ty = y + 2*dy;
        // need to be at least 2 grids away from the edge
        if (!onBoard(tx, ty))
        {
            continue;
        }
        qDebug() << "(tx,ty) = (" << tx << "," << ty << ") is on the board";

        // oppenent disk must be adjacent in the current direction
        if (getState(x+dx, y+dy) != getOtherPlayer(m_currentPlayer))
        {
            qDebug() << "but there is no adjacent opponent" << getOtherPlayer(m_currentPlayer);
            continue;
        }
        qDebug() << "Adjacent opponent" << getOtherPlayer(m_currentPlayer) << "found at ([x+dx],[y+dy]) = (" << x+dx << "," << y+dy << ") CurrentPlayer is" << m_currentPlayer->m_color;

        // as long as we stay on the board going in the current direction, we search for the surrounding disk
        while(onBoard(tx, ty) && getState(tx,ty) == getOtherPlayer(m_currentPlayer))
        {
            tx += dx;
            ty += dy;
        }

        // if we are still on the board and we found the surrounding disk in the current direction
        // the move is legal.
        if(onBoard(tx, ty) && getState(tx,ty) == m_currentPlayer->m_color)
        {
            qDebug() << "Found surrounding disk of Player" << m_currentPlayer->m_color << "at (tx,ty) = (" << tx << "," << ty << ")";
            moveLegal = true;
            break;
        }
    }
    qDebug() << "Board::legalMove" << moveLegal;
    return moveLegal;

}

bool Board::legalMovesAvailable()
{
    //m_movesAvailable = (getLegalMoves().isEmpty() == false);

    //return m_movesAvailable;
    return true;

}

QMap<QPair<int,int >, QVector<QPair<int,int > > > Board::getLegalMoves()
{
    QMap<QPair<int,int >, QVector<QPair<int,int > > > legalMoves;
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            if (getState(x,y) == m_currentPlayer->m_color || getState(x,y) == m_opponentPlayer->m_color)
            {
                continue;
            }


            QVector<QPair<int,int > > flipped;
            // check if move (x,y) is legal
            for(int dir = 0; dir < BOARD_SIZE; dir++)
            {
                int dx = m_direction[dir][0];
                int dy = m_direction[dir][1];
                int tx = x + 2*dx;
                int ty = y + 2*dy;
                // need to be at least 2 grids away from the edge
                if (!onBoard(tx, ty))
                {
                    continue;
                }
                // oppenent piece must be adjacent in the current direction
                if (getState(x+dx,y+dy) != getOtherPlayer(m_currentPlayer))
                {
                    continue;
                }
                // as long as we stay on the board going in the current direction, we search for the surrounding disk
                while(onBoard(tx, ty) && getState(tx,ty) == getOtherPlayer(m_currentPlayer))
                {
                    tx += dx;
                    ty += dy;
                }
                // if we are still on the board and we found the surrounding disk in the current direction
                // the move is legal.

                // go back and flip the pieces if move is legal
                if(onBoard(tx, ty) && getState(tx,ty) == m_currentPlayer->m_color)
                {
                    tx -= dx;
                    ty -= dy;

                    while(getState(tx,ty) == getOtherPlayer(m_currentPlayer))
                    {
                        //qDebug() << "Flipping" << tx << "," << ty;
                        //m_boardMatrix[tx][ty] = m_currentPlayer->m_color;
                        QPair<int,int> point = QPair<int,int>(tx,ty);
                        flipped.append(point);

                        tx -= dx;
                        ty -= dy;
                    }

                    //m_legalMoves.insert(QPoint(x,y)= flipped.append(QPoint(tx,ty));

                    // check if the current position flipped any disks aka this was a legal move
                    if (flipped.isEmpty() == false)
                    {
                        // append current position
                        QPair<int,int> point = QPair<int,int>(x,y);

                        if (!flipped.contains(point))
                            flipped.append(point);

                        legalMoves.insert(point, flipped);

                        //qDebug() << legalMoves;
                    }
                }

            }

        }
    }
    qDebug() << legalMoves;
    return legalMoves;
}


void Board::makeMove(int x, int y)
{
    // convert the position into QPair
    QPair<int,int> move = QPair<int, int>(x,y);

    QMap<QPair<int,int >, QVector<QPair<int,int > > > legalMoves = getLegalMoves();


    //setAllowed(legalMoves);
    //emit signalBoardChanged();

    QVector<QPair<int, int> > flipped = legalMoves.value(move);

    m_flipped.insert(move, flipped);

    QPair<int, int> flip;
    foreach (flip, flipped)
    {
        m_boardMatrix[flip.first][flip.second] = m_currentPlayer->m_color;
    }

    // revert state of previously allowed moves
    QPair<int,int> revertMove;
    foreach (revertMove, legalMoves.keys())
    {
        if (revertMove != move)
            m_boardMatrix[revertMove.first][revertMove.second] = BOARD;
        else
            m_boardMatrix[revertMove.first][revertMove.second] = m_currentPlayer->m_color;
    }


    m_numberOfActualMoves++;
    m_numberOfTotalMoves++;



    togglePlayer();

    setAllowed(getLegalMoves());


    qDebug() << getLegalMoves();
    emit signalBoardChanged();

    storeBoardOnStack();
}

State Board::whosTurn()
{
    return m_currentPlayer->m_color;
}

bool Board::undoMove()
{
    qDebug() << "Called undoMove";
    if (m_numberOfActualMoves > 0)
    {

        Board *prevBoard = m_boardStack->at(m_numberOfActualMoves-1);
        m_boardStack->pop();

        this->m_gameOver = prevBoard->m_gameOver;
        this->m_currentPlayer = prevBoard->m_currentPlayer;
        this->m_opponentPlayer = prevBoard->m_opponentPlayer;


        for (int x = 0; x < BOARD_SIZE; x++)
        {
            for (int y = 0; y < BOARD_SIZE; y++)
            {
                this->m_boardMatrix[x][y] = prevBoard->m_boardMatrix[x][y];
            }
        }



        //setAllowed(getLegalMoves());

        //togglePlayer();
        emit signalBoardChanged();


        m_numberOfActualMoves--;
        m_numberOfTotalMoves--;
    }

}

bool Board::onBoard(int x, int y)
{
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

State Board::getOtherPlayer(Player *currentPlayer)
{
    if (currentPlayer->m_color == BLACK)
    {
        return WHITE;
    }
    else if (currentPlayer->m_color == WHITE)
    {
        return BLACK;
    }
}
