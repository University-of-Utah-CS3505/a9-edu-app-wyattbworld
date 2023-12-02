#ifndef ATOM_H
#define ATOM_H

#include <QObject>
#include <QString>
#include <vector>
#include <math.h>

class Atom : public QObject
{
    Q_OBJECT

public:
    explicit Atom (QObject *parent = nullptr,
                  int protonCount = 1);
    Atom& operator= (Atom other);       // Assignment overload
    bool isInert;                       // Defines whether this atom reacts with others.
    bool isCatalyst;                    // Defines whether this atom can catalyze.
    ///
    /// \brief Split divides this Atom in two, halving its proton count and spawning an identical Atom.
    ///
    void Split ();
    ///
    /// \brief CopyAtom creates a copy of this Atom object.
    /// \return The copy of this Atom.
    ///
    Atom* CopyAtom ();
    static const std::vector<QString> NOTATIONLIST; // The list of all elements being used in the game.
    int atomicNumber;                   // The number of protons in this Atom.
    QString elementNotation;            // This Atom's chemical notation.
    float radius;


private:
    const int logbase = std::exp(1.0);

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
