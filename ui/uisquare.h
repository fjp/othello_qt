#ifndef UISQUARE_H
#define UISQUARE_H

#include <QtWidgets>
#include <QObject>
#include <QGraphicsItem>

#include "define.h"

/**
 * @brief The UISquare class represents a single square inside the QGraphicsScene (UIGameScene).
 * It is used to show the different states of a square (BOARD, BLACK, WHITE, ALLOWED) to the user.
 * The board matrix 2x2 QVector of the UIGameScene class consists of these UISquares.
 */
class UISquare : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    /**
     * @brief UISquare main constructor. Position on the board is used for debugging.
     * @param x
     * @param y
     */
    UISquare(int x, int y, State state = NONE);
    UISquare(const double height, const double width);

    // Edit Copy Constructor
    UISquare(const UISquare &square);
    ~UISquare();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @brief setState update the state of the square according to passed
     * enum State {NONE, BOARD, BLACK, WHITE, ALLOWED, SUGGESTED}
     * @param state
     */
    void setUISquareState(const State state);
    State getUISquareState() const;
    void setPosition(const double boardPositionX, const double boardPositionY);
    void setSize(const double size);

private:
    void initSquare();
    void setSquareSize();
    void setDiskSize();

    State m_state;

    double m_boardPositionX;
    double m_boardPositionY;

    int m_x;
    int m_y;

    double m_squareSize;

    double m_diskSize;
    double m_margin;

    QRectF *m_ellipse;
};

#endif // UISQUARE_H
