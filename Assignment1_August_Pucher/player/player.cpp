#include "player.h"

Player::Player(QObject *parent, State color, Type type) : QObject(parent)
{
    m_color = color;
    m_type = type;
}
