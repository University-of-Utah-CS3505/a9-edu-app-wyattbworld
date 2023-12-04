#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(Model &model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect (&model,
            &Model::UpdateWorld,
            ui->gameView,
            &GameView::ReceiveUpdateRequest);

    connect (&model,
            &Model::SendBodies,
            ui->gameView,
            &GameView::ReceiveBodies);
    
    connect (ui->startButton,
            &QPushButton::clicked,
            &model,
            &Model::SendBodiesTemp);

    connect (ui->gameView,
            &GameView::RequestMakeCircleBody,
            &model,
            &Model::MakeCircleBody);

    connect (&model,
            &Model::SendStartGame,
            ui->gameView,
            &GameView::ReceiveStartGame);

    //here is an example of what the element popup will look like, obviously not implemented correctly yet
//    ui->elementDescription->setTitleContent("01Hydrogen");
//    ui->elementDescription->setAssetContent("01Hydrogen");
//    ui->elementDescription->setImageContent("01Hydrogen");
//    ui->elementDescription->setKeyProperties("01Hydrogen");
//    ui->elementDescription->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

