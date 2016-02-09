#include "uisquare.h"

UISquare::UISquare(int x, int y, Square::State state, Player::Color currentOwner)
{
    m_x = x;
    m_y = y;
    m_state = state;
    m_currentOwner = currentOwner;
    initSquare();
}

UISquare::UISquare(const UISquare &square)
{
    m_state = square.getState();
    setSize(50);
    initSquare();
}

UISquare::~UISquare()
{

}

void UISquare::initSquare()
{
    m_margin = 5;
    m_ellipse = new QRectF(m_margin, m_margin, m_diskSize, m_diskSize);
    setPosition(0, 0);
    setState(Square::BOARD);
}

void UISquare::setSquareSize()
{

}

QRectF UISquare::boundingRect() const
{
    return QRectF(0, 0, m_squareSize, m_squareSize);
}

void UISquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QPen pen;
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    switch(m_state)
    {
        case Square::ALLOWED:
            pen.setColor(Qt::black);
            brush.setColor(Qt::darkGreen);
            painter->setPen(pen);
            painter->setBrush(brush);
            painter->drawRect(rect);

            // draw gray disk
            pen.setColor(Qt::gray);
            brush.setColor(Qt::gray);
            painter->setPen(pen);
            painter->setBrush(brush);
            painter->drawEllipse(m_margin*4, m_margin*4, m_diskSize/2, m_diskSize/2);
            break;
        case Square::BLACK:
            pen.setColor(Qt::black);
            brush.setColor(Qt::darkGreen);
            painter->setPen(pen);
            painter->setBrush(brush);
            painter->drawRect(rect);

            // draw black disk
            brush.setColor(Qt::black);
            painter->setBrush(brush);
            painter->drawEllipse(m_margin, m_margin, m_diskSize, m_diskSize);
            break;

        case Square::WHITE:
            pen.setColor(Qt::black);
            brush.setColor(Qt::darkGreen);
            painter->setPen(pen);
            painter->setBrush(brush);
            painter->drawRect(rect);

            // draw white disk
            pen.setColor(Qt::white);
            brush.setColor(Qt::white);
            painter->setBrush(brush);
            painter->setPen(pen);
            painter->drawEllipse(m_margin, m_margin, m_diskSize, m_diskSize);
            break;

        case Square::BOARD:
            pen.setColor(Qt::black);
            brush.setColor(Qt::darkGreen);
            painter->setPen(pen);
            painter->setBrush(brush);
            painter->drawRect(rect);
            break;
        default:
            pen.setColor(Qt::gray);
            brush.setColor(Qt::green);
            painter->setPen(pen);
            painter->setBrush(brush);
            painter->drawRect(rect);
            qDebug() << "UISquare::paint" << "default case, something went wrong";
            break;
    }


    // TODO comment; used for debugging to see the square positions.
    QString owner;
    switch (m_currentOwner)
    {
    case Player::BLACK:
        owner = QString("BLACK");
        break;

    case Player::WHITE:
        owner = QString("WHITE");
        break;

    case Player::NONE:
        owner = QString("NONE");
        break;

    default:
        owner = QString("default");
        break;
    }

    QString squarePosition = QString("(%1,%2) %3").arg(QString::number(m_x), QString::number(m_y), owner);
    pen.setColor(Qt::white);
    painter->setPen(pen);
    painter->drawText(5, 10, squarePosition);

}

void UISquare::setState(const Square::State state)
{
    m_state = state;

    switch (m_state) {
    case Square::ALLOWED:
        m_currentOwner = Player::NONE;
        break;
    case Square::BLACK:
        m_currentOwner = Player::BLACK;
        break;
    case Square::WHITE:
        m_currentOwner = Player::WHITE;
        break;
    case Square::NONE:
        m_currentOwner = Player::NONE;
        break;
    default:
        break;
    }

    // commit redraw of changed square -> this updates the GraphicsScene UIGameScene.
    update();
}

Square::State UISquare::getState() const
{
    return m_state;
}

void UISquare::setPosition(const double boardPositionX, const double boardPositionY)
{
    m_boardPositionX = boardPositionX;
    m_boardPositionY = boardPositionY;
    setPos(mapToParent(m_boardPositionX, m_boardPositionY));
}

void UISquare::setSize(const double size)
{
    m_squareSize = size;
    m_diskSize = size - 2*m_margin;
    update();
}
