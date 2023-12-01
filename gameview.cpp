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
    update();
}

void GameView::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   painter.setPen(QPen(Qt::black, 3));

   // Brush determines fill color
//   QBrush brush(QColor(0,0,0,255));
//   painter.setBrush(brush);

    if (bodies.size() > 0){
        b2Vec2 position = bodies[0]->GetPosition();
        int radius = bodies[0]->GetFixtureList()->GetShape()->m_radius;
        qDebug() << "position: " << position.x << " " << position.y;
        // Draw a circle
        QPoint center(position.x, position.y);
        painter.drawEllipse(center, radius, radius);

//        QRect rect(position.x + POSITIONSCALE, position.y + POSITIONSCALE, 20, 20);
//        painter.drawRect(rect);

    }

    // Background outline
    QRect backgroundRect(0, 0, this->width(), this->height());
    painter.drawRect(backgroundRect);
}
