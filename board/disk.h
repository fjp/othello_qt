#ifndef DISK_H
#define DISK_H

#include <QWidget>

#include "square.h"

class disk : public Square
{
private:
    enum color {black, white};

public:
    disk();

    color getColor(int x, int y);
};

#endif // DISK_H
