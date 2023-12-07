#include "model.h"
#include <Box2D/Box2D.h>
#include <stdio.h>
#include <QDebug>

Model::Model(QObject *parent)
    : QObject{parent}, world(b2World(b2Vec2(0.0f, 1000.0f)))
{
    // Timer setup
    timer = new QTimer(this);
    connect (timer,
            &QTimer::timeout,
            this,
            &Model::UpdateView);

    world.SetContactListener(&contactListener);

    // Define the ground body.
    b2BodyDef groundBodyDef;

    // Set up the ground position. 90 seems to match the gameview's ground
    groundBodyDef.position.Set(0.0f, 100.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    // Define the ground box shape.
    b2PolygonShape groundBox;
    // The extents are the half-widths of the box.
    groundBox.SetAsBox(500.0f, 2.0f);
    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    b2BodyDef leftWallBodyDef;
    leftWallBodyDef.position.Set(-175.0f, 100.0f);
    b2Body* leftWallBody = world.CreateBody(&leftWallBodyDef);
    b2PolygonShape leftWallBox;
    leftWallBox.SetAsBox(2.0f, 800.0f);
    leftWallBody->CreateFixture(&leftWallBox, 0.0f);

    b2BodyDef rightWallBodyDef;
    rightWallBodyDef.position.Set(175.0f, 100.0f);
    b2Body* rightWallBody = world.CreateBody(&rightWallBodyDef);
    b2PolygonShape rightWallBox;
    rightWallBox.SetAsBox(2.0f, 800.0f);
    rightWallBody->CreateFixture(&rightWallBox, 0.0f);

    // Unsure if we need to add ground to bodies
    bodies.push_back(groundBody);

    // Create a repository for all potential Atoms in the game.
    for (unsigned int i = 0; i < 54; i++)
    {
        elementList.push_back(new Atom (nullptr, i+1));
    }

    for (Atom* atom : elementList){
        elementStatus[atom->elementNotation] = false;
    }
    bodies.push_back(leftWallBody);
    bodies.push_back(rightWallBody);
}

void Model::MakeCircleBody(float x, float y, float radius)
{
    b2BodyDef circleDef;
    circleDef.type = b2_dynamicBody;
    circleDef.position.Set(x, y);
    b2Body* circleBody = world.CreateBody(&circleDef);
    circleBody->SetUserData(this);

    b2CircleShape circleShape;
    circleShape.m_radius = radius;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.9f;
    circleBody->CreateFixture(&fixtureDef);
    bodies.push_back(circleBody);
    emit SendBodies(bodies);
}

void Model::BeginGame()
{
    timer->start(1000/60);
    emit SendStartGame();
    emit SendAtomList(elementList);
}

void Model::UpdateView()
{
    world.Step(timeStep, velocityIterations, positionIterations);
    HandleCollision(contactListener.collidingBodies);
    emit UpdateWorld();
}

void Model::SendBodiesTemp()
{
    emit SendBodies(bodies);
    BeginGame();
}

void Model::SendElementStatus(QString element){
    if (!elementStatus[element]){
        emit RequestDisplayElementInfo(element);
    }
}

void Model::UpdateElementStatus(QString element){
    elementStatus[element] = true;
}

void Model::RecieveCheckForGameOver()
{
    for (unsigned int i = 3; i < bodies.size(); i++)
    {
        if (bodies[i]->GetPosition().y < bodies[1]->GetPosition().y - 400 && //This checks if the ball is above the red line.
            bodies[i]->GetLinearVelocity().y < 0) //This checks if the velocity is negative, it is it means the ball bounced on something which means it is not dropping from the top of the screen.
        {
            GameOver();
        }
    }
}

void Model::GameOver()
{
    for (unsigned int i = 3; i < bodies.size(); i++) //This behavior is temporary and we can change it to whatever we need later.
    {
        world.DestroyBody(bodies[i]);
    }

    vector<b2Body*> temp {bodies[0], bodies[1], bodies[2]};
    bodies = temp;
    emit SendBodiesTemp();
}

void Model::HandleCollision(map<b2Body*, b2Body*> collisions)
{
    for(auto& [bodyA, bodyB] : collisions) {
        float radiusA = bodyA->GetFixtureList()->GetShape()->m_radius;
        float radiusB = bodyB->GetFixtureList()->GetShape()->m_radius;
        float newRadius = radiusA + radiusB;

        // check if one of them is a catalyst
        bool isACatalyst = (radiusA/3 >= 21 && radiusA/3 <= 30) || (radiusA/3 >= 39 && radiusA/3 <= 48);
        bool isBCatalyst = (radiusB/3 >= 21 && radiusB/3 <= 30) || (radiusB/3 >= 39 && radiusB/3 <= 48);

        // QString elementA = elementList[radiusA/3-1]->elementNotation;
        // QString elementB = elementList[radiusB/3-1]->elementNotation;
        // qDebug() << elementA << " is catalyst: "  << isACatalyst;
        // qDebug() << elementB << " is catalyst: " << isBCatalyst;


        // Prevents catalysts from reacting
        if((!isACatalyst && isBCatalyst) || (isACatalyst && !isBCatalyst))
        {
            // join the bodies and calculate the catalyst threshold
            if(isACatalyst)
            {
                if(catalystJointCount.count(bodyB) == 0) {
                    JoinBodies(bodyA, bodyB);
                    Catalyze(bodyA, bodyB);

                }
            }
            else
            {
                if(catalystJointCount.count(bodyA) == 0) {
                    JoinBodies(bodyB, bodyA);
                    Catalyze(bodyB, bodyA);
                }
            }
        }
        else if(newRadius/3-1 < 54)
        {
            // If non catalyst has a joint, ignore it
            if((isACatalyst && catalystJointCount.count(bodyB) >= 1)
                || (isBCatalyst && catalystJointCount.count(bodyA) >= 1)) {
                qDebug() << "ignore when joined";
                return;
            }

            // Two non catalysts collide and either one is joined, we don't want them to combine
            bool bothNonCatalyst = !isACatalyst && !isBCatalyst;
            bool eitherHaveJoints =  catalystJointCount.count(bodyB) >= 1 || catalystJointCount.count(bodyA) >= 1;
            if(bothNonCatalyst && eitherHaveJoints) {
                return;
            }

            // Make a circle based on posA
            MakeCircleBody(bodyA->GetPosition().x, bodyA->GetPosition().y, newRadius);
            // Remove bodies when they collide
            RemoveBodies(bodyA);
            RemoveBodies(bodyB);

            // check to see if element is new
            SendElementStatus(elementList[newRadius/3-1]->elementNotation);
        }
    }
}

void Model::Catalyze(b2Body* catalyst, b2Body* nonCatalyst)
{
    float radius = catalyst->GetFixtureList()->GetShape()->m_radius;
    // int catalystThreshold = radius/12;

    // qDebug() << "catalyst threshold: " << catalystThreshold;

    // When reaction occurs
    if(catalystJointCount[catalyst] >= 2)
    {
        qDebug() << "Removing catalyst";

        // destroy joints
        // b2JointEdge* current = catalyst->GetJointList()->next;
        // while(current != nullptr) {
        //     world.DestroyJoint(current->joint);
        //     current = current->next;
        // }

        // Crashing inconsistenly when reaction occurs.

        RemoveBodies(catalyst);
        RemoveBodies(nonCatalyst);
        // We are not deleting every joined noncatalyst, just the most recently joined.
        // Thus the non removed noncatayst isn't removed from the jointCount.

        // Can fix by changing jointCount to just hold joints (map of catalyst and vector of non catalysts)
    }
}

void Model::RemoveBodies(b2Body* body)
{
    // Remove bodyA from bodies and world
    vector<b2Body*>::iterator it = std::find(bodies.begin(), bodies.end(), body);
    if(it != bodies.end()) {
        bodies.erase(it);
        world.DestroyBody(body);
        catalystJointCount.erase(body);
    }
    contactListener.collidingBodies.clear();
    emit SendBodies(bodies);
}

void Model::JoinBodies(b2Body* bodyA, b2Body* bodyB)
{
    float radiusA = bodyA->GetFixtureList()->GetShape()->m_radius;
    float radiusB = bodyB->GetFixtureList()->GetShape()->m_radius;

    // Create a joint, attaching bodies
    b2RopeJointDef jointDef;
    jointDef.bodyA = bodyA;
    jointDef.bodyB = bodyB;
    jointDef.localAnchorA = bodyA->GetLocalCenter();
    jointDef.localAnchorB = bodyB->GetLocalCenter();
    jointDef.maxLength = radiusA + radiusB + 5;
    jointDef.collideConnected = true;
    bodyA->GetWorld()->CreateJoint(&jointDef);

    // Accumlate joint count
    catalystJointCount[bodyA] += 1;
    catalystJointCount[bodyB] += 1;

    qDebug() << "catalyst joint count: " << catalystJointCount[bodyA];
    qDebug() << "non catalyst joint count: " << catalystJointCount[bodyB];

}
