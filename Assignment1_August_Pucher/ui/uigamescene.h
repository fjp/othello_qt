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

/**
 * @brief The UIGameScene class stores the graphical representation of the board using
 * UISquare class. The GameEngine uses this class to redraw the board matrix from the Board class.
 * This class also forwards mouse release events to the GameEngine made by the user.
 */
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

    /**
     * @brief setSquareState
     * @param x column of the board.
     * @param y row of the board.
     * @param state new state of the square at position (x,y).
     */
    void setSquareState(int x, int y, State state);

    /**
     * @brief redrawBoard redraws every single square with the current state of the
     * board matrix from the passed Board class instance.
     * @param board Board class that holds the current board matrix with its states.
     */
    void redrawBoard(Board *board);

    /**
     * @brief m_sizeSceneRect size (width and height) of the whole board.
     */
    double m_sizeSceneRect;

    /**
     * @brief m_squareSize size (width and height) of a single square.
     */
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
     * @brief m_board is a 2x2 matrix which used to store pointers to UISquares.
     * Initialization is done using drawBoard() and the State of the signel UISquares
     * are updated using the public setSquareState() function.
     */
    QVector< QVector<UISquare *> > m_board;

    QVector< QGraphicsSimpleTextItem *> m_edgeText;

};

#endif // GAMESCENE_H
