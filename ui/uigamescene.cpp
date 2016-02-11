#include "uigamescene.h"

UIGameScene::UIGameScene(QObject *parent) : QGraphicsScene(parent),
    m_board(BOARD_SIZE, QVector<UISquare *>(BOARD_SIZE)), m_edgeText(QVector< QGraphicsSimpleTextItem *>(16))
{
    m_sizeSceneRect = 450;
    m_squareSize = m_sizeSceneRect / static_cast<double>(BOARD_SIZE);
    initUIGameScene();
}

UIGameScene::~UIGameScene()
{
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            if (m_board.at(x).at(y) != NULL)
                delete m_board[x][y];
        }
    }
}

void UIGameScene::setSquareState(int x, int y, State state)
{
    //qDebug() << "UIGameScene::setSquareState:" << "x,y" << x << "," << y << "State"<< state;
    m_board[x][y]->setUISquareState(state);
}

void UIGameScene::redrawBoard(Board *board)
{
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            m_board[x][y]->setUISquareState(board->getState(x, y));
        }
    }

}

void UIGameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    // get the cursor position inside UIGameScene.
    QPointF point = mouseEvent->scenePos();

    // provide the GameEngine with the click event
    emit newMouseEvent(point);
}

void UIGameScene::initUIGameScene()
{

    setSceneRect(0, 0, m_squareSize*BOARD_SIZE, m_squareSize*BOARD_SIZE);
    setBackgroundBrush(QColor(153, 102, 0));
    drawBoard();
}

void UIGameScene::drawBoard()
{
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            m_board[x][y] = new UISquare(x, y, BOARD);
            this->addItem(m_board[x][y]);
            m_board[x][y]->setPosition(x*m_squareSize, y*m_squareSize);
            m_board[x][y]->setSize(m_squareSize);
        }
    }
    m_board[3][3]->setUISquareState(WHITE);
    m_board[3][4]->setUISquareState(BLACK);
    m_board[4][3]->setUISquareState(BLACK);
    m_board[4][4]->setUISquareState(WHITE);


    QString A = QString("A");
    QString B = QString("B");
    QString C = QString("C");
    QString D = QString("D");
    QString E = QString("E");
    QString F = QString("F");
    QString G = QString("G");
    QString H = QString("H");
    QString _1 = QString("1");
    QString _2 = QString("2");
    QString _3 = QString("3");
    QString _4 = QString("4");
    QString _5 = QString("5");
    QString _6 = QString("6");
    QString _7 = QString("7");
    QString _8 = QString("8");

    QString m_text[16] = {A, B, C, D, E, F, G, H, _1, _2, _3, _4, _5, _6, _7, _8};

    QPen color(Qt::red);

    for (int i = 0; i < 8; i++)
    {
        m_edgeText[i] = new QGraphicsSimpleTextItem(m_text[i]);
        m_edgeText[i]->setPen(color);
        m_edgeText[i]->setPos(i*m_squareSize + m_squareSize/2, 2);
        this->addItem(m_edgeText[i]);

        m_edgeText[i+8] = new QGraphicsSimpleTextItem(m_text[i+8]);
        m_edgeText[i+8]->setPen(color);
        m_edgeText[i+8]->setPos(2, i*m_squareSize + m_squareSize/2);
        this->addItem(m_edgeText[i+8]);
    }
}
