#include "gameevent.h"
#include "gameengine.h"

GameEvent::GameEvent(GameEvent::eventCode event, Square *square)
{
    m_gameEvent = event;
    m_square = square;
    GameEngine::eventQueue.enqueue(this);
}
