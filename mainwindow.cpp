#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(Model &model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->elementInfo->hide();//don't show any element cards before the game starts
    ui->progressBar->hide();
    ui->progressLabel->hide();
    ui->menu->hide();
    ui->gameOverLabel->setVisible(false);
    ui->tutorialButtonSide->setVisible(false);
    ui->tutorialView->setVisible(false);
    QImage startImage(":/Start/Start/start.jpeg");
    ui->startImage->setPixmap(QPixmap::fromImage(startImage));

    //setup the element search bar
    searchElements = new QLineEdit(this);
    searchElements->setPlaceholderText("Search For Elements");
    ui->menu->setCornerWidget(searchElements, Qt::TopLeftCorner);

    //make the progress bar have an ombre effect
    QString styleSheet =
        "QProgressBar {"
        "    border: 1px solid black;"
        "    border-radius: 5px;"
        "}"

        "QProgressBar::chunk {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #00FF9C, stop:1 #7E00FF);"
        "}";

    ui->progressBar->setStyleSheet(styleSheet);

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

    //when the GameView requests the status of an element, it will be sent by the model
    connect (ui->gameView,
            &GameView::RequestElementStatus,
            &model,
            &Model::SendElementStatus);

    //when the model requests to display an element's info card, the ElementInfo will set the information corresponding to the element
    connect (&model,
            &Model::RequestDisplayElementInfo,
            ui->elementInfo,
            &ElementInfo::SetElementInfo);

    //when ElementInfo requests to display an element's info card, the main window will display the card
    connect (ui->elementInfo,
            &ElementInfo::RequestDisplayElementInfo,
            this,
            &MainWindow::DisplayElementInfo);

    //when ElementInfo requests to close the element info card, the main window will hide the card
    connect (ui->elementInfo,
            &ElementInfo::closeElement,
            this,
            &MainWindow::HideElementInfo);

    //when the model requests to update the elements found progres, the main window will update the progress bar and menu
    connect (&model,
            &Model::RequestUpdateProgress,
            this,
            &MainWindow::UpdateProgress);

    //when the menu is about to be shown, each current "action" (element) in the menu will be connected to display info
    connect (ui->menuElements,
            &QMenu::aboutToShow,
            this,
            &MainWindow::ConnectElementActions);

    //when the main window requests to display an element's info card, ElementInfo will set the information corresponding to the element
    connect(this,
            &MainWindow::RequestDisplayElementInfo,
            ui->elementInfo,
            &ElementInfo::SetElementInfo);

    //when the user edits the element search bar, the existing elements in the menu which don't match the search will be "hidden"
    connect(searchElements,
            &QLineEdit::textEdited,
            this,
            &MainWindow::SearchForElement);

    //when the user presses enter, the matching search results will be displayed in the menu
    connect(searchElements,
            &QLineEdit::returnPressed,
            this,
            &MainWindow::DisplaySearchResults);

    connect(ui->startButton,
            &QPushButton::clicked,
            this,
            &MainWindow::DisplayMenuAndProgress);

    connect (ui->startButton,
            &QPushButton::clicked,
            this,
            &MainWindow::StartElementPreviews);

    connect (ui->gameView,
            &GameView::SendAtomPreview,
            this,
            &MainWindow::GetNextAtom);

    connect (&model,
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
            &Model::SetGameOverLabelVisibility,
            ui->gameOverLabel,
            &QLabel::setVisible);

    connect (&model,
            &Model::SetTutorialButtonVisibility,
            ui->tutorialButton,
            &QPushButton::setVisible);

    connect (&model,
            &Model::SetTutorialButtonSideVisibility,
            ui->tutorialButtonSide,
            &QPushButton::setVisible);

    connect (ui->tutorialButton,
            &QPushButton::clicked,
            &model,
            &Model::OpenTutorial);

    connect (ui->tutorialButtonSide,
            &QPushButton::clicked,
            &model,
            &Model::OpenTutorial);

    connect(&model,
            &Model::SetTutorialViewVisability,
            ui->tutorialView,
            &TutorialView::setVisible);

    connect(&model,
            &Model::SetGameViewVisibility,
            ui->gameView,
            &GameView::setVisible);

    connect(&model,
            &Model::SetAtomImagePreviewVisability,
            ui->AtomImagePreview,
            &QLabel::setVisible);

    connect(&model,
            &Model::SetNextElementIndicator,
            ui->NextElementIndicator,
            &QLabel::setVisible);


    ui->AtomImagePreview->hide();
    ui->NextElementIndicator->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::StartElementPreviews()
{
    ui->AtomImagePreview->show();
    ui->NextElementIndicator->show();
}

void MainWindow::GetNextAtom(Atom* nextAtom)
{
    QPixmap atomBody = QPixmap("://Elements//Elements/"+ nextAtom->elementNotation + ".png");
    QSize size(80, 80);
    atomBody = atomBody.scaled(size);
    ui->AtomImagePreview->setPixmap(atomBody);
}

void MainWindow::ConnectElementActions(){
    QMenu *menu = qobject_cast<QMenu*>(sender());
    //for each element in the menu, when clicked, the corresponding element card will be displayed
    for (QAction *action : menu->actions()) {
        connect(action, &QAction::triggered, this, &MainWindow::DisplayElementFromMenu);
    }
}

void MainWindow::DisplayElementInfo(){
    ui->elementInfo->show();
}

void MainWindow::DisplayElementFromMenu(){
    //get the desired element based on which menu "action" (element) was triggered
    QAction *action = qobject_cast<QAction*>(sender());
    QString element = action->text();
    //request to display the corresponding info card
    emit RequestDisplayElementInfo(element);
}

void MainWindow::HideElementInfo(){
    ui->elementInfo->hide();
}

void MainWindow::UpdateProgress(QString element, int numElementsFound){
    ui->progressBar->setValue(numElementsFound); //increment the progress bar
    ui->menuElements->addAction(element); //add the element to the menu of elements
}

void MainWindow::SearchForElement(const QString &text){
    //for any "search" (must click enter), if the text entered matches any elements in the menu, those elements will be in the search results
    for (QAction *action : ui->menuElements->actions()) {
        if (text.isEmpty() || action->text().startsWith(text, Qt::CaseInsensitive)) {
            action->setVisible(true);
        }
        else{
            action->setVisible(false);//all other elements will be "hidden"
        }
    }
}

void MainWindow::DisplaySearchResults(){
    //display the search results in the same position as the menu
    QPoint searchPos = searchElements->mapToGlobal(QPoint(searchElements->width(), searchElements->height()));
    ui->menuElements->exec(searchPos);
}

void MainWindow::DisplayMenuAndProgress(){
    ui->menu->show();
    ui->progressBar->show();
    ui->progressLabel->show();
    ui->startImage->hide();
}




