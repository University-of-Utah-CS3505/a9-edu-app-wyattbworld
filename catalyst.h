#ifndef CATALYST_H
#define CATALYST_H

#include <QObject>

class Catalyst : public QObject
{
    Q_OBJECT
public:
    explicit Catalyst (QObject *parent = nullptr);
};

#endif // CATALYST_H
