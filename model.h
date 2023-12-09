#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <Box2D/Box2D.h>
#include <stdio.h>
#include <QTimer>
#include <atom.h>
#include <QMap>
#include "gamecontactlistener.h"

using std::vector;
using std::map;

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);
    void BeginGame();

private:
    b2World world;
    const float32 timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 6;
    const int32 positionIterations = 2;

    QTimer* timer;
    QVector<Atom*> elementList;

    QMap<QString, bool> elementStatus;

    int numElementsFound;

    GameContactListener contactListener;


    vector<b2Body*> bodies;
    QVector<Atom*> elementList;
    QMap<QString, bool> elementStatus;
    map<b2Body*, int> catalystJointCount;
    map<b2Body*, vector<b2Body*>> joinedBodies;


    void GameOver(); //Activates the game over sequence.
    void HandleCollision(b2Contact* collissions); // called in update to hanlde all current collissions
    void RemoveBodies(b2Body* body); // removes bodies from the world
    void JoinBodies(b2Body* bodyA, b2Body* bodyB); // creates joint for catalyst
    void Catalyze(b2Body* catalyst, b2Body* nonCatalyst); // handle catalyst

public slots:
    void SendBodiesTemp();
    void UpdateView();
    void MakeCircleBody(float x, float y, float radius);
    void RecieveCheckForGameOver(); //Receives a request to check if the game is over.
    void SendElementStatus(QString element);
    void UpdateElementStatus(QString element);

signals:
    void UpdateWorld();
    void SendBodies(vector<b2Body*> &bodies);
    void SendStartGame();
    void SendAtomList(QVector<Atom*>);
    void RequestDisplayElementInfo(QString element);
    void RequestUpdateProgress(QString element, int numElementsFound);
};

#endif // MODEL_H
