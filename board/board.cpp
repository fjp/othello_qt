#include "board.h"

Board::Board(QObject *parent) : QObject(parent),
  m_boardMatrix(BOARD_SIZE, QVector<Square* >(BOARD_SIZE))
{
    newBoard();
}

void Board::newBoard()
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {

            m_boardMatrix[col][row] = new Square(col,row);
        }
    }

    m_boardMatrix[4][4]->setSquareState(Square::WHITE);
    m_boardMatrix[4][5]->setSquareState(Square::BLACK);
    m_boardMatrix[5][4]->setSquareState(Square::WHITE);
    m_boardMatrix[5][5]->setSquareState(Square::BLACK);


}

void Board::setTestSquare()
{

}
