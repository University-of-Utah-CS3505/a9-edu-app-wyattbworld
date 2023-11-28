#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QImage>
#include <QPen>
#include <QPainter>
#include <QColor>
#include <QRect>

#include <Box2D/Box2D.h>
#include <stdio.h>


using std::vector;

namespace Ui {
class GameView;
}

class GameView : public QWidget
{
    Q_OBJECT

    vector<b2Body*> bodies;

public:
    explicit GameView(QWidget *parent = nullptr);
    ~GameView();

private:
    Ui::GameView *ui;
    void paintEvent(QPaintEvent *event);

public slots:
    void ReceiveUpdateRequest();
    void ReceiveBodies(vector<b2Body*> sentBodies);
};

#endif // GAMEVIEW_H
