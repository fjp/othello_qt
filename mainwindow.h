#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSize>

#include "board/board.h"
#include "ui/uigamescene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QSize m_boardSize;
    int m_iBoardSize;

    UIGameScene *m_uiGameScene;
    Board *m_board;
};

#endif // MAINWINDOW_H
