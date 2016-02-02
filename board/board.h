#ifndef BOARD_H
#define BOARD_H

#include <QObject>

class Board : public QObject
{
    Q_OBJECT
public:
    explicit Board(QObject *parent = 0);

private:
    enum { BoardWidth = 8, BoardHeight = 8 };

signals:

public slots:
};

#endif // BOARD_H
