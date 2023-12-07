#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(Model &model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->elementInfo->hide();

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

    connect (ui->gameView,
            &GameView::RequestElementStatus,
            &model,
            &Model::SendElementStatus);

    connect (&model,
            &Model::RequestDisplayElementInfo,
            ui->elementInfo,
            &ElementInfo::SetElementInfo);

    connect (ui->elementInfo,
            &ElementInfo::RequestDisplayElementInfo,
            this,
            &MainWindow::DisplayElementInfo);

    connect (ui->elementInfo,
            &ElementInfo::closeElement,
            this,
            &MainWindow::HideElementInfo);

    connect (&model,
            &Model::RequestUpdateProgress,
            this,
            &MainWindow::UpdateProgress);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DisplayElementInfo(){
    ui->elementInfo->show();
}

void MainWindow::HideElementInfo(){
    ui->elementInfo->hide();
}

void MainWindow::UpdateProgress(QString element){
    ui->progressBar->setValue(ui->progressBar->value() + 1);
    ui->menuElements->addAction(element);
}




