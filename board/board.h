#ifndef BOARD_H
#define BOARD_H


#define BOARD_SIZE 8

#include <QObject>

#include "board/square.h"

class Board : public QObject
{
    Q_OBJECT
public:
    explicit Board(QObject *parent = 0);



    Square getSquare(int x, int y) const;
    //void setSquare(int x, int y, Square *square);

    void newBoard();
    void setSuggestion();
    void setAllowed();
    void setPlayers();
    void setTestSquare();

    bool checkValidMove(int x, int y);


private:
    QVector<QVector<Square* > > m_boardMatrix;

signals:

public slots:
};

#endif // BOARD_H
