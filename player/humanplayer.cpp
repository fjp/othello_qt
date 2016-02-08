#include "humanplayer.h"

HumanPlayer::HumanPlayer(Color color) : Player(0, color)
{

}

Player::PlayerType HumanPlayer::getPlayerType()
{
    return PlayerType::HUMAN;
}
