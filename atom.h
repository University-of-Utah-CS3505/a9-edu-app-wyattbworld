#ifndef ATOM_H
#define ATOM_H

#include "qpixmap.h"
#include <QObject>
#include <QString>
#include <QImage>

/*
 * Wyatt Bruchhauser, Jackson Wetzel, Julia Thomas, Bodie Criswell, Nathaniel Pimentel, Brenlie Shirts
 * Reviewer: Jackson Wetzel
 * CS3505
 * Assignment 9: Education App
 * File Description: The Atom class serves to contain all logistical information about an Atom.
 * The Atom object is then bound to a specific physical body elsewhere in the program, appearing differently based on its size.
 */
class Atom : public QObject
{
    Q_OBJECT

public:
    explicit Atom (QObject *parent = nullptr,
                  int protonCount = 1);
    bool isInert;                       // Defines whether this atom reacts with others.
    bool isCatalyst;                    // Defines whether this atom can catalyze.
    ///
    /// \brief Split divides this Atom in two, halving its proton count and spawning an identical Atom.
    ///
    void Split ();
    // The list of all elements being used in the game.
    static const std::vector<QString> NOTATIONLIST;
    int atomicNumber;                   // The number of protons in this Atom.
    QString elementNotation;            // This Atom's chemical notation.
    float radius;                       // The Atom's relative size.
    QPixmap atomBody;                   // The image containing this Atom's atomic number and notation.


private:

signals:
    ///
    /// \brief SpawnOtherHalf request to spawn the other half of this Atom when it is split by a catalyst.
    /// \param protonCount  The other half of the protons.
    ///
    void SpawnOtherHalf (int protonCount);

public slots:
    ///
    /// \brief FuseElements combines two Atoms upon collision.
    /// \param otherProtonCount The amount of protons to be added to this atom.
    ///
    void FuseElements (int otherProtonCount);
    ///
    /// \brief Catalyze is only called if this Atom is a catalyst. It splits the Atom it collided with.
    /// \param otherAtom The Atom to be split.
    ///
    void Catalyze (Atom& otherAtom);

};

#endif // ATOM_H
