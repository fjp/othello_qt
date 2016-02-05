#include "uigamescene.h"

UIGameScene::UIGameScene(QObject * parent) : QGraphicsScene(parent)
{
    m_sizeSceneRect = 500;
    m_squareWidth = 50;
    m_squareHeight = 50;

    m_numberColumns = 8;
    m_numberRows = 8;
    initUIGameScene();
}

UIGameScene::UIGameScene(QObject *parent, int numberColumns, int numberRows) : QGraphicsScene(parent),
    m_board(numberRows, QVector<UISquare *>(numberColumns))
{
    m_sizeSceneRect = 500;
    m_squareWidth = m_sizeSceneRect / static_cast<double>(numberColumns);
    m_squareHeight = m_sizeSceneRect / static_cast<double>(numberRows);
    m_numberColumns = numberColumns;
    m_numberRows = numberRows;
    initUIGameScene();
}

UIGameScene::~UIGameScene()
{

}

void UIGameScene::setSquareState(int column, int row, UISquare::State state)
{
    qDebug() << "UIGameScene::setSquareState:" << "col,row" << column << "," << row << "State"<< state;
    m_board[column][row]->setState(state);
}

void UIGameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF point = mouseEvent->scenePos();
    qDebug() << "UIGameScene::mouseReleaseEvent" << "Mouse Pointer is at"<< point;

    emit newMouseEvent(point);
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void UIGameScene::initUIGameScene()
{
    setBackgroundBrush(Qt::gray);
    setSceneRect(0, 0, m_squareWidth*m_numberColumns, m_squareHeight*m_numberRows);
    drawBoard();
}

void UIGameScene::drawBoard()
{
    for (int row = 0; row < m_numberRows; row++) {
        for (int col = 0; col < m_numberColumns; col++) {
            m_board[col][row] = new UISquare();
            m_board[col][row]->setState(UISquare::BOARD);
            this->addItem(m_board[col][row]);
            m_board[col][row]->setPosition(row*m_squareHeight, col*m_squareWidth);
            m_board[col][row]->setSize(m_squareHeight, m_squareWidth);
        }
    }
    m_board[3][3]->setState(UISquare::BLACK);
    m_board[4][3]->setState(UISquare::WHITE);
    m_board[3][4]->setState(UISquare::WHITE);
    m_board[4][4]->setState(UISquare::BLACK);
}
