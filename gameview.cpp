/*
Wyatt Bruchhauser, Jackson Wetzel, Julia Thomas, Bodie Criswell, Nathaniel Pimentel, Brenlie Shirts
CS 3505
Assignment 9 : Educational App
File Description: This file details the functionality of our game window.
*/

#include "gameview.h"
#include "ui_gameview.h"
#include <QDebug>
#include <QWidget>
#include <QTimer>

GameView::GameView(QWidget *parent) :
    QWidget(parent),
    world(b2World(b2Vec2(0.0f, -9.8f))),
    ui(new Ui::GameView)
{

    ui->setupUi(this);
    dropEnabled = false;
    generator = QRandomGenerator::global();
}

GameView::~GameView()
{
    delete ui;
}

void GameView::ReceiveBodies(vector<b2Body*> &sentBodies)
{
    bodies = sentBodies;
}

void GameView::ReceiveAtomList(QVector<Atom*> elements)
{
    atomList = elements;
    nextAtom = atomList[generator->bounded(10)]; //We only want the first 10 elements of the periodic table.
    emit SendAtomPreview(nextAtom);
}

void GameView::ReceiveStartGame()
{
    dropEnabled = true;
}

void GameView::ReceiveUpdateRequest()
{
    update();
}

void GameView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if (bodies.size() > 0){
        painter.setPen(QPen(Qt::red, 1));

        painter.drawLine(QLine(0, 50, this->width(), 50 )); //drawing the game over line.
        painter.setPen(QPen(Qt::black, 3));

        QPoint position = ModelToGameView(bodies[0]->GetPosition());

        QRect rect(position.x() - 500, position.y() - 1, 1000, 2); //Drawing the floor
        painter.fillRect(rect, QColor(0,0,0,255));

        position = ModelToGameView(bodies[1]->GetPosition());
        QRect leftRect(position.x() - 1, position.y() - 400, 2, 800); //Drawing the left wall
        painter.fillRect(leftRect, QColor(0,0,0,255));

        position = ModelToGameView(bodies[2]->GetPosition());
        QRect rightRect(position.x() - 1, position.y() -400, 2, 800); //Drawing the right wall
        painter.fillRect(rightRect, QColor(0,0,0,255));

        //Drawing the atoms.
        for (unsigned int i = 3; i < bodies.size(); i++) //We start at 3 because the first 3 bodies are the walls and ceiling.
        {
            position = ModelToGameView(bodies[i]->GetPosition());
            int radius = bodies[i]->GetFixtureList()->GetShape()->m_radius;
            QPoint center(position.x(), position.y());

            painter.drawPixmap(center.x()-radius, center.y()-radius, atomList[radius/3-1]->atomBody);

            // if catalyst draw its joints
            if((radius/3 >= 21 && radius/3 <= 30) || (radius/3 >= 39 && radius/3 <= 48))
            {
                // set joint brightness based on connected joints
                b2JointEdge* currentJointTotal = bodies[i]->GetJointList();
                int joints = 0;
                while(currentJointTotal != nullptr)
                {
                    joints = joints + 1;
                    currentJointTotal = currentJointTotal->next;
                }
                int alpha = 255 * ((double)(joints + 2) / (radius/12 + 2)); //The line becomes less transparent as more joints connect.

                b2JointEdge* currentJoint = bodies[i]->GetJointList();
                painter.setPen(QPen(QColor(255, 17, 0, alpha), 3));
                while(currentJoint != nullptr)
                {
                    QPoint posA = ModelToGameView(currentJoint->joint->GetBodyA()->GetPosition());
                    QPoint posB = ModelToGameView(currentJoint->joint->GetBodyB()->GetPosition());
                    painter.drawLine(posA, posB);
                    currentJoint = currentJoint->next;
                }
            }
        }

        emit RequestCheckForGameOver();
    }
}

void GameView::mousePressEvent(QMouseEvent *event)
{
    if (GameViewToModel(event->pos()).x > -140 && GameViewToModel(event->pos()).x < 140) //Make sure the ball is inside the testtube. 140 are magic numbers that must be changed if you change the size of the walls.
    {
        if (dropEnabled)
        {
            dropEnabled=false; //Make it so the user has to wait before sending the next circle.
            QTimer::singleShot(CIRCLEDROPTIME, [this]{dropEnabled=true;});

            emit RequestMakeCircleBody(GameViewToModel(event->pos()).x , GameViewToModel(QPoint(0, 0)).y, nextAtom->radius);
            emit ChangeElementStatus(nextAtom->elementNotation);
            nextAtom = atomList[generator->bounded(10)];
            emit SendAtomPreview(nextAtom);
            emit RequestElementStatus(nextAtom->elementNotation);
        }
    }
}

QPoint GameView::ModelToGameView(b2Vec2 coord)
{
    return QPoint(coord.x + POSITIONSCALEX, coord.y + POSITIONSCALEY);
}

b2Vec2 GameView::GameViewToModel(QPoint coord)
{
    return b2Vec2(coord.x() - POSITIONSCALEX, coord.y() - POSITIONSCALEY);
}
