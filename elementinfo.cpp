#include "elementinfo.h"
#include "ui_elementinfo.h"

//note this is not model-view yet, just trying to get it somewhat set up
ElementInfo::ElementInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ElementInfo)
{
    ui->setupUi(this);

    QString styleSheet = QString("background-color: white");
    ui->frame->setStyleSheet(styleSheet);

    elementDescriptions["01Hydrogen"] = {"Atomic number : 1 \nGroup : S-block \nPhase @ STP : Gas" , "Hydrogen comprises more than 90% of the atoms in the universe and was first recognized as a distinct substance in 1776. On earth, it is most commonly found combined with oxygen as water, and is also present in living plants, petroleum, coal, and other organic matter."};
    elementDescriptions["02Helium"] = {"Atomic number : 2 \nGroup : Noble Gas \nPhase @ STP : Gas" , "The first evidence of helium was detected during the solar eclipse of 1868. It is the second most abundant element and can be extracted from natural gas. The majority of helium in the U.S. is obtained from wells in Texas, Oklahoma, and Kansas."};
    elementDescriptions["03Lithium"] = {"Atomic number : 3 \nGroup: S-block \nPhase @ STP : Solid", "Discovered in 1817, lithium is the lightest of all metals. It does not occur freely in nature and is found (combined) in all igneous rocks, mineral springs, and the minerals lepidolite, spodumene, petalite, and amblygonite."};
    elementDescriptions["04Berylium"] = {"Atomic number : 4 \nGroup: S-block \nPhase @ STP : Solid","Beryllium was discovered as an oxide in both beryl and emeralds in 1798. Beryllium is found in bertrandite, beryl, chrysoberyl, phenacite, and many other minerals."};
}

ElementInfo::~ElementInfo()
{
    delete ui;
}

///
/// \brief ElementInfo::setTitleContent Sets the title of the element.
/// \param element Text representing the element, the atomic number followed by name (ex: "01Hydrogen")
///
void ElementInfo::setTitleContent(const QString &element)
{
    ui->elementName->setText(element.mid(2).toUpper());//displays the elements sans number
}

///
/// \brief ElementInfo::setAssetContent Sets the "asset" image of the element.
/// \param element Text representing the element, the atomic number followed by name (ex: "01Hydrogen")
///
void ElementInfo::setAssetContent(const QString &element)
{
    QImage assetImage(":/new/prefix1/images/"+element+".png");
    if (assetImage.isNull()) {
        qDebug() << "Failed to load the original image.";
    }

   // make the image the same size as the label
    QSize size(ui->elementAsset->width(), ui->elementAsset->height());
    QImage resizedImage = assetImage.scaled(size, Qt::KeepAspectRatio);
    //display the image on the label
    ui->elementAsset->setPixmap(QPixmap::fromImage(resizedImage));
}

///
/// \brief ElementInfo::setImageContent Sets the image representing the element.
/// \param element Text representing the element, the atomic number followed by name (ex: "01Hydrogen")
///
void ElementInfo::setImageContent(const QString &element)
{

    QImage image(":new/prefix1/images/"+element+"Image.jpg");

    //make the image the same size as the label
    QSize size(ui->elementImage->width(), ui->elementImage->height());
    QImage resizedImage = image.scaled(size, Qt::KeepAspectRatio);
    //display the image on the label
    ui->elementImage->setPixmap(QPixmap::fromImage(resizedImage));

}

void ElementInfo::setKeyProperties(const QString &element)
{
    ui->keyProperties->setText(elementDescriptions[element][0]);
    ui->uses->setText(elementDescriptions[element][1]);
}
