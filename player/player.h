#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "define.h"

class Player : public QObject
{
    Q_OBJECT
public:

    Type m_type;
    State m_color;

    explicit Player(QObject *parent = 0, State color = NONE, Type type = UNKNOWN);


signals:

public slots:
};

#endif // PLAYER_H
