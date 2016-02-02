#ifndef UISQUARE_H
#define UISQUARE_H

#include <QtWidgets>
#include <QObject>
#include <QGraphicsItem>

class UISquare : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum State {BOARD, BLACK, WHITE, ALLOWED, SUGGESTED};

    UISquare();
    UISquare(const double height, const double width);

    // Edit Copy Constructor
    UISquare(const UISquare &square);
    ~UISquare();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setState(const State state);
    State getState() const;
    void setPosition(const double positionX, const double positionY);
    void setSize(const double height, const double width);

public slots:


private:
    void initSquare();
    State m_state;
    State m_stateBuf;
    double m_positionX;
    double m_positionY;
    double m_height;
    double m_width;
    QRectF *m_squareState;
    QRectF *m_allowedSquare;
    QRectF *m_suggestedSquare;
    QRectF *m_boardSquare;
    QRectF *m_blackSquare;
    QRectF *m_whiteSquare;
};

#endif // UISQUARE_H
