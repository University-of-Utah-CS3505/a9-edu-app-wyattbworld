#ifndef GAMECONTACTLISTENER_H
#define GAMECONTACTLISTENER_H

#include <Box2D/Box2D.h>
#include <QHash>

class GameContactListener : public b2ContactListener
{
public:
    GameContactListener();
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    QHash<b2Body*, QHash<b2Body*, bool>> collidingBodies;
};

#endif // GAMECONTACTLISTENER_H
