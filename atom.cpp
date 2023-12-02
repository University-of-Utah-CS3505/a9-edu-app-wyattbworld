#include "atom.h"

// All of the first 54 elements from Hydrogen to Xenon.
const std::vector<QString> Atom::NOTATIONLIST = {"H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne",
                                                        "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar",
                                                        "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr",
                                                        "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe"};

Atom::Atom(QObject *parent,
           int protonCount)
    : QObject{parent}
{
    logbase = std::exp(1.0);
    atomicNumber = protonCount;
    elementNotation = NOTATIONLIST[atomicNumber-1];
    radius = log2(atomicNumber)/log2(logbase);

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
