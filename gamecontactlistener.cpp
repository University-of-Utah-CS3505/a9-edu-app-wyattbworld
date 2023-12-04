#include "gamecontactlistener.h"
#include <QObject>

#include <map>

using std::map;

GameContactListener::GameContactListener()
{
    collidingBodies = map<b2Body*, b2Body>();
}

void GameContactListener::BeginContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();


    collidingBodies[bodyA] = bodyB;
}
