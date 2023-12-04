#ifndef ELEMENTINFO_H
#define ELEMENTINFO_H

#include <QWidget>
#include <QPixmap>
#include <QImage>

namespace Ui {
class ElementInfo;
}

class ElementInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ElementInfo(QWidget *parent = nullptr);
    ~ElementInfo();

    void SetAssetContent(const QString &text);
    void SetImageContent(const QString &text);
    void SetKeyProperties(const QString &text);

private:
    Ui::ElementInfo *ui;
    QMap<QString, QList<QString>> elementDescriptions;

public slots:
    void SetElementInfo(QString element);
    void ExitElement();
signals:
    void RequestDisplayElementInfo();
    void closeElement();
};

#endif // ELEMENTINFO_H
