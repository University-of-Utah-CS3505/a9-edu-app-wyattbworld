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
}

GameView::~GameView()
{
    delete ui;
}

void GameView::ReceiveBodies(vector<b2Body*> &sentBodies)
{
    bodies = sentBodies;
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

       painter.drawLine(QLine(0, 50, this->width(), 50 ));
       painter.setPen(QPen(Qt::black, 3));

       QPoint position = ModelToGameView(bodies[0]->GetPosition());

        QRect rect(position.x() - 500, position.y() - 1, 1000, 2);
        painter.fillRect(rect, QColor(0,0,0,255));

        position = ModelToGameView(bodies[1]->GetPosition());
        QRect leftRect(position.x() - 1, position.y() - 400, 2, 800);
        painter.fillRect(leftRect, QColor(0,0,0,255));

        position = ModelToGameView(bodies[2]->GetPosition());
        QRect rightRect(position.x() - 1, position.y() -400, 2, 800);
        painter.fillRect(rightRect, QColor(0,0,0,255));

        for (unsigned int i = 3; i < bodies.size(); i++)
        {
            position = ModelToGameView(bodies[i]->GetPosition());
            int radius = bodies[i]->GetFixtureList()->GetShape()->m_radius;
            QPoint center(position.x(), position.y());

            painter.drawEllipse(center, radius, radius);
        }

        emit RequestCheckForGameOver();
    }

    // Background outline
    //QRect backgroundRect(0, 0, this->width(), this->height());
    //painter.drawRect(backgroundRect);
}

void GameView::mousePressEvent(QMouseEvent *event)
{
    if (GameViewToModel(event->pos()).x > -140 && GameViewToModel(event->pos()).x < 140) //Make sure the ball is inside the testtube. 140 are magic numbers that must be changed if you change the size of the walls.
    {
        if (dropEnabled)
        {
            dropEnabled=false; //Make it so the user has to wait before sending the next circle.
            QTimer::singleShot(CIRCLEDROPTIME, [this]{dropEnabled=true;});
            emit RequestMakeCircleBody(GameViewToModel(event->pos()).x , GameViewToModel(QPoint(0, 0)).y, 50.0f);
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
