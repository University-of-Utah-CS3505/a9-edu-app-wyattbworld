#ifndef TUTORIALVIEW_H
#define TUTORIALVIEW_H

#include <QWidget>

namespace Ui {
class TutorialView;
}

class TutorialView : public QWidget
{
    Q_OBJECT

public:
    explicit TutorialView(QWidget *parent = nullptr);
    ~TutorialView();

private:
    Ui::TutorialView *ui;
};

#endif // TUTORIALVIEW_H
