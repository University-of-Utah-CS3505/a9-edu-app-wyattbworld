#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <Box2D/Box2D.h>
#include <stdio.h>

using std::vector;

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);
    void BeginGame();

private:
    b2World world;
    vector<b2Body*> bodies;

public slots:
    void SendBodiesTemp();
signals:
    void UpdateView();
    void SendBodies(vector<b2Body*> &bodies);
};

#endif // MODEL_H
