#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QTextEdit>
#include <QDebug>
#include <QTimer>
#include <QMouseEvent>
#include <QVector>
#include <QMessageBox>

#include "board/board.h"
#include "player/player.h"
#include "ui/uigamescene.h"
#include "ai.h"

class GameEngine : public QObject
{
    Q_OBJECT
public:
    GameEngine(QObject* parent, UIGameScene* uiGameScene, QTextEdit *eventList, QTextEdit *infoList);
    ~GameEngine();

    void startGame(int numberOfHumans = 1, double timeLimit = 10);

    Board *m_board;
    
public slots:
    void mouseReleased(QPointF point);
    void updateUISquare(int x, int y, State currentPlayer);
    void updateUIGameScene();

private:
    /**
     * @brief gameOver test if game is over.
     */
    bool gameOver(void);

    bool m_gameOver;

    /**
     * @brief getGameStats summarize game statistics
     */
    QString getGameStats(void);


    void eventHandling(int x, int y);

    void makeComputerMove();

    /**
     * @brief togglePlayer
     */
    void togglePlayer();

    /**
     * @brief makeMove first checks if the intended move is valid using Board::legalMove(int,int,Player::Color)
     * If the move is valid, squares are colored accordingly by calling UIGameScene
     * and the actual m_board is updated.
     * updated
     * @param x
     * @param y
     */
    //void makeMove(int x, int y); TODO moved to board -> copy comment.

    QVector<QPoint> m_legalMoves;


    UIGameScene* m_uiGameScene;
    QTextEdit *m_eventList;
    QTextEdit *m_infoList;

    /**
     * @brief updateInfoText
     * @param string
     */
    void updateInfoText(QString string);
    void updateEventText(QString string);

    int m_numberOfHumans;

    /**
     * @brief m_gameEvents sequence of moves including passes.
     */
    QList<int> m_gameEvents;

    /**
     * @brief numberOfActualMoves number of actual moves without passes.
     */
    // TODO move comment to boardint m_numberOfActualMoves;

    /**
     * @brief numberOfTotalMoves number of total moves including passes.
     */
    int m_numberOfTotalMoves;

    /**
     * @brief m_timeLimit user defined max time limit for AI.
     */
    double m_timeLimit;

    /**
     * @brief m_elapsedTime used to display the time needed to make a move.
     */
    double m_elapsedTime;

    /**
     * @brief getThinkingTime returns the time in seconds needed for a move.
     * @return
     */
    double getThinkingTime();

    Player *m_currentPlayer;
    Player *m_opponentPlayer;

    /**
     * @brief m_thinkingTime displays the time needed to make a move.
     */
    QElapsedTimer m_thinkingTime;


    AI *m_ai;


private slots:

};

#endif // GAMEENGINE_H
