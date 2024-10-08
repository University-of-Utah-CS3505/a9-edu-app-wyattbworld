#include "atom.h"
#include "qpixmap.h"
/*
 * Wyatt Bruchhauser, Jackson Wetzel, Julia Thomas, Bodie Criswell, Nathaniel Pimentel, Brenlie Shirts
 * Reviewer: Jackson Wetzel
 * CS3505
 * Assignment 9: Education App
 * File Description: The Atom class serves to contain all logistical information about an Atom.
 * The Atom object is then bound to a specific physical body elsewhere in the program, appearing differently based on its size.
 */

// All of the first 54 elements from Hydrogen to Xenon.
const std::vector<QString> Atom::NOTATIONLIST = {"H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne",
                                                 "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar",
                                                 "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr",
                                                 "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe"};

Atom::Atom(QObject *parent,
           int protonCount)
    : QObject{parent}
{
    // Initialize all necessary attributes
    atomicNumber = protonCount;
    elementNotation = NOTATIONLIST[atomicNumber-1];
    radius = atomicNumber*3;

    // Elements with protons in multiples of 8 plus 2 are inert and do not combine with other atoms.
    if (atomicNumber - 2 == 0 || (atomicNumber - 2) % 8 == 0)
    {
        isInert = true;
    }
    // Transition metals are catalysts, which are also inert but also split atoms they collide with.
    else if ((20 < atomicNumber && atomicNumber < 31) || (38 < atomicNumber && atomicNumber < 49))
    {
        isInert = true;
        isCatalyst = true;
    }
    // Assign this Atom's associated image and scale it to the size of the physical body.
    atomBody = QPixmap("://Elements//Elements/"+ elementNotation + ".png");
    QSize size(radius*2, radius*2);
    atomBody = atomBody.scaled(size);
}

void Atom::Split()
{
    // Cut the atomic number in half and spawn the other half
    atomicNumber /= 2;
    elementNotation = NOTATIONLIST[atomicNumber-1];
    emit SpawnOtherHalf(atomicNumber);
}

void Atom::FuseElements(int otherProtonCount)
{
    // Combine this Atom with the other one
    atomicNumber += otherProtonCount;
    elementNotation = NOTATIONLIST[atomicNumber-1];
}

void Atom::Catalyze(Atom &otherAtom)
{
    // Split the colliding atom.
    otherAtom.Split();
}
