#ifndef UISQUARE_H
#define UISQUARE_H

#include <QtWidgets>
#include <QObject>
#include <QGraphicsItem>

class UISquare : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum State {NONE, BOARD, BLACK, WHITE, ALLOWED, SUGGESTED};

    UISquare();
    UISquare(const double height, const double width);

    // Edit Copy Constructor
    UISquare(const UISquare &square);
    ~UISquare();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setState(const State state);
    State getState() const;
    void setPosition(const double boardPositionY, const double boardPositionX);
    void setSize(const double height, const double width);

public slots:


private:
    void initSquare();
    void setSquareSize();
    void setDiskSize();

    State m_state;

    double m_boardPositionX;
    double m_boardPositionY;

    double m_squareHeight;
    double m_squareWidth;
    double m_diskHeight;
    double m_diskWidth;
    double m_margin;

    QRectF *m_ellipse;
};

#endif // UISQUARE_H
