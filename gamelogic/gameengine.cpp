#include "gameengine.h"


QQueue<GameEvent*> GameEngine::eventQueue;

GameEngine::GameEngine(QObject *parent, UIGameScene *uiGameScene) : QObject(parent)
{

}

GameEngine::~GameEngine()
{

}

void GameEngine::startGame(int numberOfHumans)
{
    m_board = new Board();

    m_numberOfHumans = numberOfHumans;
    //createPlayers(numberOfHumans);

    connect(&loopQTimer, SIGNAL(timeout()), this, SLOT(loop()));
    loopQTimer.start(1000);
}

void GameEngine::mouseReleased(QPointF point)
{
    qDebug() << "Mouse pointer is at" << point;
}

void GameEngine::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QMessageBox *msgBox = new QMessageBox();
        msgBox->setWindowTitle("Hello");
        msgBox->setText("You Clicked Left Mouse Button");
        msgBox->show();
    }
}

void GameEngine::eventHandling()
{
    GameEvent *event;
    while(!GameEngine::eventQueue.isEmpty())
    {
        event = GameEngine::eventQueue.dequeue();

        switch(event->m_gameEvent)
        {
        case GameEvent::A1:

            break;
        case GameEvent::A2:

            break;
        }
    }
}

void GameEngine::updateUI(GameEvent *event, UISquare::State state)
{
    int positionX = event->m_square->m_positionX;
    int positionY = event->m_square->m_positionY;
    m_uiGameScene->setSquareState(positionX, positionY, state);
}

void GameEngine::counter()
{

}
