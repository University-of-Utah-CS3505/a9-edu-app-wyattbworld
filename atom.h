#ifndef ATOM_H
#define ATOM_H

#include <QObject>
#include <QString>
#include <vector>

class Atom : public QObject
{
    Q_OBJECT

public:
    explicit Atom(QObject *parent = nullptr,
                  int protonCount = 1,
                  QString elementAbbv = "H");
    bool isInert;
    bool isCatalyst;
    void Split();
    Atom CopyAtom();
private:
    const std::vector<QString> NOTATIONLIST = {"H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne",
                                               "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar",
                                               "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr",
                                               "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe"};
    int atomicNumber;
    QString elementNotation;

signals:
    void SpawnOtherHalf(int protonCount);

public slots:
    void FuseElements(int otherProtonCount);
    void Catalyze(Atom otherAtom);

};

#endif // ATOM_H
