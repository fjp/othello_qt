#include "uisquare.h"

UISquare::UISquare()
{
    initSquare();
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
    m_margin = 5;
    m_ellipse = new QRectF(m_margin, m_margin, m_diskWidth, m_diskHeight);
    setPosition(0, 0);
    setState(BOARD);
}

void UISquare::setSquareSize()
{

}

QRectF UISquare::boundingRect() const
{
    return QRectF(0, 0, m_squareWidth, m_squareHeight);
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
            pen.setColor(Qt::black);
            brush.setColor(Qt::yellow);
            painter->setPen(pen);
            painter->setBrush(brush);
            painter->drawRect(rect);
            break;
        case BLACK:
            pen.setColor(Qt::black);
            brush.setColor(Qt::darkGreen);
            painter->setPen(pen);
            painter->setBrush(brush);
            painter->drawRect(rect);

            // draw black disk
            brush.setColor(Qt::black);
            painter->setBrush(brush);
            qDebug() << "BLACK" << m_margin;
            painter->drawEllipse(m_margin, m_margin, m_diskWidth, m_diskHeight);
            break;

        case WHITE:
            pen.setColor(Qt::black);
            brush.setColor(Qt::darkGreen);
            painter->setPen(pen);
            painter->setBrush(brush);
            painter->drawRect(rect);

            // draw white disk
            brush.setColor(Qt::white);
            painter->setBrush(brush);

            painter->drawEllipse(m_margin, m_margin, m_diskWidth, m_diskHeight);
            break;

        case BOARD:
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

void UISquare::setPosition(const double boardPositionY, const double boardPositionX)
{
    m_boardPositionX = boardPositionX;
    m_boardPositionY = boardPositionY;
    setPos(mapToParent(m_boardPositionX, m_boardPositionY));
}

void UISquare::setSize(const double height, const double width)
{
    m_squareWidth = width;
    m_squareHeight = height;
    m_diskWidth = width - 2*m_margin;
    m_diskHeight = width - 2*m_margin;
    update();
}
