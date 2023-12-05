#include "gamecontactlistener.h"
#include <QObject>
#include <Box2D/Box2D.h>

#include <QDebug>

GameContactListener::GameContactListener()
{
    collidingBodies = QHash<b2Body*, QHash<b2Body*, bool>>();
}

void GameContactListener::BeginContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    // add collission to A's map
    if(collidingBodies.count(bodyA) == 0)
    {
        QHash<b2Body*, bool> bodysCollisions;
        bodysCollisions[bodyB] = true;
        collidingBodies[bodyA] = bodysCollisions;
    }
    else
    {
        collidingBodies[bodyA][bodyB] = true;
    }

    // add collission to B's map
    if(collidingBodies.count(bodyB) == 0)
    {
        QHash<b2Body*, bool> bodysCollisions;
        bodysCollisions[bodyA] = true;
        collidingBodies[bodyB] = bodysCollisions;
    }
    else
    {
        collidingBodies[bodyB][bodyA] = true;
    }

    // if bodies coliding are possible catalyst and element apply joint
    if(bodyA->GetType() != 0 && bodyA->GetType() != 0)
    {
//        bool p = bodyA->GetFixtureList()->GetShape()->m_radius == 30.0f;
//        bool q = bodyA->GetFixtureList()->GetShape()->m_radius == 30.0f;

        bool p = false;
        bool q = true;

        if(q)
        {
            b2RopeJointDef jointDef;
            jointDef.bodyA = bodyA;
            jointDef.bodyB = bodyB;
//            jointDef.localAnchorA = bodyA->GetLocalCenter();
//            jointDef.localAnchorB = bodyB->GetLocalCenter();
            jointDef.maxLength = 105.0f;

            bodyA->GetWorld()->CreateJoint(&jointDef);
        }

    }

    qDebug() << "collission added: " << bodyA->GetType() << "," << bodyB->GetType();
}

void GameContactListener::EndContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    if(collidingBodies.count(bodyA) > 0)
        collidingBodies[bodyA].remove(bodyB);

    if(collidingBodies.count(bodyB) > 0)
        collidingBodies[bodyB].remove(bodyA);

    qDebug() << "collission removed: " << collidingBodies.count(bodyA);
}
