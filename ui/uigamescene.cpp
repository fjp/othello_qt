#include "uigamescene.h"

UIGameScene::UIGameScene(QObject * parent) : QGraphicsScene(parent)
{
    m_sizeSceneRect = 500;
    m_squareWidth = 50;
    m_squareHeight = 50;
    m_numberSquareX = 8;
    m_numberSquareY = 8;
    initUIGameScene();
}

UIGameScene::UIGameScene(QObject *parent, int numberSquareX, int numberSquareY) : QGraphicsScene(parent),
    m_board(numberSquareX, QVector<UISquare>(numberSquareY)), m_backgroundBlocks((numberSquareX+2)*2 + numberSquareY*2)
{
    m_sizeSceneRect = 500;
    m_squareWidth = m_sizeSceneRect / static_cast<double>(numberSquareX);
    m_squareHeight = m_sizeSceneRect / static_cast<double>(numberSquareY);
    m_numberSquareX = numberSquareX;
    m_numberSquareY = numberSquareY;
    initUIGameScene();
}

UIGameScene::~UIGameScene()
{

}

void UIGameScene::setSquareState(int x, int y, UISquare::State state)
{
    m_board[x][y].setState(state);
}

void UIGameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF point = mouseEvent->scenePos();
    qDebug() << Q_FUNC_INFO << point;



    // Todo: move to game logic + extra funciton that converts from point to square
    int x = point.x() / m_sizeSceneRect * m_numberSquareX;
    int y = point.y() / m_sizeSceneRect * m_numberSquareY;
    setSquareState(x,y,UISquare::BLACK);
    //drawBoard();

    // ------------------

    emit newMouseEvent(point);
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void UIGameScene::initUIGameScene()
{
    setBackgroundBrush(Qt::gray);
    setSceneRect(0, 0, m_squareWidth*m_numberSquareX, m_squareHeight*m_numberSquareY);
    drawBoard();
}

void UIGameScene::drawBoard()
{
    for (int x = 0; x < m_numberSquareX; x++) {
        for (int y=0; y < m_numberSquareY; y++) {
            addItem(&m_board[x][y]);
            m_board[x][y].setPosition(x*m_squareWidth, y*m_squareHeight);
            m_board[x][y].setSize(m_squareHeight, m_squareWidth);
        }
    }
}
