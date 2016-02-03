#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsItem>
#include <QPoint>

class Square : public QGraphicsItem
{

public:
    Square();
    int getSize(void);

    enum State {BOARD, BLACK, WHITE, ALLOWED, SUGGESTED};

    int m_positionX;
    int m_positionY;



private:
    QPoint position;
    QRectF *square;


};

#endif // SQUARE_H
