#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "define.h"

/**
 * @brief The Player class defines the current and the opponent player.
 * Each player has its own color, BLACK or WHITE, and is of type HUMAN or COMPUTER.
 */
class Player : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief m_type stores the player type. Either HUMAN or COMPUTER.
     */
    Type m_type;

    /**
     * @brief m_color stores the color of the player. Either Black or White.
     */
    State m_color;

    /**
     * @brief Player initializes the instance with its color and type.
     * @param parent
     * @param color
     * @param type
     */
    explicit Player(QObject *parent = 0, State color = NONE, Type type = UNKNOWN);
};

#endif // PLAYER_H
