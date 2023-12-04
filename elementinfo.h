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

    void setTitleContent(const QString &text);
    void setAssetContent(const QString &text);
    void setImageContent(const QString &text);
    void setKeyProperties(const QString &text);

private:
    Ui::ElementInfo *ui;
    QMap<QString, QList<QString>> elementDescriptions;
};

#endif // ELEMENTINFO_H
