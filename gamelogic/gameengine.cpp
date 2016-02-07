#include "gameengine.h"

GameEngine::GameEngine(QObject *parent, UIGameScene *uiGameScene, QTextEdit *eventList, QTextEdit *infoList) : QObject(parent)
{
    m_uiGameScene = uiGameScene;
    m_eventList = eventList;
    m_infoList = infoList;
}

GameEngine::~GameEngine()
{

}

void GameEngine::startGame(int numberOfHumans)
{
    m_board = new Board();

    m_numberOfHumans = numberOfHumans;
    createPlayers(numberOfHumans);

    connect(m_board, SIGNAL(signalBoardChanged(int,int,Player::Color)), this, SLOT(updateUI(int,int,Player::Color)));

    connect(&loopQTimer, SIGNAL(timeout()), this, SLOT(loop()));

    updateInfoText("Current Player");

    // TODO counter
    loopQTimer.start(1000);
}

void GameEngine::mouseReleased(QPointF point)
{
    int x = point.x() / m_uiGameScene->m_sizeSceneRect * m_uiGameScene->m_numberColumns;
    int y = point.y() / m_uiGameScene->m_sizeSceneRect * m_uiGameScene->m_numberRows;
    qDebug() << "Mouse pointer is at" << point << "x" << x << "y" << y;

    eventHandling(x, y);

}

void GameEngine::createPlayers(int numberOfHumans)
{
    m_humanPlayerB = new HumanPlayer(Player::BLACK);
    m_humanPlayerW = new HumanPlayer(Player::WHITE);
    m_computerPlayerB = new ComputerPlayer(Player::BLACK);
    m_computerPlayerW = new ComputerPlayer(Player::WHITE);

    // TODO set players correctly according to parameter numberOfHumans
    m_currentPlayer = m_humanPlayerB;
    m_opponentPlayer = m_humanPlayerW;
}

void GameEngine::eventHandling(int x, int y)
{
    m_eventList->append(QString("(" + QString::number(x) + "," + QString::number(y) + ")"));

    Player::Color currentPlayer = m_currentPlayer->m_color;
    switch(currentPlayer)
    {
    case Player::BLACK:
        if (m_board->legalMove(x, y, currentPlayer))
        {
            //makeMove(x, y);
            m_board->makeMove(x, y, Player::BLACK);
            updateUI(x, y, Player::BLACK);
            togglePlayer();
        }
        break;

    case Player::WHITE:
        if (m_board->legalMove(x, y, currentPlayer))
        {
            //makeMove(x, y);
            m_board->makeMove(x, y, Player::WHITE);
            updateUI(x, y, Player::WHITE);
            togglePlayer();
        }
        break;

    case Player::NONE:
        qDebug() << "GameEngine::eventHandling" << "Player::NONE?! Debug this";
        break;

    default:
        qDebug() << "GameEngine::eventHandling" << "default case. Debug this";
        break;
    }
}

void GameEngine::updateUI(int x, int y, Player::Color currentPlayer)
{
    switch (currentPlayer) {
    case Player::BLACK:
        m_uiGameScene->setSquareState(x, y, UISquare::BLACK, currentPlayer);
        break;
    case Player::WHITE:
        m_uiGameScene->setSquareState(x, y, UISquare::WHITE, currentPlayer);
        break;
    case Player::NONE:
        m_uiGameScene->setSquareState(x, y, UISquare::BOARD, currentPlayer);
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

void GameEngine::togglePlayer()
{
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
}

//void GameEngine::makeMove(int x, int y)
//{
//    // TODO update number of moves if valid;
//    // TODO append to a tree?!

//    for(int dir = 0; dir < BOARD_SIZE; dir++)
//    {
//        int dx = m_board->m_direction[dir][0];
//        int dy = m_board->m_direction[dir][1];
//        int tx = x + 2*dx;
//        int ty = y + 2*dy;
//        // need to be at least 2 grids away from the edge
//        if (!m_board->onBoard(tx, ty))
//        {
//            continue;
//        }
//        // oppenent piece must be adjacent in the current direction
//        if (m_board->getSquare(x+dx, y+dy)->getOwner() != m_opponentPlayer->m_color)
//        {
//            continue;
//        }
//        // as long as we stay on the board going in the current direction, we search for the surrounding disk
//        while(m_board->onBoard(tx, ty) && m_board->getSquare(tx, ty)->getOwner() == m_opponentPlayer->m_color)
//        {
//            tx += dx;
//            ty += dy;
//        }
//        // if we are still on the board and we found the surrounding disk in the current direction
//        // the move is legal.

//        // go back and flip the pieces if move is legal
//        if(m_board->onBoard(tx, ty) && m_board->getSquare(tx, ty)->getOwner() == m_currentPlayer->m_color)
//        {
//            tx -= dx;
//            ty -= dy;

//            while(m_board->getSquare(tx, ty)->getOwner() == m_opponentPlayer->m_color)
//            {
//                qDebug() << "Flipping" << tx << "," << ty;
//                m_board->getSquare(tx, ty)->setOwner(m_currentPlayer->m_color);
//                if (m_currentPlayer->m_color == Player::BLACK)
//                {
//                    updateUI(tx, ty, UISquare::BLACK, Player::BLACK);
//                }
//                else
//                {
//                    updateUI(tx, ty, UISquare::WHITE, Player::WHITE);
//                }
//                tx -= dx;
//                ty -= dy;
//            }
//            // set color of placed disk to current player
//            m_board->getSquare(x, y)->setOwner(m_currentPlayer->m_color);
//        }
//    }
//}

void GameEngine::counter()
{

}
