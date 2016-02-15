#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSize>
#include <QDebug>

#include "gamelogic/gameengine.h"
#include "board/board.h"
#include "ui/uigamescene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow constrains the window elements by fixing their size.
     * Improves rendering of the board UIGameScene inside the GraphicsView.
     * Sets a validator to the user input for the search depth to allow only integer numbers (0 to 10).
     * Sets the connects for the signal and slot mechanism for the newGame push button.
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    /**
     * @brief startNewGame creates a new UIGameScene class that gets passed to the newly created
     * GameEngine class. Also the gui textEdits (ui->textEditEvents ui->textEditInfo) to display
     * user informations are passed to GameEngine. Further more, the undo push button is
     * registered with the GameEngine and the user mouse events are forwarded too.
     * Finally the number of humans from the ui->comboBoxNumberOfHumans is passed to the GameEngine.
     */
    void startNewGame();


private:
    /**
     * @brief ui pointer to the gui elements.
     */
    Ui::MainWindow *ui;

    /**
     * @brief m_gameEngine pointer to teh GameEngine class which controls the flow of the game.
     */
    GameEngine *m_gameEngine;

    /**
     * @brief m_uiGameScene pointer to the UIGameScene class which displays the board states using
     * the UISquare class with the current board state from the Board class.
     * The updating is done by the GameEngine.
     */
    UIGameScene *m_uiGameScene;
};

#endif // MAINWINDOW_H
