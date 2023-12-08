#include "tutorialview.h"
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
