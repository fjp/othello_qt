#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsItem>
#include <QPoint>

#include "player/player.h"

class Square
{

public:
    Square(int col, int row);

    enum State {NONE, BOARD, BLACK, WHITE, ALLOWED, SUGGESTED};

    int m_col;
    int m_row;

    State getSquareState(void);
    void setSquareState(State state);

private:
    void initSquare();
    State m_squareState;
    Player *m_currentOwner;


};

#endif // SQUARE_H
