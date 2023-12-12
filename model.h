#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <atom.h>
#include <QMap>

using std::vector;
using std::map;

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);
    void BeginGame();
    void QuitGame();
    void OpenTutorial();

private:
    b2World world;
    const float32 timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 6;
    const int32 positionIterations = 2;

    QTimer* timer;
    QVector<Atom*> elementList;
    QMap<QString, bool> elementStatus;
    int numElementsFound;
    vector<b2Body*> bodies;
    map<b2Body*, vector<b2Body*>> joinedBodies;

    void GameOver(); //Activates the game over sequence.

    ///
    /// \brief HandleCollision Combine elements.
    /// Noble gasses are inert and catalysts act join with elements unitl a certain threshold.
    /// Walls are ignored.
    /// \param collissions List of fixture contacts.
    ///
    void HandleCollision(b2Contact* collisions);

    ///
    /// \brief RemoveBody Removes a body from the world and model.
    /// \param body Body to remove.
    ///
    void RemoveBody(b2Body* body);

    ///
    /// \brief JoinBodies Joins catalyst with non catalyst.
    /// \param bodyA Catalyst.
    /// \param bodyB Non catalyst.
    ///
    void JoinBodies(b2Body* bodyA, b2Body* bodyB);

    ///
    /// \brief Catalyze A catalyst builds up non catalysts, then reaction occurs when a certain threshold is met.
    /// \param catalyst Catalyst with certain threshold
    /// \param nonCatalyst Becomes inert when joined with catalyst.
    ///
    void Catalyze(b2Body* catalyst, b2Body* nonCatalyst);

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
    void SetGameViewVisibility(bool);
    void SetGameOverLabelVisibility(bool);
    void SetStartButtonVisibility(bool);
    void SetQuitButtonVisibility(bool);
    void SetTutorialButtonVisibility(bool);
    void SetTutorialButtonSideVisibility(bool);
    void SetTutorialViewVisability(bool);
    void SetAtomImagePreviewVisability(bool);
    void SetNextElementIndicator(bool);
};

#endif // MODEL_H
