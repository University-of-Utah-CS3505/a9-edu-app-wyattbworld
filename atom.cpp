#include "atom.h"

Atom::Atom(QObject *parent,
           int protonCount,
           QString elementAbbv)
    : QObject{parent}
{
    atomicNumber = protonCount;
    elementNotation = elementAbbv;
    if (atomicNumber - 2 == 0 || (atomicNumber - 2) % 8 == 0)
    {
        isInert = true;
    }
    else if ((20 < atomicNumber && atomicNumber < 31) || (38 < atomicNumber && atomicNumber < 49))
    {
        isInert = true;
        isCatalyst = true;
    }
}
