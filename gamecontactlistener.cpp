#include "gamecontactlistener.h"
#include <QObject>
#include <map>
#include <QDebug>

using std::map;

GameContactListener::GameContactListener()
{
    //    collidingBodies = map<b2Body*, b2Body>();
}

void GameContactListener::BeginContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    b2Vec2 posA = bodyA->GetPosition();
    b2Vec2 posB = bodyB->GetPosition();

    // We want to check if the body is not a floor/wall
    // We do this by setting the circle bodies userData in the model
    // For now, this differentiates between circles and floor/wall, more differences will have to be dealt with in the model
    if(bodyA->GetUserData() && bodyB->GetUserData()) {
        qDebug() << "posA: " << posA.x << ", " << posA.y;
        qDebug() << "posB: " << posB.x << ", " << posB.y;
        collidingBodies[bodyA] = bodyB;
    }

}
