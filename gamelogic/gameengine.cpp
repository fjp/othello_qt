#include "gameengine.h"

GameEngine::GameEngine(QObject *parent, UIGameScene *uiGameScene, QTextEdit *eventList, QTextEdit *infoList) : QObject(parent)
{
    m_uiGameScene = uiGameScene;
    m_eventList = eventList;
    m_infoList = infoList;

    m_legalMoves = new QVector<Square* >;
}

GameEngine::~GameEngine()
{

}

void GameEngine::startGame(int numberOfHumans)
{
    m_numberOfHumans = numberOfHumans;
    createPlayers(numberOfHumans);

    // TODO use these variables...
    m_numberOfActualMoves = 0;
    m_numberOfTotalMoves = 0;
    m_elapsedTime = 0;

    m_board = new Board(m_currentPlayer);

    connect(m_board, SIGNAL(signalBoardChanged(int,int,Player::Color)), this, SLOT(updateUI(int,int,Player::Color)));

    // show infos like whos turn it is and the time needed so far (TODO is this really needed?!).
    updateInfoText("Current Player");

    // display legal moves for player that starts the game (usually black)
    showLegalMoves();

    // TODO thinking timer start and stop (toggle, ...)
    //connect(&m_thinkingTime, SIGNAL(timeout()), this, SLOT(loop()));
    m_thinkingTime.start();
    //timer.elapsed() << "milliseconds";

}

void GameEngine::mouseReleased(QPointF point)
{
    int x = point.x() / m_uiGameScene->m_sizeSceneRect * m_uiGameScene->m_numberColumns;
    int y = point.y() / m_uiGameScene->m_sizeSceneRect * m_uiGameScene->m_numberRows;
    // TODO comment all qDebug()s
    //qDebug() << "Mouse pointer is at" << point << "x" << x << "y" << y;
    eventHandling(x, y);
}

void GameEngine::createPlayers(int numberOfHumans)
{
    if (numberOfHumans == 2)
    {
        m_humanPlayerB = new HumanPlayer(Player::BLACK);
        m_humanPlayerW = new HumanPlayer(Player::WHITE);
    }
    else if (numberOfHumans == 1)
    {
        // TODO let palyer choose color
        m_computerPlayerB = new ComputerPlayer(Player::BLACK);
        m_humanPlayerW = new HumanPlayer(Player::WHITE);

        //m_computerPlayerW = new ComputerPlayer(Player::WHITE);
    }

    // TODO set players correctly according to parameter numberOfHumans
    m_currentPlayer = m_humanPlayerB;
    m_opponentPlayer = m_humanPlayerW;
}

bool GameEngine::gameOver()
{
    // check if current player has options to make a move
    if (m_board->getLegalMoves(m_legalMoves) == true)
    {
        return false;
    }

    // make a pass if there are no legal moves left ...
    makePass();
    // ... and check if the opponent has legal moves left
    if(m_board->getLegalMoves(m_legalMoves) == true) {
        return false;
    }

    qDebug() << "Game Over";
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
        gameResult = QString(QString("White player (") + QString::number(numberOfBlackDisks) + QString(") wins! \n") +
                             QString("Black player (") + QString::number(numberOfWhiteDisks) + QString(") loses."));
    }
    else if (numberOfBlackDisks == numberOfWhiteDisks)
    {
        gameResult = QString(QString("Draw \n") + QString("Both players have ") + QString::number(numberOfBlackDisks));
    }

    return gameResult;
}

void GameEngine::makePass()
{
    if (m_currentPlayer->m_color == Player::BLACK)
    {
        updateInfoText("Black passed, it's White's turn");
    }
    else if (m_currentPlayer->m_color == Player::WHITE)
    {
        updateInfoText("White passed, it's Black's turn");
    }
    m_numberOfTotalMoves++;
    togglePlayer();

}

