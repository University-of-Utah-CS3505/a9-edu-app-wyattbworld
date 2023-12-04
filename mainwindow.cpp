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

    connect (ui->gameView,
            &GameView::RequestCheckForGameOver,
            &model,
            &Model::RecieveCheckForGameOver);

    connect (&model,
            &Model::SendAtomList,
            ui->gameView,
            &GameView::ReceiveAtomList);
}

MainWindow::~MainWindow()
{
    delete ui;
}

