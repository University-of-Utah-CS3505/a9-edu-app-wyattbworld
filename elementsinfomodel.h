#ifndef ELEMENTSINFOMODEL_H
#define ELEMENTSINFOMODEL_H

#include <QObject>

class ElementsInfoModel : public QObject
{
    Q_OBJECT
public:
    explicit ElementsInfoModel(QObject *parent = nullptr);

signals:

private:
//     QMap<QString, QList<QString>> elementDescriptions;
};

#endif // ELEMENTSINFOMODEL_H
