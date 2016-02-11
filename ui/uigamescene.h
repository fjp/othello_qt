#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QObject>
#include <QVector>
#include <QtWidgets>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QGraphicsSimpleTextItem>

#include "uisquare.h"
#include "board/board.h"
#include "define.h"

class UIGameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @brief UIGameScene
     * @param parent
     */
    UIGameScene(QObject * parent);
    ~UIGameScene();

    void setSquareState(int x, int y, State state);
    void redrawBoard(Board *board);

    double m_sizeSceneRect;
    double m_squareSize;

signals:
    /**
     * @brief newMouseEvent is used to inform the GameEngine where the user
     * pressed inside this UIGameScene. The cursor position is processed
     * inside slot mouseReleased(QPoint position) of the GameEngine class.
     * @param position
     */
    void newMouseEvent(QPointF position);

public slots:
    /**
     * @brief mouseReleaseEvent this event happens when the user releases
     * the mouse inside this UIGameScene. These events are used to forward
     * the current mouse position to the GameEngine using the signal newMouseEvent().
     * The connect of the Signal and Slot is done inside the MainWindow class.
     * @param mouseEvent defines which mouse button was released.
     */
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);

private:
    /**
     * @brief initUIGameScene sets a fixed size of the scene rectangle and calls drawBoard()
     */
    void initUIGameScene();
    /**
     * @brief drawBoard is only called to initialize the board when new game starts
     */
    void drawBoard();
    //void generatePlayers();

    /**
     * @brief m_board is a 2x2 matrix which used to store pointers UISquares.
     * Initialization is done using drawBoard() and the State of the signel UISquares
     * are updated using the public setSquareState() function.
     */
    QVector< QVector<UISquare *> > m_board;

    QVector< QGraphicsSimpleTextItem *> m_edgeText;

};

#endif // GAMESCENE_H
