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
    qDebug() << "Sending";
    bodies = sentBodies;
}

void GameView::ReceiveUpdateRequest()
{
    repaint();
}

void GameView::paintEvent(QPaintEvent *)
{
   QPainter painter(this);

   painter.setPen(QPen(Qt::black, 3));

    QBrush brush(QColor(0,0,0,255));
    if (bodies.size() > 0){
        QRect rect(bodies[0]->GetPosition().x+200, bodies[0]->GetPosition().y+200, 20, 20);
        painter.drawRect(rect);
        //QPoint center(bodies[0]->GetPosition().x+200,bodies[0]->GetPosition().y+200);
        //painter.drawEllipse(center,(int) bodies[0]->GetFixtureList()->GetShape()->m_radius, (int) bodies[0]->GetFixtureList()->GetShape()->m_radius);
        //qDebug() << bodies[0]->GetPosition().x+200 << ", " << bodies[0]->GetPosition().y+200;
    }
    QRect rect(200,300,200,200);
    painter.drawRect(rect);
}
