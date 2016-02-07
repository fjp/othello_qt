#include "board.h"

Board::Board(QObject *parent) : QObject(parent),
  m_boardMatrix(BOARD_SIZE, QVector<Square* >(BOARD_SIZE))
{
    newBoard();
}

Square *Board::getSquare(int x, int y)
{
    return m_boardMatrix[x][y];
}

void Board::newBoard()
{
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {

            m_boardMatrix[x][y] = new Square(x,y);
        }
    }

    m_boardMatrix[3][3]->setSquareState(Square::BLACK);
    m_boardMatrix[3][4]->setSquareState(Square::WHITE);
    m_boardMatrix[4][3]->setSquareState(Square::WHITE);
    m_boardMatrix[4][4]->setSquareState(Square::BLACK);
}

void Board::setTestSquare()
{

}

bool Board::legalMove(int x, int y, Player::Color currentPlayer)
{
    qDebug() << "--------------------------- Check new legal Move at -------------------------------";
    // check if inside board
    if(!onBoard(x, y))
    {
        return false;
    }
    // check if pressed square is occupied by player
    if (!m_boardMatrix[x][y]->isEmpty())
    {
        return false;
    }
    qDebug() << "Board(" << x << "," << y << ") is not occupied" << m_boardMatrix[x][y]->getOwner() << "Square State" << m_boardMatrix[x][y]->getSquareState();
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
        if (m_boardMatrix[x+dx][y+dy]->getOwner() != getOtherPlayer(currentPlayer))
        {
            QString string = QString(getOtherPlayer(currentPlayer));
            qDebug() << "but there is no adjacent opponent" << string;
            continue;
        }
        qDebug() << "Adjacent opponent" << getOtherPlayer(currentPlayer) << "found at ([x+dx],[y+dy]) = (" << x+dx << "," << y+dy << ") CurrentPlayer is" << currentPlayer;

        // as long as we stay on the board going in the current direction, we search for the surrounding disk
        while(onBoard(tx, ty) && m_boardMatrix[tx][ty]->getOwner() == getOtherPlayer(currentPlayer))
        {
            tx += dx;
            ty += dy;
        }

        // if we are still on the board and we found the surrounding disk in the current direction
        // the move is legal.
        if(onBoard(tx, ty) && m_boardMatrix[tx][ty]->getOwner() == currentPlayer)
        {
            qDebug() << "Found surrounding disk of Player" << currentPlayer << "at (tx,ty) = (" << tx << "," << ty << ")";
            moveLegal = true;
            break;
        }
    }
    qDebug() << "Board::legalMove" << moveLegal;
    return moveLegal;

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

Player::Color Board::getOtherPlayer(Player::Color currentPlayer)
{
    if (currentPlayer == Player::BLACK)
    {
        return Player::WHITE;
    }
    else if (currentPlayer == Player::WHITE)
    {
        return Player::BLACK;
    }
}
