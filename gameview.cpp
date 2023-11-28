#include "gameview.h"
#include "ui_gameview.h"

#include <QWidget>

GameView::GameView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameView)
{
    ui->setupUi(this);
}

GameView::~GameView()
{
    delete ui;
}

void GameView::ReceiveBodies(vector<b2Body*> sentBodies)
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

    QBrush brush(QColor(0,0,0,255));
    QPoint center(bodies[0]->GetPosition().x+200,bodies[0]->GetPosition().y+200);
    painter.drawEllipse(center,(int) bodies[0]->GetFixtureList()->GetShape()->m_radius+200, (int) bodies[0]->GetFixtureList()->GetShape()->m_radius+200);

    QRect rect(200,300,2,2);
    painter.drawRect(rect);
}
