#include "tutorialview.h"
#include "qpainter.h"
#include "ui_tutorialview.h"

/*
Wyatt Bruchhauser, Jackson Wetzel, Julia Thomas, Bodie Criswell, Nathaniel Pimentel, Brenlie Shirts
Reviewer: Julia Thomas
CS 3505
Assignment 9: Education App
This class represents the window that comes up when the tutorial button is pressed. Displays information on how to play the game
*/
TutorialView::TutorialView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TutorialView)
{
    ui->setupUi(this);
    ui->exitButton->setStyleSheet(QString("background-color: #BB4430;"));
}

TutorialView::~TutorialView()
{
    delete ui;
}

///
/// \brief onExitButtonClicked
///
void TutorialView::OnExitButtonClicked()
{
    qDebug() << "connecting";
    this->setVisible(false);
}

void TutorialView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::darkGray, 5));

    painter.fillRect(QRect(0,0, this->width(), this->height()), QColor(Qt::white));
    painter.drawLine(this->width(), 0, this->width(), this->height());
    painter.drawLine(0, this->height(), this->width(), this->height());
}

