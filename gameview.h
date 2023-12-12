/*
Wyatt Bruchhauser, Jackson Wetzel, Julia Thomas, Bodie Criswell, Nathaniel Pimentel, Brenlie Shirts
CS 3505
Assignment 9 : Educational App
File Description: This file details the functionality of our game window.
*/

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QImage>
#include <QPen>
#include <QPainter>
#include <QColor>
#include <QRect>
#include <QMouseEvent>
#include <atom.h>
#include <QRandomGenerator>
#include <QtMath>

#include <Box2D/Box2D.h>
#include <stdio.h>


using std::vector;

namespace Ui {
class GameView;
}

class GameView : public QWidget
{
    Q_OBJECT

    b2World world;

    vector<b2Body*> bodies; //Every object in our world is in this.

public:
    explicit GameView(QWidget *parent = nullptr);
    ~GameView();

private:
    QRandomGenerator* generator; //Used for generating elements randomly.
    Ui::GameView *ui;
    void paintEvent(QPaintEvent *event);
    const int POSITIONSCALEX = 175; //These constants represent how many pixels the game view translates from the game world.
    const int POSITIONSCALEY = 350;
    void mousePressEvent(QMouseEvent *event);
    const int CIRCLEDROPTIME = 500; //The minimum interval of time (in milliseconds) that the user can drop circles.
    bool dropEnabled; //Determines whether the user is allowed to drop elements into the jar.
    QPoint ModelToGameView(b2Vec2 coord);
    b2Vec2 GameViewToModel(QPoint coord);
    QVector<Atom*> atomList; //The list of atoms theat can be generated.
    Atom* nextAtom; //Used for the element preview.

public slots:
    void ReceiveStartGame(); //Allows users to drop bodies.
    void ReceiveAtomList(QVector<Atom*>); //Allows atom to talk to us.
    void ReceiveUpdateRequest(); //Is used by other classes to update the screen.
    void ReceiveBodies(vector<b2Body*> &sentBodies); //Connects the model to the view.

signals:
    void RequestMakeCircleBody(float, float, float); //Can be used to summon a new body in the model.
    void RequestCheckForGameOver(); //This signal is sent to the model to tell it to check if the game is over.
    void RequestElementStatus(QString name); //Used for sending what elements have been dropped.
    void ChangeElementStatus(QString name); //Used to update discovered status.
    void SendAtomPreview(Atom* nextAtom); //Used to send the atom for preview.
};

#endif // GAMEVIEW_H
