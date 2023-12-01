#include "gameview.h"
#include "ui_gameview.h"
#include <QDebug>
#include <QWidget>

GameView::GameView(QWidget *parent) :
    QWidget(parent),
    world(b2World(b2Vec2(0.0f, -9.8f))),
    ui(new Ui::GameView)
{

    ui->setupUi(this);
}

GameView::~GameView()
{
    delete ui;
}

void GameView::ReceiveBodies(vector<b2Body*> &sentBodies)
{
    bodies = sentBodies;
}

void GameView::ReceiveUpdateRequest()
{
    update();
}

void GameView::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   painter.setPen(QPen(Qt::black, 3));

   // Brush determines fill color


    if (bodies.size() > 0){
        b2Vec2 position = bodies[0]->GetPosition();

        position = bodies[0]->GetPosition();
        QRect rect(position.x + POSITIONSCALE - 500, position.y + POSITIONSCALE - 1, 1000, 2);
        painter.fillRect(rect, QColor(0,0,0,255));

        position = bodies[1]->GetPosition();
        QRect leftRect(position.x + POSITIONSCALE - 1, position.y + POSITIONSCALE - 500, 2, 1000);
        painter.fillRect(leftRect, QColor(0,0,0,255));

        position = bodies[2]->GetPosition();
        QRect rightRect(position.x + POSITIONSCALE - 1, position.y + POSITIONSCALE - 500, 2, 1000);
        painter.fillRect(rightRect, QColor(0,0,0,255));

        for (int i = 3; i < bodies.size(); i++)
        {
            position = bodies[i]->GetPosition();
            int radius = bodies[i]->GetFixtureList()->GetShape()->m_radius;
            QPoint center(position.x + POSITIONSCALE, position.y + POSITIONSCALE);

            painter.drawEllipse(center, radius, radius);
        }
    }

    // Background outline
    QRect backgroundRect(0, 0, this->width(), this->height());
    painter.drawRect(backgroundRect);
}

void GameView::mousePressEvent(QMouseEvent *event)
{
    if (event->pos().x() > -140 + POSITIONSCALE && event->pos().x() < 140 + POSITIONSCALE) //Make sure the ball is inside the testtube. 140 are magic numbers that must be changed if you change the size of the walls.
    {
        if ( bodies.size() > 0) //Make sure there are bodies in the game world.
        {
        emit RequestMakeCircleBody(event->pos().x() -POSITIONSCALE , -POSITIONSCALE, 10.0f);
        }
    }
}
