#ifndef GAMECONTACTLISTENER_H
#define GAMECONTACTLISTENER_H

#include <Box2D/Box2D.h>
#include <map>

using std::map;

class GameContactListener : public b2ContactListener
{
public:
    GameContactListener();
    void BeginContact(b2Contact* contact);
    map<b2Body*, b2Body*> collidingBodies;
};

#endif // GAMECONTACTLISTENER_H
