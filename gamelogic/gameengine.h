#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
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
    GameEngine(QObject* parent, UIGameScene* uiGameScene);
    ~GameEngine();

    void registerHumanPlayer(HumanPlayer player);

    void startGame(int numberOfHumans);

    Board *m_board;
    
public slots:
    void mouseReleased(QPointF point);

private:
    void createPlayers(int human_players);
    //void movePlayers();
    void eventHandling(int col, int row);
    void nextPlayer();

    bool checkValidMove(Player *player, Square *square);
    bool getValidMoves(Player* player);

    UIGameScene* m_uiGameScene;

    void updateUI(int col, int row, UISquare::State state);


    /**
     * @brief execute_move executes the allowed move
     * @param player which player shall move
     */
    void executeHumanMove(HumanPlayer *player, UISquare *uiSquare);
    void setStateInterfacePlayer(HumanPlayer *player, UISquare *uiSquare);

    int m_numberOfHumans;

    Player *m_currentPlayer;

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
