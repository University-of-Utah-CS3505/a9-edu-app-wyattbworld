#include "tutorialview.h"
#include "qpainter.h"
#include "ui_tutorialview.h"

TutorialView::TutorialView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TutorialView)
{
    ui->setupUi(this);
}

TutorialView::~TutorialView()
{
    delete ui;
}

void TutorialView::on_exitButton_clicked()
{
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

