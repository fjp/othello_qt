#include "player.h"

Player::Player(QObject *parent, Color color, Type type) : QObject(parent)
{
    m_color = color;
    m_type = UNKNOWN;
}
