#include "model.h"
#include <Box2D/Box2D.h>
#include <stdio.h>
#include <QApplication>
#include <QDebug>
#include "tutorialview.h"

Model::Model(QObject *parent)
    : QObject{parent}, world(b2World(b2Vec2(0.0f, 100.0f)))
{
    // Timer setup
    timer = new QTimer(this);
    connect (timer,
            &QTimer::timeout,
            this,
            &Model::UpdateView);



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
        for (unsigned int i = 0; i < 10; i++)
        {
            elementList.push_back(new Atom (nullptr, i));
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
    emit SetStartButtonVisibility(false);
    emit SetQuitButtonVisibility(false);
    emit SetGameViewVisibility(true);
    emit SetGameOverLabelVisibility(false);
    emit SetTutorialButtonVisibility(false);
    emit SetTutorialButtonSideVisibility(true);
    emit SendStartGame();
}

void Model::UpdateView()
{
    world.Step(timeStep, velocityIterations, positionIterations);
    emit UpdateWorld();
}

void Model::SendBodiesTemp()
{
    emit SendBodies(bodies);
    BeginGame();
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
    SendBodiesTemp();
    emit SetGameOverLabelVisibility(true);
    emit SetGameViewVisibility(false);
    emit SetStartButtonVisibility(true);
    emit SetQuitButtonVisibility(true);
    emit SetTutorialButtonVisibility(true);
    emit SetTutorialButtonSideVisibility(false);
}

void Model::QuitGame() {
    QApplication::quit();
}

void Model::OpenTutorial()
{
    emit SetTutorialViewVisability(true);
    qDebug() << "Open";
}
// Box2D code from lab14
//int main(int argc, char** argv)
//{
//    B2_NOT_USED(argc);
//    B2_NOT_USED(argv);

//    // Define the gravity vector.
//    b2Vec2 gravity(0.0f, -10.0f);

//    // Construct a world object, which will hold and simulate the rigid bodies.
//    b2World world(gravity);

//    // Define the ground body.
//    b2BodyDef groundBodyDef;
//    groundBodyDef.position.Set(0.0f, -10.0f);

//    // Call the body factory which allocates memory for the ground body
//    // from a pool and creates the ground box shape (also from a pool).
//    // The body is also added to the world.
//    b2Body* groundBody = world.CreateBody(&groundBodyDef);

//    // Define the ground box shape.
//    b2PolygonShape groundBox;

//    // The extents are the half-widths of the box.
//    groundBox.SetAsBox(50.0f, 10.0f);

//    // Add the ground fixture to the ground body.
//    groundBody->CreateFixture(&groundBox, 0.0f);

//    // Define the dynamic body. We set its position and call the body factory.
//    b2BodyDef bodyDef;
//    bodyDef.type = b2_dynamicBody;
//    bodyDef.position.Set(0.0f, 4.0f);
//    b2Body* body = world.CreateBody(&bodyDef);

//    // Define another box shape for our dynamic body.
//    b2PolygonShape dynamicBox;
//    dynamicBox.SetAsBox(1.0f, 1.0f);

//    // Define the dynamic body fixture.
//    b2FixtureDef fixtureDef;
//    fixtureDef.shape = &dynamicBox;

//    // Set the box density to be non-zero, so it will be dynamic.
//    fixtureDef.density = 1.0f;

//    // Override the default friction.
//    fixtureDef.friction = 0.3f;

//    // Add the shape to the body.
//    body->CreateFixture(&fixtureDef);

//    // Prepare for simulation. Typically we use a time step of 1/60 of a
//    // second (60Hz) and 10 iterations. This provides a high quality simulation
//    // in most game scenarios.
//    float32 timeStep = 1.0f / 60.0f;
//    int32 velocityIterations = 6;
//    int32 positionIterations = 2;

//    // This is our little game loop.
//    for (int32 i = 0; i < 60; ++i)
//    {
//        // Instruct the world to perform a single step of simulation.
//        // It is generally best to keep the time step and iterations fixed.
//        world.Step(timeStep, velocityIterations, positionIterations);

//        // Now print the position and angle of the body.
//        b2Vec2 position = body->GetPosition();
//        float32 angle = body->GetAngle();

//        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
//    }

//    // When the world destructor is called, all bodies and joints are freed. This can
//    // create orphaned pointers, so be careful about your world management.

//    return 0;
//}
