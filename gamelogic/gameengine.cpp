#include "gameengine.h"

GameEngine::GameEngine(QObject *parent, UIGameScene *uiGameScene, QTextEdit *eventList, QTextEdit *infoList) : QObject(parent)
{
    m_uiGameScene = uiGameScene;
    m_eventList = eventList;
    m_infoList = infoList;
}

GameEngine::~GameEngine()
{
    if (m_board != NULL)
        delete m_board;

    if (m_ai != NULL)
        delete m_ai;

}

void GameEngine::startGame(int numberOfHumans, double timeLimit)
{
    m_numberOfHumans = numberOfHumans;

    m_timeLimit = timeLimit;

    // TODO use these variables...
    m_numberOfTotalMoves = 0;
    m_elapsedTime = 0;

    m_gameOver = false;

    m_board = new Board(this, numberOfHumans);

    updateUIGameScene();

    connect(m_board, SIGNAL(signalBoardChanged()), this, SLOT(updateUIGameScene()));

    // show infos like whos turn it is and the time needed so far (TODO is this really needed?!).
    updateInfoText("Current Player");

    // display legal moves for player that starts the game (usually black)
    //showLegalMoves();

    // TODO thinking timer start and stop (toggle, ...)
    //connect(&m_thinkingTime, SIGNAL(timeout()), this, SLOT(loop()));
    m_thinkingTime.start();
    //timer.elapsed() << "milliseconds";

    // create the AI
    m_ai = new AI(m_board);


    if (m_numberOfHumans == 1 && m_board->whosTurnType() == COMPUTER)
    {
        makeComputerMove();
    }

}

void GameEngine::mouseReleased(QPointF point)
{
    if (m_numberOfHumans == 1 && m_board->whosTurnType() == COMPUTER)
    {
        qDebug() << "Computer move! Don't click!";
        return;
    }
    int x = point.x() / m_uiGameScene->m_sizeSceneRect * BOARD_SIZE;
    int y = point.y() / m_uiGameScene->m_sizeSceneRect * BOARD_SIZE;
    // TODO comment all qDebug()s
    //qDebug() << "Mouse pointer is at" << point << "x" << x << "y" << y;
    eventHandling(x, y);
}

void GameEngine::updateUIGameScene()
{
    m_uiGameScene->redrawBoard(m_board);
}

bool GameEngine::gameOver()
{
    // check if current player has options to make a move
    if (m_board->legalMovesAvailable() == true)
    {
        return false;
    }

    // make a pass if there are no legal moves left ...
    m_board->makePass();
    // ... and check if the opponent has legal moves left
    if(m_board->legalMovesAvailable() == true)
    {
        return false;
    }
    qDebug() << "Game Over";

    m_gameOver = true;
    QString gameStats = getGameStats();
    updateInfoText(gameStats);

    return true;
}

QString GameEngine::getGameStats()
{
    QString gameResult;

    m_board->countDisks();
    int numberOfBlackDisks = m_board->m_numberOfBlackDisks;
    int numberOfWhiteDisks = m_board->m_numberOfWhiteDisks;

    // TODO is it needed?
    int numberOfDisks = m_board->m_numberOfDisks;

    // TODO check rules ... count empty squares too???
    if (numberOfBlackDisks > numberOfWhiteDisks)
    {
        gameResult = QString(QString("Black player (") + QString::number(numberOfBlackDisks) + QString(") wins! \n") +
                             QString("White player (") + QString::number(numberOfWhiteDisks) + QString(") loses."));
    }
    else if (numberOfWhiteDisks > numberOfBlackDisks)
    {
        gameResult = QString(QString("White player (") + QString::number(numberOfWhiteDisks) + QString(") wins! \n") +
                             QString("Black player (") + QString::number(numberOfBlackDisks) + QString(") loses."));
    }
    else if (numberOfBlackDisks == numberOfWhiteDisks)
    {
        gameResult = QString(QString("Draw \n") + QString("Both players have ") + QString::number(numberOfBlackDisks));
    }
    return gameResult;
}

