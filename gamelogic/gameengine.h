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

/**
 * @brief The GameEngine class controls the course of the game by processing user input,
 * executing moves from humans and the computer and informing the user about events using
 * lists from the GUI. Furthermore it has an interface to the ui class UIGameScene to
 * evoke redraws of the board.
 */
class GameEngine : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief GameEngine initializes the passed pointers from the main window gui elements (textEdits).
     * Furthermore the pointer to GameEngine gets assigned to the corresponding member variable.
     * @param parent creating class.
     * @param uiGameScene pointer to UIGameScene class, used to update the graphical representaiton of the board.
     * @param eventList pointer to the textEdit that informs the user about the moves.
     * @param infoList pointer to the textEdit that informs the user about the current player and the game results.
     */
    GameEngine(QObject* parent, UIGameScene* uiGameScene, QTextEdit *eventList, QTextEdit *infoList);
    ~GameEngine();

    /**
     * @brief startGame reads the user settings, like number of humans, search depth (m_timeLimit),
     * connects the most of the signal and slot mechanism for redrawing the gui and updating the
     * textEdits and creates the classes important classes (AI, Board).
     * @param numberOfHumans number of human players. One: Human vs Computer, Two: Human vs Human.
     * @param timeLimit is the search depth of the used alpha-beta pruning algorithm.
     */
    void startGame(int numberOfHumans = 1, double timeLimit = 10);

    /**
     * @brief m_board points to the Board class that stores the board.
     * This representation is used to update the gui with the current states of the signle squares
     * of the board.
     */
    Board *m_board;
    
public slots:
    /**
     * @brief mouseReleased converts the position where the user clicked inside the GraphicsScene (UIGameScene),
     * to a row and column inside the board. The event is only forwarded to eventHandling() if it is a human
     * move.
     * @param point received mouse position from the GraphicsScene (UIGameScene).
     */
    void mouseReleased(QPointF point);

    /**
     * @brief updateUISquare DEPRECATED! this funciton was used to update single squres of the board on the
     * gui side.
     * @param x
     * @param y
     * @param currentPlayer
     */
    void updateUISquare(int x, int y, State currentPlayer);

    /**
     * @brief updateUIGameScene evokes a redraw of the whole board using the m_board member.
     */
    void updateUIGameScene();

    /**
     * @brief updateInfoTextPass informs the user about the current player and game result.
     * @param string passed informations which is shown to the user inside the textEdit.
     */
    void updateInfoTextPass(QString string);

private:
    /**
     * @brief gameOver test if game is over by looking for legalmoves for both players (current and opponent)
     * by using makePass of the Board class.
     */
    bool gameOver(void);

    /**
     * @brief m_gameOver stores the gamve over state of the game.
     */
    bool m_gameOver;

    /**
     * @brief getGameStats summarize game statistics like disk count and who wins the game.
     */
    QString getGameStats(void);


    /**
     * @brief eventHandling processes the passed position clicked by the user by executing
     * a move for the current player, if legal. After a human move, the function makeComputerMove()
     * is called if there is only one human player. This function also checks weather the game is over
     * using gameOver().
     * @param x
     * @param y
     */
    void eventHandling(int x, int y);

    /**
     * @brief makeComputerMove executes a move for a computer player with the help of the
     * AI class.
     */
    void makeComputerMove();

    /**
     * @brief m_uiGameScene pointer to the UIGameScene class to update the GUI with the current board square states.
     */
    UIGameScene* m_uiGameScene;

    /**
     * @brief m_eventList informs the user about the chosen moves (x,y) and the time needed.
     */
    QTextEdit *m_eventList;

    /**
     * @brief m_infoList informs the user who's turn it is and the game result.
     */
    QTextEdit *m_infoList;

    /**
     * @brief updateInfoText updates the GUI textEdit that informs the user about the current player
     * and the game result.
     * @param string
     */
    void updateInfoText(QString string);

    /**
     * @brief updateEventText updates the GUI textEdit that informs the user abou the chosen moves (x,y)
     * and the time needed for them.
     * @param string
     */
    void updateEventText(QString string);

    /**
     * @brief m_numberOfHumans lets the player choose between two human player or human vs computer.
     */
    int m_numberOfHumans;

    /**
     * @brief m_timeLimit is the user defined max search depth for the AI.
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

    /**
     * @brief m_thinkingTime displays the time needed to make a move.
     */
    QElapsedTimer m_thinkingTime;


    /**
     * @brief m_ai interface to the AI class that lets the computer find the best move using
     * alpha-beta pruning algorithm.
     */
    AI *m_ai;


    /**
     * @brief mapMoveToString converts the chosen move (x,y) to a string (A-H, 1-8).
     * @param x column of position.
     * @param y row of position.
     * @return
     */
    QString mapMoveToString(int x, int y);

};

#endif // GAMEENGINE_H
