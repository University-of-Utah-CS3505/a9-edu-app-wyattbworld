#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"
#include <QDebug>
#include <QLineEdit>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Model &model, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLineEdit *searchElements;

public slots:
    void DisplayElementInfo();
    void HideElementInfo();
    void UpdateProgress(QString element);
    void DisplayElementFromMenu();
    void ConnectElementActions();
    void SearchForElement(const QString &text);
    void DisplaySearchResults();
signals:
    void RequestDisplayElementInfo(QString element);
};
#endif // MAINWINDOW_H
