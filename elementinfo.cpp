#include "elementinfo.h"
#include "ui_elementinfo.h"

//note this is not model-view yet, just trying to get it somewhat set up
ElementInfo::ElementInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ElementInfo)
{
    ui->setupUi(this);

    //make the background of the popup white
    QString styleSheet = QString("background-color: white");
    ui->frame->setStyleSheet(styleSheet);

    elementDescriptions["H"] = {"Hydrogen (H)", "Atomic number : 1 \nGroup : S-block \nPhase @ STP : Gas" , "Hydrogen comprises more than 90% of the atoms in the universe and was first recognized as a distinct substance in 1776. On earth, it is most commonly found combined with oxygen as water, and is also present in living plants, petroleum, coal, and other organic matter."};
    elementDescriptions["He"] = {"Helium (He)","Atomic number : 2 \nGroup : Noble Gas \nPhase @ STP : Gas" , "The first evidence of helium was detected during the solar eclipse of 1868. It is the second most abundant element and can be extracted from natural gas. The majority of helium in the U.S. is obtained from wells in Texas, Oklahoma, and Kansas."};
    elementDescriptions["Li"] = {"Lithium (Li)", "Atomic number : 3 \nGroup: S-block \nPhase @ STP : Solid", "Discovered in 1817, lithium is the lightest of all metals. It does not occur freely in nature and is found (combined) in all igneous rocks, mineral springs, and the minerals lepidolite, spodumene, petalite, and amblygonite."};
    elementDescriptions["Be"] = {"Beryllium (Be)", "Atomic number : 4 \nGroup: S-block \nPhase @ STP : Solid","Beryllium was discovered as an oxide in both beryl and emeralds in 1798. Beryllium is found in bertrandite, beryl, chrysoberyl, phenacite, and many other minerals."};

    connect(ui->exitButton,
            &QPushButton::clicked,
            this,
            &ElementInfo::ExitElement);
}

ElementInfo::~ElementInfo()
{
    delete ui;
}

void ElementInfo::SetElementInfo(QString element){
    SetAssetContent(element);
    SetImageContent(element);
    SetKeyProperties(element);
    emit RequestDisplayElementInfo();
}

void ElementInfo::ExitElement(){
    emit closeElement();
}


///
/// \brief ElementInfo::setAssetContent Sets the "asset" image of the element.
/// \param element Text representing the element, the atomic number followed by name (ex: "01Hydrogen")
///
void ElementInfo::SetAssetContent(const QString &element)
{
    QImage assetImage(":/Elements/Elements/"+element+".png");
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
void ElementInfo::SetImageContent(const QString &element)
{

    QImage image(":/elements/images/"+element+"Image.jpg");
    //make the image the same size as the label
    QSize size(ui->elementImage->width(), ui->elementImage->height());
    QImage resizedImage = image.scaled(size, Qt::KeepAspectRatio);
    //display the image on the label
    ui->elementImage->setPixmap(QPixmap::fromImage(resizedImage));

}

void ElementInfo::SetKeyProperties(const QString &element)
{
    ui->elementName->setText(elementDescriptions[element][0]);
    ui->keyProperties->setText(elementDescriptions[element][1]);
    ui->uses->setText(elementDescriptions[element][2]);
}
