#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsItem>
#include <QPoint>

class Square : public QGraphicsItem
{

public:
    Square();
    int getSize(void);

private:
    QPoint position;
    QRectF *square;


};

#endif // SQUARE_H
