#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow), m_iBoardSize(8) // TODO where is BoardSize actually used?
{
    ui->setupUi(this);

    this->setFixedSize(this->geometry().width(),this->geometry().height());

    // Todo set fixed size of graphicsView and of MainWindow itself.
    // I don't know the size - look at ui option.
    //ui->graphicsViewBoard->setFixedSize(m_iWidgetSize - m_iWidgetBorder, m_iWidgetSize - m_iWidgetBorder);
    ui->graphicsViewBoard->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsViewBoard->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsViewBoard->setRenderHint(QPainter::Antialiasing,true);
    ui->graphicsViewBoard->setRenderHint(QPainter::SmoothPixmapTransform, true);

    // set multi row text edit
    ui->textEditEvents->setWordWrapMode(QTextOption::WordWrap);
    ui->textEditInfo->setWordWrapMode(QTextOption::WordWrap);

    connect(ui->pushButtonNewGame, SIGNAL(released()), this, SLOT(startNewGame()));
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
    ui->graphicsViewBoard->setScene(m_uiGameScene);

    // create new GameLogic here to avoid swalloing KeyBoard Input
    m_gameEngine = new GameEngine(this, m_uiGameScene, ui->textEditEvents, ui->textEditInfo);
    connect(m_uiGameScene, SIGNAL(newMouseEvent(QPointF)), m_gameEngine, SLOT(mouseReleased(QPointF)));
    //ui->graphicsViewBoard->setScene(m_uiGameScene);

    // TODO implement number of human palyers correctly; let player choose number and color.
    m_gameEngine->startGame(2);
}
