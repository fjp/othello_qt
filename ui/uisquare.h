#ifndef UISQUARE_H
#define UISQUARE_H

#include <QtWidgets>
#include <QObject>
#include <QGraphicsItem>

#include "player/player.h"

class UISquare : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum State {NONE, BOARD, BLACK, WHITE, ALLOWED, SUGGESTED};

    /**
     * @brief UISquare main constructor. Position on the board is used for debugging.
     * @param x
     * @param y
     */
    UISquare(int x, int y, State state = NONE, Player::Color currentOwner = Player::NONE);
    UISquare(const double height, const double width);

    // Edit Copy Constructor
    UISquare(const UISquare &square);
    ~UISquare();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setState(const State state, const Player::Color currentOwner = Player::NONE);
    State getState() const;
    void setPosition(const double boardPositionX, const double boardPositionY);
    void setSize(const double height, const double width);

public slots:


private:
    void initSquare();
    void setSquareSize();
    void setDiskSize();

    State m_state;

    double m_boardPositionX;
    double m_boardPositionY;

    int m_x;
    int m_y;

    Player::Color m_currentOwner;

    double m_squareHeight;
    double m_squareWidth;

    double m_diskHeight;
    double m_diskWidth;
    double m_margin;

    QRectF *m_ellipse;
};

#endif // UISQUARE_H
