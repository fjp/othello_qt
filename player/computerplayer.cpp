#include "computerplayer.h"

ComputerPlayer::ComputerPlayer(Color color) : Player(0, color)
{

}

Player::PlayerType ComputerPlayer::getPlayerType()
{
    return PlayerType::COMPUTER;
}
