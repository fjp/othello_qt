#include "square.h"

Square::Square(int col, int row)
{
    m_col = col;
    m_row = row;
    initSquare();
}

void Square::initSquare()
{
    setSquareState(Square::BOARD);
}

Square::State Square::getSquareState(void)
{
    return m_squareState;

}

void Square::setSquareState(State state)
{
    m_squareState = state;
}


