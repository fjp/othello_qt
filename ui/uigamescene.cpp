#include "uigamescene.h"

UIGameScene::UIGameScene(QObject *parent) : QGraphicsScene(parent),
    m_board(BOARD_SIZE, QVector<UISquare *>(BOARD_SIZE))
{
    m_sizeSceneRect = 500;
    m_squareSize = m_sizeSceneRect / static_cast<double>(BOARD_SIZE);
    initUIGameScene();
}

UIGameScene::~UIGameScene()
{

}

void UIGameScene::setSquareState(int x, int y, Square::State state)
{
    //qDebug() << "UIGameScene::setSquareState:" << "x,y" << x << "," << y << "State"<< state;
    m_board[x][y]->setState(state);
}

void UIGameScene::redrawBoard(Board *board)
{
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            m_board[x][y]->setState(board->getSquareState(x, y));
            m_board[x][y]->setPosition(x*m_squareSize, y*m_squareSize);
            m_board[x][y]->setSize(m_squareSize);
        }
    }
}

void UIGameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF point = mouseEvent->scenePos();
    //qDebug() << "UIGameScene::mouseReleaseEvent" << "Mouse Pointer is at"<< point;

    emit newMouseEvent(point);
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void UIGameScene::initUIGameScene()
{
    setBackgroundBrush(Qt::gray);
    setSceneRect(0, 0, m_squareSize*BOARD_SIZE, m_squareSize*BOARD_SIZE);
    drawBoard();
}

void UIGameScene::drawBoard()
{
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            m_board[x][y] = new UISquare(x, y, Square::BOARD, Player::NONE);
            this->addItem(m_board[x][y]);
            m_board[x][y]->setPosition(x*m_squareSize, y*m_squareSize);
            m_board[x][y]->setSize(m_squareSize);
        }
    }
    m_board[3][3]->setState(Square::WHITE);
    m_board[3][4]->setState(Square::BLACK);
    m_board[4][3]->setState(Square::BLACK);
    m_board[4][4]->setState(Square::WHITE);
}
