#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsItem>
#include <QPoint>
#include <QDebug>

#include "player/player.h"

class Square
{

public:
    Square(int x, int y);

    enum State {NONE, BOARD, BLACK, WHITE, ALLOWED, SUGGESTED};

    int m_x;
    int m_y;

    /**
     * @brief getSquareState returns the current state of the square stored in m_squareState.
     * @return m_squareState which can be one of the enum State.
     */
    State getSquareState(void);

    /**
     * @brief isEmpty determins if a square is either of enum State BOARD, ALLOWED or SUGGESTED
     * if so, the function returns true.
     * @return true if square is not occupied by a player.
     */
    bool isEmpty();

    void setSquareState(State state);

    Player::Color getOwner(void);
    void setOwner(Player::Color currentOwner);


private:
    void initSquare();
    State m_squareState;
    Player::Color m_currentOwner;


};

#endif // SQUARE_H
