#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(Model &model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->elementInfo->hide();
    ui->gameOverLabel->setVisible(false);

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

    connect (ui->gameView,
           &GameView::ChangeElementStatus,
           &model,
           &Model::UpdateElementStatus);

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

    connect(&model,
            &Model::SetStartButtonVisibility,
            ui->startButton,
            &QPushButton::setVisible);

    connect (ui->quitButton,
            &QPushButton::clicked,
            &model,
            &Model::QuitGame);

    connect (&model,
            &Model::SetQuitButtonVisibility,
            ui->quitButton,
            &QPushButton::setVisible);

    connect (&model,
            &Model::SetGameViewVisibility,
            ui->gameView,
            &GameView::setVisible);

    connect (&model,
            &Model::SetGameOverLabelVisibility,
            ui->gameOverLabel,
            &QLabel::setVisible);

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




