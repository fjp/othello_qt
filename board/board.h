#ifndef BOARD_H
#define BOARD_H

#define BOARD_SIZE 8

#include <QObject>
#include <QDebug>
#include <QMap>
#include <QVector>
#include <QStack>
#include <QPair>

#include "player/player.h"

#include "define.h"

class Board : public QObject
{
    Q_OBJECT
public:
    Board(QObject *parent = 0, int numberOfHumans = 2);
    Board(const Board &board);

    static const int m_direction[8][2];

    State getState(int x, int y) const;

    void setAllowed(QMap<QPair<int,int >, QVector<QPair<int,int > > > legalMoves);

    void newBoard(int numberOfHumans);

    void storeBoardOnStack();

    void setPlayers();

    void togglePlayer();

    /**
     * @brief makePass used if there are no legal moves left for the current player
     */
    void makePass();

    /**
     * @brief countDisks count number of black, white and total disks
     * and store it in the corresponding member variables.
     */
    void countDisks(void);



    /**
     * @brief countPlayerDisks counts the disk of the current player of the board.
     * This function is used for the evaluation function inside the AI class.
     * @return
     */
    int countPlayerDisks(void);

    int m_numberOfBlackDisks;
    int m_numberOfWhiteDisks;
    int m_numberOfDisks;

    bool m_gameOver;


    /**
     * @brief legalMove check if the move at position (x,y) is legal.
     * @param x
     * @param y
     * @return
     */
    bool legalMove(int x, int y);

    bool legalMovesAvailable();


    QMap<QPair<int,int>, QVector<QPair<int,int> > > getLegalMoves();
    QMap<QPair<int,int >, QVector<QPair<int,int > > > m_prevLegalMoves;

    QMap<QPair<int,int>, QVector<QPair<int,int > > > m_flipped;

    bool m_movesAvailable;

    QVector<Board *> makeLegalMoves();

    /**
     * @brief makeMove actually make a move that is legal.
     * @param x
     * @param y
     */
    void makeMove(int x, int y);

    /**
     * @brief whosTurn returns the color of the current player stored in m_currentPlayer.
     * @return
     */
    State whosTurn();

    /**
     * @brief whosTurnType returns the type of the current player stored in m_currentPlayer.
     * @return
     */
    Type whosTurnType();


    /**
     * @brief onBoard checks if a position or move is on the board
     * @param x
     * @param y
     * @return
     */
    bool onBoard(int x, int y);

    /**
     * @brief getOtherPlayer used to get the color of the opponent
     * @param player
     * @return
     */
    State getOtherPlayer(Player *player);


    /**
     * @brief m_boardStack stores the boards according to the made moves.
     * Mainly used for the AI to unwind the recursion.
     */
    QStack<Board* > *m_boardStack;

    int m_numberOfActualMoves;
    int m_numberOfTotalMoves;


private:
    QVector<QVector<State > > m_boardMatrix;
    //QMap<QPoint, State> m_boardMatrix;
    Player *m_currentPlayer;
    Player *m_opponentPlayer;


signals:
    void signalBoardChanged();
    void signalUpdateInfo(QString);

public slots:
    /**
     * @brief undoMove get the last board from the board stack.
     * @return true if undo was possible.
     */
    bool undoMove();
};

#endif // BOARD_H