void GameEngine::eventHandling(int x, int y)
{
    // first check if the game is over
    if (gameOver())
    {
        QString gameStats = getGameStats();
        updateInfoText(gameStats);
    }

    // this string will hopefully overwritten by a legal event.
    QString eventString = "Something went wrong in eventHandling";

    Player::Color currentPlayer = m_currentPlayer->m_color;
    switch(currentPlayer)
    {
    case Player::BLACK:
        if (m_board->legalMove(x, y))
        {
            m_board->makeMove(x, y);
            revertAllowedUISquares(x, y);
            updateUI(x, y, Player::BLACK);
            m_numberOfActualMoves++;
            m_numberOfTotalMoves++;
            eventString = QString(QString::number(m_numberOfActualMoves) + ". Black played at (" +
                                  QString::number(x) + "," + QString::number(y) +
                                  ") in " + QString::number(getThinkingTime()) + " sec");

            togglePlayer();
        }
        // check if game is over if no legal move possible
        else
        {
            gameOver();
        }
        break;

    case Player::WHITE:
        if (m_board->legalMove(x, y))
        {
            m_board->makeMove(x, y);
            revertAllowedUISquares(x, y);
            updateUI(x, y, Player::WHITE);
            m_numberOfActualMoves++;
            m_numberOfTotalMoves++;
            eventString = QString(QString::number(m_numberOfActualMoves) + ". White played at (" +
                                  QString::number(x) + "," + QString::number(y) +
                                  ") in " + QString::number(getThinkingTime()) + " sec");

            togglePlayer();
        }
        // check if game is over if no legal move possible
        else
        {
            gameOver();
        }
        break;

    case Player::NONE:
        qDebug() << "GameEngine::eventHandling" << "Player::NONE?! Debug this";
        break;

    default:
        qDebug() << "GameEngine::eventHandling" << "default case. Debug this";
        break;
    }

    updateEventText(eventString);

    // restart the stopwatch
    m_elapsedTime = 0;
    m_thinkingTime.start();
}

void GameEngine::updateUI(int x, int y, Player::Color currentPlayer)
{
    // update chosen square with player color
    switch (currentPlayer) {
    case Player::BLACK:
        m_uiGameScene->setSquareState(x, y, UISquare::BLACK);
        break;
    case Player::WHITE:
        m_uiGameScene->setSquareState(x, y, UISquare::WHITE);
        break;
    case Player::NONE:
        m_uiGameScene->setSquareState(x, y, UISquare::BOARD);
        break;
    default:
        break;
    }
}

void GameEngine::updateInfoText(QString string)
{
    m_infoList->setText(string);
    switch (m_currentPlayer->m_color)
    {
    case Player::BLACK:
        m_infoList->append(QString("Black to move"));
        break;
    case Player::WHITE:
        m_infoList->append(QString("White to move"));
        break;
    case Player::NONE:
        m_infoList->append(QString("NONE to move?! Debug this"));
        break;
    default:
        m_infoList->append(QString("default case ... Debug this"));
        break;
    }
}

void GameEngine::updateEventText(QString string)
{
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

    switch(m_currentPlayer->m_color)
    {
    case Player::BLACK:
        m_currentPlayer->m_color = Player::WHITE;
        m_opponentPlayer->m_color = Player::BLACK;
        break;
    case Player::WHITE:
        m_currentPlayer->m_color = Player::BLACK;
        m_opponentPlayer->m_color = Player::WHITE;
        break;
    default:
        m_currentPlayer->m_color = Player::NONE;
        m_opponentPlayer->m_color = Player::NONE;
    }
    updateInfoText("Current Player");
    qDebug() << "GameEngine::nextPlayer" << m_currentPlayer->m_color;

    showLegalMoves();
}

void GameEngine::showLegalMoves()
{
    // clear list first (forget previous legal moves)
    m_legalMoves->clear();

    // check if there are legal moves available before actually trying to redraw some.
    bool legalMovesAvailable = m_board->getLegalMoves(m_legalMoves);
    if (legalMovesAvailable == true)
    {
        foreach (Square *square, *m_legalMoves) {
            m_uiGameScene->setSquareState(square->m_x, square->m_y, UISquare::ALLOWED);
        }
    }
}

void GameEngine::revertAllowedUISquares(int x, int y)
{
    // revert allowed squares to Board state that were NOT picked by current player
    Square *movedSquare = m_board->getSquare(x, y);
    m_legalMoves->removeOne(movedSquare);
    foreach (Square *square, *m_legalMoves)
    {
        updateUI(square->m_x, square->m_y, Player::NONE);
    }
}

void GameEngine::counter()
{

}