void GameEngine::eventHandling(int x, int y)
{
    // first check if the game is over
    if (m_gameOver)
        return;

    // this string will hopefully overwritten by a legal event.
    QString eventString = "Not a legal move!";

    switch(m_board->whosTurn())
    {
    case BLACK:
        if (m_board->legalMove(x, y))
        {
            m_board->makeMove(x, y);
            //revertAllowedUISquares(x, y);
            updateUIGameScene();
            //updateUI(x, y, Player::BLACK);
            eventString = QString(QString::number(m_board->m_numberOfActualMoves) + ". Black played at (" +
                                  QString::number(x) + "," + QString::number(y) +
                                  ") in " + QString::number(getThinkingTime()) + " sec");

            //togglePlayer();
            updateInfoText("Current Player");
            //qDebug() << "GameEngine::nextPlayer" << m_currentPlayer->m_color;
        }
        break;

    case WHITE:
        if (m_board->legalMove(x, y))
        {
            m_board->makeMove(x, y);
            //revertAllowedUISquares(x, y);
            updateUIGameScene();
            //updateUI(x, y, Player::WHITE);
            eventString = QString(QString::number(m_board->m_numberOfActualMoves) + ". White played at (" +
                                  QString::number(x) + "," + QString::number(y) +
                                  ") in " + QString::number(getThinkingTime()) + " sec");

            //togglePlayer();
            updateInfoText("Current Player");
            //qDebug() << "GameEngine::nextPlayer" << m_currentPlayer->m_color;
        }
        break;

    case NONE:
        qDebug() << "GameEngine::eventHandling" << "Player::NONE?! Debug this";
        break;

    default:
        qDebug() << "GameEngine::eventHandling" << "default case. Debug this";
        break;
    }


    //bool movesAvailable = m_board->legalMovesAvailable();
    //if (!movesAvailable)
    //{
        //gameOver();
    //}

    updateEventText(eventString);

    // restart the stopwatch
    m_elapsedTime = 0;
    m_thinkingTime.start();

    // make a new computer move if it is his turn.
    if (!gameOver() && m_numberOfHumans == 1 && m_board->whosTurnType() == COMPUTER)
    {
        makeComputerMove();
        updateInfoText("Current Player");
    }
    updateEventText(eventString);
}

void GameEngine::makeComputerMove()
{
    //m_ai->makeMove();

    m_ai->m_startingDepth = m_board->m_numberOfActualMoves;

    QPair<int,int> savedMove = QPair<int,int>(-10,-10);
    int evaluation = m_ai->max(m_timeLimit, -INFTY, +INFTY);
    savedMove = m_ai->savedMove();
    qDebug() << "Evaluation" << evaluation;
    if (savedMove.first == -10)
    {
        qDebug() << "AI found no more moves";
        // check if game over when AI cannot find moves.
        gameOver();
    }

    else
    {
        // execute saved moves
        qDebug() << "executing saved moves";
        if (m_board->legalMove(savedMove.first, savedMove.second))
        {
            m_board->makeMove(savedMove.first, savedMove.second);
        }
        else
        {
            qDebug() << "COMPUTER MADE A WRONG MOVE!";
        }
    }

    updateInfoText("Current Player");

    bool movesAvailable = m_board->legalMovesAvailable();
    if (!movesAvailable)
    {
        gameOver();
    }

    // restart the stopwatch
    m_elapsedTime = 0;
    m_thinkingTime.start();
}

void GameEngine::updateUISquare(int x, int y, State currentPlayer)
{
    // update chosen square with player color
    switch (currentPlayer) {
    case BLACK:
        m_uiGameScene->setSquareState(x, y, BLACK);
        break;
    case WHITE:
        m_uiGameScene->setSquareState(x, y, WHITE);
        break;
    case NONE:
        m_uiGameScene->setSquareState(x, y, BOARD);
        break;
    default:
        m_uiGameScene->setSquareState(x, y, NONE);
        break;
    }
}

void GameEngine::updateInfoText(QString string)
{
    //m_infoList->setText(string);
    switch (m_board->whosTurn())
    {
    case BLACK:
        m_infoList->setText(QString("Black to move"));
        break;
    case WHITE:
        m_infoList->setText(QString("White to move"));
        break;
    case NONE:
        m_infoList->append(QString("NONE to move?! Debug this"));
        break;
    default:
        m_infoList->append(QString("default case ... Debug this"));
        break;
    }
}

void GameEngine::updateEventText(QString string)
{
    //qDebug() << "NumberOfActualMoves" << m_board->m_numberOfActualMoves;
    //qDebug() << "NumberOfTotalMoves" << m_board->m_numberOfTotalMoves;
    m_eventList->append(string);
}

double GameEngine::getThinkingTime()
{
    m_elapsedTime = m_thinkingTime.elapsed();
    m_elapsedTime = m_elapsedTime/1000.0;
    return m_elapsedTime;
}

void GameEngine::togglePlayer()
{

    // TODO comment or delet; just for debugging
    m_board->countDisks();

    Player *dummyPlayer;
    dummyPlayer = m_currentPlayer;
    m_currentPlayer = m_opponentPlayer;
    m_opponentPlayer = dummyPlayer;
}
