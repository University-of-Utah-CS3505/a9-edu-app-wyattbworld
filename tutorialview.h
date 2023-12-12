#ifndef TUTORIALVIEW_H
#define TUTORIALVIEW_H

#include <QWidget>

namespace Ui {
class TutorialView;
}

/*
Wyatt Bruchhauser, Jackson Wetzel, Julia Thomas, Bodie Criswell, Nathaniel Pimentel, Brenlie Shirts
Reviewer: Julia Thomas
CS 3505
Assignment 9: Education App
This class represents the window that comes up when the tutorial button is pressed. Displays information on how to play the game
*/
class TutorialView : public QWidget
{
    Q_OBJECT

public:
    explicit TutorialView(QWidget *parent = nullptr);
    ~TutorialView();

private:
    ///
    /// \brief paintEvent Draws the tutorial view on the screen
    void paintEvent(QPaintEvent *);

private slots:
    ///
    /// \brief OnExitButtonClicked Quit the window
    void OnExitButtonClicked();

private:
    Ui::TutorialView *ui;
};

#endif // TUTORIALVIEW_H
