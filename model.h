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

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);
    void BeginGame();
    GameContactListener contactListener; // the instance of the contact listener used for the game

private:
    b2World world;
    vector<b2Body*> bodies;
    const float32 timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 6;
    const int32 positionIterations = 2;


    QTimer* timer;
    QVector<Atom*> elementList;

    QMap<QString, bool> elementStatus;

    void GameOver(); //Activates the game over sequence.
    void RemoveBodies(b2Body* bodyA, b2Body* bodyB); // Remove bodies that collided
    void joinBodies(b2Body* bodyA, b2Body* bodyB);

public slots:
    void SendBodiesTemp();
    void UpdateView();
    void MakeCircleBody(float x, float y, float radius);
    void RecieveCheckForGameOver(); //Receives a request to check if the game is over.
    void SendElementStatus(QString element);
    void UpdateElementStatus(QString element);
    void QuitGame();
    void HandleCollision(map<b2Body*, b2Body*>); // handle the collisison signal

signals:
    void UpdateWorld();
    void SendBodies(vector<b2Body*> &bodies);
    void SendStartGame();
    void SendAtomList(QVector<Atom*>);
    void RequestDisplayElementInfo(QString element);
    void SetStartButtonVisibility(bool);
    void SetQuitButtonVisibility(bool);
    void SetGameViewVisibility(bool);
    void SetGameOverLabelVisibility(bool);
};

#endif // MODEL_H
