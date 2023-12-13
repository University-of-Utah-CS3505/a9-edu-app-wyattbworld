/*
Wyatt Bruchhauser, Jackson Wetzel, Julia Thomas, Bodie Criswell, Nathaniel Pimentel, Brenlie Shirts
Reviewer: Bodie Crsiwell, Nathaniel Pimentel
CS 3505
Assignment 9: Educational App
This class represents the model for our game. It impliments the declarations in model.h.
*/

#include "model.h"
#include <Box2D/Box2D.h>
#include <QDebug>
#include <QApplication>

Model::Model(QObject *parent)
    : QObject{parent}, world(b2World(b2Vec2(0.0f, 1000.0f)))
{
    // Timer setup
    timer = new QTimer(this);
    connect (timer,
            &QTimer::timeout,
            this,
            &Model::UpdateView);

    // Ground
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 100.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(500.0f, 2.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Left Wall
    b2BodyDef leftWallBodyDef;
    leftWallBodyDef.position.Set(-175.0f, 100.0f);
    b2Body* leftWallBody = world.CreateBody(&leftWallBodyDef);
    b2PolygonShape leftWallBox;
    leftWallBox.SetAsBox(2.0f, 800.0f);
    leftWallBody->CreateFixture(&leftWallBox, 0.0f);

    // Right wall
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

    numElementsFound = 0;
}

void Model::MakeCircleBody(float x, float y, float radius)
{
    // create the definition of the body and adds it to the world
    b2BodyDef circleDef;
    circleDef.type = b2_dynamicBody;
    circleDef.position.Set(x, y);
    b2Body* circleBody = world.CreateBody(&circleDef);

    // define the shape of the body
    b2CircleShape circleShape;
    circleShape.m_radius = radius;

    // attatch that shape to the fixture and define the object's characteristics
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
    emit SetStartButtonVisibility(false);
    emit SetQuitButtonVisibility(false);
    emit SetGameViewVisibility(true);
    emit SetGameOverLabelVisibility(false);
    emit SetTutorialButtonVisibility(false);
    emit SetTutorialButtonSideVisibility(true);
    emit SetAtomImagePreviewVisability(true);
    emit SetNextElementIndicator(true);
    emit SendStartGame();
}

void Model::UpdateView()
{
    world.Step(timeStep, velocityIterations, positionIterations);
    HandleCollision(world.GetContactList());
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
        UpdateElementStatus(element);
    }
}

void Model::UpdateElementStatus(QString element){
    elementStatus[element] = true;
    numElementsFound +=1;
    emit RequestUpdateProgress(element, numElementsFound);
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
    emit SendBodies(bodies);

    emit SetGameOverLabelVisibility(true);
    emit SetGameViewVisibility(false);
    emit SetStartButtonVisibility(true);
    emit SetQuitButtonVisibility(true);
    emit SetTutorialButtonVisibility(true);
    emit SetTutorialButtonSideVisibility(false);
    emit SetAtomImagePreviewVisability(false);
    emit SetNextElementIndicator(false);
}

