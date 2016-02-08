#include "player.h"

Player::Player(QObject *parent, Color color) : QObject(parent)
{
    m_color = color;
}

void Player::setPlayerColor(Player::Color color)
{
    m_color = color;
}

Player::PlayerType Player::getPlayerType()
{
     return PlayerType::UNKNOWN;
}
