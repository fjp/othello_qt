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

/**
 * @brief The Board class holds the board matrix and stores every board on a stack with
 * the current and opponent player.
 * It is used to find all allowed moves for the current player and actually execute them.
 */
class Board : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Board initialize the member variables and create a new board matrix by calling newBoard(numberOfHumans).
     * @param parent class that created the Board.
     * @param numberOfHumans is the set number of humans inside the GUI.
     */
    Board(QObject *parent = 0, int numberOfHumans = 2);

    /**
     * @brief Board copy constructor is used to store the boards on the stack.
     * The storeBoardOnStack() function, which uses the copy constructor, is called after every move and pass.
     * @param board the current board to store on the stack.
     */
    Board(const Board &board);

    /**
     * @brief m_direction is a member that is used to check all directions for legal moves.
     */
    static const int m_direction[8][2];

    /**
     * @brief getState returns the current State of the board at position x and y.
     * @param x column of the board matrix.
     * @param y row of the board matrix.
     * @return state of the chosen position (x,y).
     */
    State getState(int x, int y) const;

    /**
     * @brief setAllowed updates the board matrix with the allowed moves for the current player.
     * @param legalMoves the list with allowed moves for the current player.
     * As parameter getLegalMoves() is usually used.
     */
    void setAllowed(QMap<QPair<int,int >, QVector<QPair<int,int > > > legalMoves);

    /**
     * @brief newBoard initializes the board with the number of set human players (and computer).
     * Updates the board matrix with the 2x2 diagonal beginning and sets the allowed moves for
     * the black player using setAllowed().
     * @param numberOfHumans
     */
    void newBoard(int numberOfHumans);

    /**
     * @brief storeBoardOnStack uses the copy constructor to store the current board on
     * the "global" stack which is used for alpha-beta pruning algorithm and undoing a move.
     * This funciton is called after a move and a pass.
     */
    void storeBoardOnStack();

    /**
     * @brief togglePlayer adjusts the pointers of the current and opponent player.
     * Furthermore it sets the allowed moves and evokes a redraw of the board using signalBoardChanged().
     */
    void togglePlayer();

    /**
     * @brief makePass used if there are no legal moves left for the current player
     * This functions calls storeBoardOnStack() to register the pass.
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
     * @param x column of the board
     * @param y row of the board
     * @return true if move at position (x,y) is legal.
     */
    bool legalMove(int x, int y);

    /**
     * @brief legalMovesAvailable returns true if the current player has legal moves available.
     * @return
     */
    bool legalMovesAvailable();


    /**
     * @brief getLegalMoves stores the legal moves for the current player and the therefore happening
     * disk flips inside a map. The keys are the available legal moves. Its corresponding values
     * are QVectors with the disks that will be flipped (taking a key(=move)).
     * @return
     */
    QMap<QPair<int,int>, QVector<QPair<int,int> > > getLegalMoves();

    bool m_movesAvailable;

    /**
     * @brief makeMove execute a move, at position (x,y), for the current player that is legal
     * and switches to the opponent user by calling togglePlayer().
     * @param x column of the move.
     * @param y row of the move.
     */
    void makeMove(int x, int y);

    /**
     * @brief whosTurn returns the color of the current player stored in m_currentPlayer.
     * @return Color of current player.
     */
    State whosTurn();

    /**
     * @brief whosTurnType returns the type of the current player stored in m_currentPlayer.
     * @return Type of current player.
     */
    Type whosTurnType();


    /**
     * @brief onBoard checks if a position or move is on the board.
     * @param x column of the position.
     * @param y row of the position.
     * @return ture if position (x,y) is on the board, false if outisde.
     */
    bool onBoard(int x, int y);

    /**
     * @brief getOtherPlayer used to get the color of the opponent
     * @param pointer to a player (current or opponent).
     * @return the color of the other player depending on the passed player.
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
    /**
     * @brief m_boardMatrix holds the states of every square on the board.
     */
    QVector<QVector<State > > m_boardMatrix;

    /**
     * @brief m_currentPlayer pointer for the current player which holds color and type (human/computer).
     */
    Player *m_currentPlayer;

    /**
     * @brief m_opponentPlayer pointer for the oponnent player which holds color and type (human/computer).
     */
    Player *m_opponentPlayer;


signals:
    /**
     * @brief signalBoardChanged is used to inform the GameEngine about changes on the board in order
     * to evoke a redraw.
     */
    void signalBoardChanged();

    /**
     * @brief signalUpdateInfo informs the GameEngine (InfoList) about a pass with the information about the player
     * who passed.
     */
    void signalUpdateInfo(QString);

public slots:
    /**
     * @brief undoMove get the last board from the board stack.
     * @return true if undo was possible.
     */
    bool undoMove();
};

#endif // BOARD_H
