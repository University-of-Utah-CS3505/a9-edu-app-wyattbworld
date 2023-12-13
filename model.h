/*
Wyatt Bruchhauser, Jackson Wetzel, Julia Thomas, Bodie Criswell, Nathaniel Pimentel, Brenlie Shirts
Reviewer: Bodie Crsiwell, Nathaniel Pimentel
CS 3505
Assignment 9: Educational App
This class declares the methods and fields of our model class. It represents the model in the MV application design.
*/

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
    ///
    /// \brief SendBodiesTemp Recieves the request from view and sends bodies to the view to be rendered.
    ///
    void SendBodiesTemp();

    ///
    /// \brief UpdateView Steps the simulation and handles any collissions.
    ///
    void UpdateView();

    ///
    /// \brief MakeCircleBody Creates a new circle body in the simulation.
    /// \param x The x coordinate in the box2D world.
    /// \param y The y coordinate in the box2D world.
    /// \param radius The radius of the circle shape created.
    ///
    void MakeCircleBody(float x, float y, float radius);

    ///
    /// \brief RecieveCheckForGameOver Checks if the game is still in an active state.
    ///
    void RecieveCheckForGameOver();

    ///
    /// \brief SendElementStatus Requests the element status for the element specified.
    /// \param element The element that's status will be checked.
    ///
    void SendElementStatus(QString element);

    ///
    /// \brief UpdateElementStatus Updates the current status of the element to be found once found.
    /// \param element The new element that was foudn.
    ///
    void UpdateElementStatus(QString element);

signals:
    void UpdateWorld(); // sent to view to update world state
    void SendBodies(vector<b2Body*> &bodies); // sends the bodies vector for view to render them
    void SendStartGame(); // sends the signal to begin the game
    void SendAtomList(QVector<Atom*>); // sends the atom list to the view
    void RequestDisplayElementInfo(QString element); // requests the info of an element for display
    void RequestUpdateProgress(QString element, int numElementsFound); // requests the current game progress
    void SetGameViewVisibility(bool); // sets the visibility of the game window in mainwindow
    void SetGameOverLabelVisibility(bool); // enables or disables the game over screen
    void SetStartButtonVisibility(bool); // enables or disables the start button
    void SetQuitButtonVisibility(bool); // enables or disables the quit button
    void SetTutorialButtonVisibility(bool); // enables or disables the toturial button
    void SetTutorialButtonSideVisibility(bool); // enables or disables the border toturial button
    void SetTutorialViewVisability(bool); // enables or disables the toturial
    void SetAtomImagePreviewVisability(bool); // enables or disables the atom information window
    void SetNextElementIndicator(bool); // enables or disables the element indicator
};

#endif // MODEL_H
