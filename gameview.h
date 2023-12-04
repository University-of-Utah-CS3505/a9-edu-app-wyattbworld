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

    vector<b2Body*> bodies;

public:
    explicit GameView(QWidget *parent = nullptr);
    ~GameView();

private:
    QRandomGenerator* generator;
    Ui::GameView *ui;
    void paintEvent(QPaintEvent *event);
    const int POSITIONSCALEX = 175;
    const int POSITIONSCALEY = 350;
    void mousePressEvent(QMouseEvent *event);
    const int CIRCLEDROPTIME = 500; //The minimum interval of time (in milliseconds) that the user can drop circles.
    bool dropEnabled; //Determines whether the user is allowed to drop elements into the jar.
    QPoint ModelToGameView(b2Vec2 coord);
    b2Vec2 GameViewToModel(QPoint coord);
    QVector<Atom*> atomList;

public slots:
    void ReceiveStartGame();
    void ReceiveAtomList(QVector<Atom*>);
    void ReceiveUpdateRequest();
    void ReceiveBodies(vector<b2Body*> &sentBodies);

signals:
    void RequestMakeCircleBody(float, float, float);
    void RequestCheckForGameOver(); //This signal is sent to the model to tell it to check if the game is over.
};

#endif // GAMEVIEW_H
