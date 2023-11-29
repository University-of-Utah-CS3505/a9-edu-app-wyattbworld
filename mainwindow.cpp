#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(Model &model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&model,
            &Model::UpdateView,
            ui->gameView,
            &GameView::ReceiveUpdateRequest);

    connect(&model,
            &Model::SendBodies,
            ui->gameView,
            &GameView::ReceiveBodies);

    connect (ui->pushButton,
            &QPushButton::clicked,
            &model,
            &Model::SendBodiesTemp);



}

MainWindow::~MainWindow()
{
    delete ui;
}

