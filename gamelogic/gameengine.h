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
#include "player/computerplayer.h"
#include "player/humanplayer.h"
#include "ui/uigamescene.h"

class GameEngine : public QObject
{
    Q_OBJECT
public:
    GameEngine(QObject* parent, UIGameScene* uiGameScene, QTextEdit *eventList, QTextEdit *infoList);
    ~GameEngine();

    void registerHumanPlayer(HumanPlayer player);

    void startGame(int numberOfHumans);

    Board *m_board;
    
public slots:
    void mouseReleased(QPointF point);
    void updateUI(int x, int y, Player::Color currentPlayer);

private:
    void createPlayers(int numberOfHumans);
    //void movePlayers();
    void eventHandling(int x, int y);
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
    //void makeMove(int x, int y);


    bool checkValidMove(Player *player, Square *square);
    bool getValidMoves(Player* player);

    UIGameScene* m_uiGameScene;
    QTextEdit *m_eventList;
    QTextEdit *m_infoList;


    void updateInfoText(QString string);
    void updateEventText(QString string);

    int m_numberOfHumans;

    Player *m_currentPlayer;
    Player *m_opponentPlayer;

    //QVector<QVector<Tile*> > map;

    QTimer loopQTimer;

    HumanPlayer* m_humanPlayerB;
    HumanPlayer* m_humanPlayerW;
    ComputerPlayer* m_computerPlayerB;
    ComputerPlayer* m_computerPlayerW;
    QList<Player *> players;

    QList<Square *> possibleSquares;


private slots:
    void counter();
};

#endif // GAMEENGINE_H