void Model::HandleCollision(b2Contact* collisions)
{
    // loops over all current contatcts registered within the world
    b2Contact* currentContact = collisions;
    while(currentContact != nullptr)
    {
        b2Body* bodyA = currentContact->GetFixtureA()->GetBody();
        b2Body* bodyB = currentContact->GetFixtureB()->GetBody();

        // ignore contacts with the floor or walls
        if(bodyA->GetType() == 0 || bodyB->GetType() == 0) {
            return;
        }

        float radiusA = bodyA->GetFixtureList()->GetShape()->m_radius;
        float radiusB = bodyB->GetFixtureList()->GetShape()->m_radius;
        float newRadius = radiusA + radiusB;

        // Catalysts are joined with elements until a certain threshold
        bool isACatalyst = (radiusA/3 >= 21 && radiusA/3 <= 30) || (radiusA/3 >= 39 && radiusA/3 <= 48);
        bool isBCatalyst = (radiusB/3 >= 21 && radiusB/3 <= 30) || (radiusB/3 >= 39 && radiusB/3 <= 48);

        // Noble gasses are inert
        bool isANobleGas = (radiusA/3 == 2) || (radiusA/3 == 10) || (radiusA/3 == 18) || (radiusA/3 == 36) || (radiusA/3 == 54);
        bool isBNobleGas = (radiusB/3 == 2) || (radiusB/3 == 10) || (radiusB/3 == 18) || (radiusB/3 == 36) || (radiusB/3 == 54);
        if(isANobleGas || isBNobleGas) {
            return;
        }

        // Elements are inert when joined to a catalyst
        if((isACatalyst && bodyB->GetJointList() != nullptr)
            || (isBCatalyst && bodyA->GetJointList() != nullptr)) {
            return;
        }

        // Two non catalysts are inert if joined to a catalyst
        bool bothNonCatalyst = !isACatalyst && !isBCatalyst;
        bool eitherHaveJoints =  bodyB->GetJointList() != nullptr || bodyA->GetJointList() != nullptr;
        if(bothNonCatalyst && eitherHaveJoints) {
            return;
        }

        // Prevents catalysts from combining
        if((!isACatalyst && isBCatalyst) || (isACatalyst && !isBCatalyst))
        {
            // join the bodies and calculate the catalyst threshold
            if(isACatalyst)
            {
                if(bodyB->GetJointList() == nullptr) {
                    Catalyze(bodyA, bodyB);
                }
            }
            else
            {
                if(bodyA->GetJointList() == nullptr) {
                    Catalyze(bodyB, bodyA);
                }
            }
        }
        else if(newRadius/3-1 < 54)
        {
            // Make a new element
            MakeCircleBody(bodyA->GetPosition().x, bodyA->GetPosition().y, newRadius);
            RemoveBody(bodyA);
            RemoveBody(bodyB);

            // check to see if element is new, to display info
            SendElementStatus(elementList[newRadius/3-1]->elementNotation);
        }
        // progress contact loop
        currentContact = currentContact->GetNext();
    }
}

void Model::Catalyze(b2Body* catalyst, b2Body* nonCatalyst)
{
    JoinBodies(catalyst, nonCatalyst);
    float radius = catalyst->GetFixtureList()->GetShape()->m_radius;
    int catalystThreshold = radius/12;
    int newRadius = 0;

    // When reaction occurs
    if(joinedBodies[catalyst].size() >= (unsigned int) catalystThreshold)
    {
        // Remove joined bodies
        for(b2Body* body : joinedBodies[catalyst]) {
            newRadius += body->GetFixtureList()->GetShape()->m_radius;
            RemoveBody(body);
        }
        RemoveBody(catalyst);

        // Check if valid element
        if(newRadius/3-1 > 54) {
            newRadius = 162;
        }

        // Make new element
        MakeCircleBody(0, 0, newRadius);
        SendElementStatus(elementList[newRadius/3-1]->elementNotation);
    }
}

void Model::RemoveBody(b2Body* body)
{
    vector<b2Body*>::iterator it = std::find(bodies.begin(), bodies.end(), body);
    bodies.erase(it);
    world.DestroyBody(body);
    joinedBodies.erase(body);
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
    jointDef.localAnchorA = b2Vec2 (bodyA->GetLocalCenter().x,bodyA->GetLocalCenter().y + joinedBodies[bodyA].size());
    jointDef.localAnchorB = bodyB->GetLocalCenter();
    jointDef.maxLength = radiusA + radiusB + 5;
    jointDef.collideConnected = true;
    bodyA->GetWorld()->CreateJoint(&jointDef);

    // Keep track of which bodies are joined
    joinedBodies[bodyA].push_back(bodyB);
    joinedBodies[bodyB].push_back(bodyA);
}

void Model::QuitGame() {
    QApplication::quit();
}

void Model::OpenTutorial()
{
    emit SetTutorialViewVisability(true);
}
