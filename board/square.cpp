#include "square.h"

Square::Square()
{
    position = QPoint();
    square = new QRectF();

}

int Square::getSize()
{
    return square->height();
}
