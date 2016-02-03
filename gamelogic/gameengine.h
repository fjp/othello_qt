#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QMouseEvent>
#include <QVector>
#include <QMessageBox>

#include "gameevent.h"
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

    static QQueue<GameEvent*> eventQueue;

    Board *m_board;
    
public slots:
    void mouseReleased(QPointF point);
    void mouseReleaseEvent(QMouseEvent * event);

private:
    /// Game events are appended to the queue and processed by the logic
    //    QQueue<Event> eventQueue;       //-> in constructor

    //void createPlayers(int human_players);
    //void movePlayers();
    void eventHandling();

    bool checkValidMove(Player *player, Square *square);
    bool getValidMoves(Player* player);

    UIGameScene* m_uiGameScene;

    void updateUI(GameEvent *event, UISquare::State state);


    /**
     * @brief execute_move executes the allowed move
     * @param player which player shall move
     */
    void executeHumanMove(HumanPlayer *player, UISquare *uiSquare);
    void setStateInterfacePlayer(HumanPlayer *player, UISquare *uiSquare);

    int m_numberOfHumans;

    //QVector<QVector<Tile*> > map;

    QTimer loopQTimer;

    HumanPlayer* HumanPlayerB;
    HumanPlayer* HumanPlayerW;
    ComputerPlayer* m_computerPlayerB;
    ComputerPlayer* m_computerPlayerW;
    QList<Player *> players;

    QList<Square *> possibleSquares;


private slots:
    void counter();
};

#endif // GAMEENGINE_H
