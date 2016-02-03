#include "uisquare.h"

UISquare::UISquare()
{

}

UISquare::UISquare(const double height, const double width)
{
    m_state = BOARD;
    setSize(height, width);
    initSquare();
}

UISquare::UISquare(const UISquare &square)
{
    m_state = square.getState();
    setSize(50,50);
    initSquare();
}

UISquare::~UISquare()
{

}

void UISquare::initSquare()
{
    m_squareState = new QRectF(0, 0,m_width, m_height);
    m_boardSquare = new QRectF(0, 0,m_width, m_height);
    m_allowedSquare = new QRectF(0, 0,m_width, m_height);
    m_suggestedSquare = new QRectF(0, 0,m_width, m_height);
    m_blackSquare = new QRectF(0, 0,m_width, m_height);
    m_whiteSquare = new QRectF(0, 0,m_width, m_height);
    m_stateBuf = BOARD;
    setPosition(0, 0);
}

QRectF UISquare::boundingRect() const
{
    return QRectF(0, 0, m_width, m_height);
}

void UISquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QPen pen;
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    switch(m_state)
    {
        case ALLOWED:
            pen.setColor(Qt::gray);
            brush.setColor(Qt::yellow);
            painter->setPen(pen);
            painter->setBrush(brush);
            painter->drawRect(rect);
            break;
        case BLACK:
            pen.setColor(Qt::gray);
            brush.setColor(Qt::black);
            painter->setPen(pen);
            painter->setBrush(brush);
            painter->drawRect(rect);
            break;
        case WHITE:
            pen.setColor(Qt::gray);
            brush.setColor(Qt::white);
            painter->setPen(pen);
            painter->setBrush(brush);
            painter->drawRect(rect);
            break;
        case BOARD:
            pen.setColor(Qt::gray);
            brush.setColor(Qt::green);
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
            break;
    }

}

void UISquare::setState(const UISquare::State state)
{
    m_state = state;
    update();
}

UISquare::State UISquare::getState() const
{
    return m_state;
}

void UISquare::setPosition(const double positionX, const double positionY)
{
    m_positionX = positionX;
    m_positionY = positionY;
    setPos(mapToParent(m_positionX,m_positionY));
}

void UISquare::setSize(const double height, const double width)
{
    m_width = width;
    m_height = height;
    update();
}
