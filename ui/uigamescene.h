#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QObject>
#include <QVector>
#include <QtWidgets>
#include <QGraphicsScene>

#include "uisquare.h"
#include "uidisk.h"

class UIGameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    UIGameScene(QObject * parent);
    UIGameScene(QObject * parent, int numberSquareX, int numberSquareY);
    ~UIGameScene();

    void setSquareState(int x, int y, UISquare::State state);

    UIDisk *m_player1;
    UIDisk *m_player2;

private:
    void initUIGameScene();
    void drawBoard();
    void setBackgroundBlocks();
    void generatePlayers();
    QVector< QVector<UISquare> > m_board;
    QVector<UISquare> m_backgroundBlocks;
    int m_numberSquareX;
    int m_numberSquareY;
    double m_squareWidth;
    double m_squareHeight;
};

#endif // GAMESCENE_H
