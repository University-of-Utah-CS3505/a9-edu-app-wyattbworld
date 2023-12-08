/*
Wyatt Bruchhauser, Jackson Wetzel, Julia Thomas, Bodie Criswell, Nathaniel Pimentel, Brenlie Shirts
CS 3505
Assignment 9 : Educational App
File Description: This file defines the element description cards/visuals.
*/

#ifndef ELEMENTINFO_H
#define ELEMENTINFO_H

#include <QWidget>
#include <QPixmap>
#include <QImage>
#include <QDebug>

namespace Ui {
class ElementInfo;
}

///
////// \brief The ElementInfo class is a custom form class which represents a widget which will display basic information and images for each element in the game.
///
class ElementInfo : public QWidget
{
    Q_OBJECT

public:

    //constructor and destructor
    explicit ElementInfo(QWidget *parent = nullptr);
    ~ElementInfo();

    ///
    /// \brief SetAssetContent Sets the appropriate atom image based on the desired element.
    /// \param element The desired element abbreviation
    ///
    void SetAssetContent(const QString &element);

    ///
    /// \brief SetImageContent Sets the appropriate representative image based on the desired element.
    /// \param element The desired element abbreviation
    ///
    void SetImageContent(const QString &element);

    ///
    /// \brief SetKeyProperties Sets the name, basic properties, and short fact about the desired element.
    /// \param element The desired element abbreviation.
    ///
    void SetKeyProperties(const QString &element);

private:
    Ui::ElementInfo *ui;
    QMap<QString, QList<QString>> elementDescriptions; //A map which stores the element abbreviations as keys and the list of key properties for that element as values.

public slots:
    ///
    /// \brief SetElementInfo Sets all appropriate information (atom image, element image, key properties), and emits a signal to display said information.
    /// \param element The desired element abbreviation.
    ///
    void SetElementInfo(QString element);

    ///
    /// \brief ExitElement Emits the closeElement signal.
    ///
    void ExitElement();

signals:
    ///
    /// \brief RequestDisplayElementInfo Signals to display the element information card.
    ///
    void RequestDisplayElementInfo();

    ///
    /// \brief closeElement Signals to close the element information card.
    ///
    void closeElement();
};

#endif // ELEMENTINFO_H
