#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow), m_iBoardSize(8)
{
    ui->setupUi(this);

    ui->graphicsViewBoard->size();

    m_uiGameScene = new UIGameScene(this, m_iBoardSize, m_iBoardSize);

    ui->graphicsViewBoard->setScene(m_uiGameScene);
}

MainWindow::~MainWindow()
{
    delete ui;
}
