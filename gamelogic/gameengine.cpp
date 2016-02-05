#include "gameengine.h"

GameEngine::GameEngine(QObject *parent, UIGameScene *uiGameScene) : QObject(parent)
{
    m_uiGameScene = uiGameScene;
}

GameEngine::~GameEngine()
{

}

void GameEngine::startGame(int numberOfHumans)
{
    m_board = new Board();

    m_numberOfHumans = numberOfHumans;
    createPlayers(numberOfHumans);

    connect(&loopQTimer, SIGNAL(timeout()), this, SLOT(loop()));
    loopQTimer.start(1000);
}

void GameEngine::mouseReleased(QPointF point)
{
    int col = point.x() / m_uiGameScene->m_sizeSceneRect * m_uiGameScene->m_numberColumns;
    int row = point.y() / m_uiGameScene->m_sizeSceneRect * m_uiGameScene->m_numberRows;
    qDebug() << "Mouse pointer is at" << point << "Col" << col << "Row" << row;

    eventHandling(col, row);

}

void GameEngine::createPlayers(int human_players)
{
    m_humanPlayerB = new HumanPlayer(Player::BLACK);
    m_humanPlayerW = new HumanPlayer(Player::WHITE);
    m_computerPlayerB = new ComputerPlayer(Player::BLACK);
    m_computerPlayerW = new ComputerPlayer(Player::WHITE);
    m_currentPlayer = m_humanPlayerB;
}

void GameEngine::eventHandling(int col, int row)
{
    UISquare::State uiState;

    switch(m_currentPlayer->m_color)
    {
    case Player::BLACK:
        uiState = UISquare::BLACK;
        break;

    case Player::WHITE:
        uiState = UISquare::WHITE;
        break;
    }
    nextPlayer();

    updateUI(col, row, uiState);
}

void GameEngine::updateUI(int col, int row, UISquare::State state)
{
    m_uiGameScene->setSquareState(col, row, state);
}

void GameEngine::nextPlayer()
{
    switch(m_currentPlayer->m_color)
    {
    case Player::BLACK:
        m_currentPlayer->m_color = Player::WHITE;
        break;
    case Player::WHITE:
        m_currentPlayer->m_color = Player::BLACK;
        break;
    default:
        m_currentPlayer->m_color = Player::NONE;
    }
    qDebug() << "GameEngine::nextPlayer" << m_currentPlayer->m_color;
}

void GameEngine::counter()
{

}
