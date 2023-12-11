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
    ///
    /// \brief DisplayElementInfo Displays the element information card
    ///
    void DisplayElementInfo();

    ///
    /// \brief HideElementInfo Hides the currenlty displayed element information card
    ///
    void HideElementInfo();

    ///
    /// \brief UpdateProgress Updates the progress bar and element menu
    /// \param element The desired element abbreviation
    /// \param numElementsFound The current number of elements that have been discovered
    ///
    void UpdateProgress(QString element, int numElementsFound);

    ///
    /// \brief DisplayElementFromMenu Determines which menu "action" (element) was clicked and requests to display it
    ///
    void DisplayElementFromMenu();

    ///
    /// \brief ConnectElementActions Connects each menu "action" (element) to display their element info card when clicked.
    ///
    void ConnectElementActions();

    ///
    /// \brief SearchForElement Sets all elements on the menu that don't match the search text to be hidden.
    /// \param text The search query
    ///
    void SearchForElement(const QString &text);

    ///
    /// \brief DisplaySearchResults Displays the results of an element search in the menu.
    ///
    void DisplaySearchResults();

    void DisplayMenuAndProgress();

    void StartElementPreviews();
    void GetNextAtom(Atom* nextAtom);
signals:
    ///
    /// \brief RequestDisplayElementInfo Signals that we need to display a new element's information
    /// \param element The desired element abbreviation
    ///
    void RequestDisplayElementInfo(QString element);
};
#endif // MAINWINDOW_H
