#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow), m_iBoardSize(8)
{
    ui->setupUi(this);

    //qApp->installEventFilter(this);

    ui->graphicsViewBoard->setScene(m_uiGameScene);


    connect(ui->pushButton, SIGNAL(released()), this, SLOT(startNewGame()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startNewGame()
{
    qDebug() << "Starting New Game!";
    //qDebug() << m_iMapSize;
    m_uiGameScene = new UIGameScene(this, m_iBoardSize, m_iBoardSize);

    // create new GameLogic here to avoid swalloing KeyBoard Input
    m_gameEngine = new GameEngine(this, m_uiGameScene);
    connect(m_uiGameScene, SIGNAL(newMouseEvent(QPointF)), m_gameEngine, SLOT(mouseReleased(QPointF)));
    ui->graphicsViewBoard->setScene(m_uiGameScene);
    m_gameEngine->startGame(1);
}

//bool MainWindow::eventFilter(QObject *parent, QEvent *event)
//{
//    if (event->type() == QEvent::MouseButtonRelease)
//    {
//        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
//        // forward to graphicsView (via default MainWindow behaviour)
//        qDebug() << "Mouse";
//        QMainWindow::mouseReleaseEvent(mouseEvent);
//    }
//    return false;
//}
