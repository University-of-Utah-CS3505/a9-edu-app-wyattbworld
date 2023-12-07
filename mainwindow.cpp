#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(Model &model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->elementInfo->hide();

    searchElements = new QLineEdit(this);
    searchElements->setPlaceholderText("Search For Elements");
    ui->menu->setCornerWidget(searchElements, Qt::TopLeftCorner);

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

    connect (ui->menuElements,
            &QMenu::aboutToShow,
            this,
            &MainWindow::ConnectElementActions);

    connect(this,
            &MainWindow::RequestDisplayElementInfo,
            ui->elementInfo,
            &ElementInfo::SetElementInfo);

    connect(searchElements,
            &QLineEdit::textEdited,
            this,
            &MainWindow::SearchForElement);

    connect(searchElements,
            &QLineEdit::returnPressed,
            this,
            &MainWindow::DisplaySearchResults);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConnectElementActions(){
    // Disconnect existing connections to avoid duplicates
    QMenu *menu = qobject_cast<QMenu*>(sender());
    //QObject::disconnect(sender(), nullptr, nullptr, nullptr);

    for (QAction *action : menu->actions()) {
        connect(action, &QAction::triggered, this, &MainWindow::DisplayElementFromMenu);
    }
}

void MainWindow::DisplayElementInfo(){
    ui->elementInfo->show();
}

void MainWindow::DisplayElementFromMenu(){
    QAction *action = qobject_cast<QAction*>(sender());
    QString element = action->text();
    emit RequestDisplayElementInfo(element);
}

void MainWindow::HideElementInfo(){
    ui->elementInfo->hide();
}

void MainWindow::UpdateProgress(QString element){
    ui->progressBar->setValue(ui->progressBar->value() + 1);
    ui->menuElements->addAction(element);
}

void MainWindow::SearchForElement(const QString &text){
    for (QAction *action : ui->menuElements->actions()) {
        if (text.isEmpty() || action->text().startsWith(text, Qt::CaseInsensitive)) {
            action->setVisible(true);
        }
        else{
            action->setVisible(false);
        }
    }
}

void MainWindow::DisplaySearchResults(){
    QPoint searchPos = searchElements->mapToGlobal(QPoint(searchElements->width(), searchElements->height()));
    ui->menuElements->exec(searchPos);
}




