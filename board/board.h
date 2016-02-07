#ifndef BOARD_H
#define BOARD_H


#define BOARD_SIZE 8

#include <QObject>
#include <QDebug>

#include "board/square.h"
#include "player/player.h"

class Board : public QObject
{
    Q_OBJECT
public:
    explicit Board(Player *currentPlayer, QObject *parent = 0);

    const int m_direction[8][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};


    Square *getSquare(int x, int y);
    Square::State getSquareState(int x, int y);
    //void setSquare(int x, int y, Square *square);

    void newBoard();
    void setSuggestion();
    void setAllowed();
    void setPlayers();
    void setTestSquare();

    bool legalMove(int x, int y);

    /**
     * @brief getLegalMoves fill the provided QVector legalMoves with Squares
     * that are allowed to place disks on for the current player.
     * @param legalMoves
     * @return
     */
    bool getLegalMoves(QVector<Square* > legalMoves);
    void makeMove(int x, int y);
    //bool findLegalMoves(bool *legalMoves);

    /**
     * @brief onBoard checks if a position is on the board
     * @param x
     * @param y
     * @return
     */
    bool onBoard(int x, int y);

    /**
     * @brief getOtherPlayer get the color of opponent
     * @param currentPlayer
     * @return
     */
    Player::Color getOtherPlayer(Player *currentPlayer);


    bool checkValidMove(int x, int y);


private:
    QVector<QVector<Square* > > m_boardMatrix;
    Player *m_currentPlayer;


signals:
    void signalBoardChanged(int x, int y, Player::Color color);

public slots:
};

#endif // BOARD_H
