/*
Wyatt Bruchhauser, Jackson Wetzel, Julia Thomas, Bodie Criswell, Nathaniel Pimentel, Brenlie Shirts
CS 3505
Assignment 9 : Educational App
File Description: This file implements the element description cards/visuals.
*/

#include "elementinfo.h"
#include "ui_elementinfo.h"

ElementInfo::ElementInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ElementInfo)
{
    ui->setupUi(this);

    //fill the background of the card to be white
    QString styleSheet = QString("background-color: white");
    ui->frame->setStyleSheet(styleSheet);

    //store all of the needed information for each element in the map of element information
    //each element corresponds to a list of properties which include full name, atomic number, group, phase at standard temperature and pressure, and an interesting fact/use of the element.
    elementDescriptions["H"] = {"Hydrogen (H)", "Atomic number : 1 \nGroup : S-block \nPhase @ STP : Gas" , "Hydrogen comprises more than 90% of the atoms in the universe and was first recognized as a distinct substance in 1776. On earth, it is most commonly found combined with oxygen as water, and is also present in living plants, petroleum, coal, and other organic matter."};
    elementDescriptions["He"] = {"Helium (He)","Atomic number : 2 \nGroup : Noble Gas \nPhase @ STP : Gas" , "The first evidence of helium was detected during the solar eclipse of 1868. It is the second most abundant element and can be extracted from natural gas. The majority of helium in the U.S. is obtained from wells in Texas, Oklahoma, and Kansas."};
    elementDescriptions["Li"] = {"Lithium (Li)", "Atomic number : 3 \nGroup: S-block \nPhase @ STP : Solid", "Discovered in 1817, lithium is the lightest of all metals. It does not occur freely in nature and is found (combined) in all igneous rocks, mineral springs, and the minerals lepidolite, spodumene, petalite, and amblygonite."};
    elementDescriptions["Be"] = {"Beryllium (Be)", "Atomic number : 4 \nGroup: S-block \nPhase @ STP : Solid","Beryllium was discovered as an oxide in both beryl and emeralds in 1798. Beryllium is found in bertrandite, beryl, chrysoberyl, phenacite, and many other minerals."};
    elementDescriptions["B"] = {"Boron (B)", "Atomic number : 5 \nGroup: P-block \nPhase @ STP : Solid", "Boron compounds have been known for thousands of years, but the element was not discovered until 1808. It is not found free in nature, but as orthoboric acid in volcanic spring waters and as borates. Important sources are the ores rasorite (kernite) and tincal (borax ore)."};
    elementDescriptions["C"] = {"Carbon (C)", "Atomic number : 6 \nGroup : P-block \nPhase @ STP : Solid" , "Carbon was discovered prehistorically. It is widely distributed in nature and is found in the stars, comets, and the atmospheres of most planets."};
    elementDescriptions["N"] = {"Nitrogen (N)","Atomic number : 7 \nGroup : P-block \nPhase @ STP : Gas" , "Nitrogen was discovered in 1772 and is found in the biological materials of all living systems."};
    elementDescriptions["O"] = {"Oxygen (O)", "Atomic number : 8 \nGroup: P-block \nPhase @ STP : Gas", "Joseph Priestley is generally credited with the discovery of oxygen. Its gas is colorless, odorless, and tasteless. The liquid and solid forms are a pale blue color and are strongly paramagnetic."};
    elementDescriptions["F"] = {"Flourine (F)", "Atomic number : 9 \nGroup: P-block \nPhase @ STP : Gas","The use of fluorspar as a flux was described in 1529, but fluorine was not isolated until 1866. It is the most electronegative and reactive of all elements."};
    elementDescriptions["Ne"] = {"Neon (Ne)", "Atomic number : 10 \nGroup: Noble Gas \nPhase @ STP : Gas", "Discovered in 1898, neon is a rare, gaseous element. In its natural form, it is a mixture of three isotopes. Six other less-stable isotopes have been identified."};
    elementDescriptions["Na"] = {"Sodium (Na)", "Atomic number : 11  \nGroup: S-Block \nPhase @STP : Solid", "Although recognized in compounds, sodium was first isolated in 1807. Sodium is fairly abundant in the sun and stars, the fourth most abundant element on Earth, and the most commonly found alkali metal."};
    elementDescriptions["Mg"] = {"Magnesium (Mg)", "Atomic number : 12  \nGroup: S-Block \nPhase @STP : Solid", "Magnesium was recognized in 1755 and first isolated in 1808. It is the eighth most abundant element in the Earth's crust and is found mainly in magnesite, dolomite, and other minerals."};
    elementDescriptions["Al"] = {"Aluminum (Al)", "Atomic number : 13 \nGroup: P-Block  \nPhase @STP : Solid", "Used originally as an astringent and a dyeing mordant, aluminum was first isolated in 1827. Originally called aluminium, the American Chemical Society adopted the name aluminum in 1925."};
    elementDescriptions["Si"] = {"Silicon (Si)", "Atomic number : 14 \nGroup: P-Block \nPhase @STP : Solid", "Impure amorphous silicon was prepared in 1811 and purified in 1824. Crystalline silicon, the second allotropic form of the element, was first prepared in 1854."};
    elementDescriptions["P"] = {"Phosphorus (P)", "Atomic number : 15  \nGroup: P-Block \nPhase @STP : Solid", "Phosphorus was discovered in 1669 and exists in four or more allotropic forms, including white (or yellow), red, and black (or violet). Phosphorus is a waxy white solid and is colorless and transparent when pure."};
    elementDescriptions["S"] = {"Sulfur (S)", "Atomic number : 16  \nGroup: P-Block \nPhase @STP : Solid", "Sulfur is essential to life and a minor constituent of fats, body fluids, and skeletal minerals. It is an odorless, pale yellow and brittle solid, insoluble in water but soluble in carbon disulfide. It can be found in multiple forms: gas, liquid, or solid."};
    elementDescriptions["Cl"] = {"Chlorine (Cl)", "Atomic number : 17 \nGroup: P-Block \nPhase @STP : Gas", "Discovered in 1774, chlorine was clearly identified as an element and named in 1810. Chlorine is a member of the halogen or salt-forming group of elements."};
    elementDescriptions["Ar"] = {"Argon (Ar)", "Atomic number : 18  \nGroup: Noble Gas \nPhase @STP : Gas", "The presence of argon was suspected as early as 1785, and it was officially discovered in 1894. In both gaseous and liquid forms, argon is colorless and odorless."};
    elementDescriptions["K"] = {"Potassium (K)", "Atomic number : 19  \nGroup: S-Block \nPhase @STP : Solid", "Discovered in 1807, potassium is the seventh most abundant metal. Potassium is not found free in nature, and most minerals that contain it are insoluble, making it difficult to obtain."};
    elementDescriptions["Ca"] = {"Calcium (Ca)", "Atomic number : 20  \nGroup: S-Block \nPhase @STP : Solid", "Elemental calcium was discovered in 1808. This alkaline earth metal is the fifth most abundant in the Earth's crust and found in leaves, bones, teeth, and shells."};
    elementDescriptions["Sc"] = {"Scandium (Sc)", "Atomic number : 21  \nGroup: Catalyst \nPhase @STP : Solid", "Scandium was discovered in 1878 in the minerals euxenite and gadolinite. Minute amounts occur in over 800 minerals, and scandium is much more abundant in the sun and certain stars than on Earth."};
    elementDescriptions["Ti"] = {"Titanium (Ti)", "Atomic number : 22  \nGroup: Catalyst \nPhase @STP : Solid", "Discovered in 1791 and named in 1795, pure titanium metal was not made until 1910. It is a lustrous white metal with low density, good strength, and excellent corrosion resistance. Ductile only when free of oxygen, it burns in air and is the only element that burns in nitrogen."};
    elementDescriptions["V"] = {"Vanadium (V)", "Atomic number : 23  \nGroup: Catalyst \nPhase @STP : Solid", "Vanadium was first discovered in 1801 but was misidentified and rediscovered in 1830. Natural vanadium is a mixture of two isotopes. Nine other unstable isotopes exist."};
    elementDescriptions["Cr"] = {"Chromium (Cr)", "Atomic number  24:  \nGroup: Catalyst \nPhase @STP : Solid", "Chromium is a hard, lustrous steel-gray metal that was discovered in 1797. Found primarily in chromite ore, it is usually produced by reducing the oxide with aluminum."};
    elementDescriptions["Mn"] = {"Manganese (Mn)", "Atomic number : 25  \nGroup: Catalyst \nPhase @STP : Solid", "solated in 1774, manganese is gray-white, harder than iron, and very brittle. It is reactive chemically and used to form important ferromagnetic and other alloys. Manganese improves the handling of steel, adding strength, stiffness, wear resistance, and hardness."};
    elementDescriptions["Fe"] = {"Iron (Fe)", "Atomic number : 26  \nGroup: Catalyst \nPhase @STP : Solid", "Iron is a relatively abundant metal found in the sun and other stars and in meteorites. It is the fourth most abundant element in the earth’s crust by weight."};
    elementDescriptions["Co"] = {"Cobalt (Co)", "Atomic number : 27 \nGroup: Catalyst \nPhase @STP : Solid", "Cobalt was discovered in 1735. It occurs in cobaltite, smaltite, erythrite, and other minerals and is a by-product of processing nickel, silver, lead, copper, and iron ores."};
    elementDescriptions["Ni"] = {"Nickel (Ni)", "Atomic number : 28  \nGroup: Catalyst \nPhase @STP : Solid", "Discovered in 1751, nickel is found in meteorites and can be used to distinguish meteorites from other minerals. Five stable isotopes comprise natural nickel and nine unstable isotopes exist."};
    elementDescriptions["Cu"] = {"Copper (Cu)", "Atomic number : 29  \nGroup: Catalyst \nPhase @STP : Solid", "Copper has been mined for 5,000 years. It is a reddish metal that takes on a bright luster. Malleable and ductile, it is a good conductor of heat and electricity."};
    elementDescriptions["Zn"] = {"Zinc (Zn)", "Atomic number : 30  \nGroup: Catalyst \nPhase @STP : Solid", "Before zinc was identified as an element, it was used to make brass. The metal was rediscovered in Europe in 1746."};
    elementDescriptions["Ga"] = {"Gallium (Ga)", "Atomic number : 31  \nGroup: P-Block \nPhase @STP : Solid", "Mendeleev predicted the existence of gallium (described as ekaaluminum), and it was discovered in 1875. Gallium is usually found in diaspore, sphalerite, germanite, bauxite, and coal."};
    elementDescriptions["Ge"] = {"Germainium (Ge)", "Atomic number : 32  \nGroup: P-Block \nPhase @STP : Solid", "The existence of germanium was predicted by Mendeleev (who called it ekasilicon). It was discovered in 1886. In its pure state, this metalloid is grayish-white, crystalline, and brittle. It is found in argyrodite (a sulfide of germanium and silver), germanite, zinc ores, coal, and other minerals."};
    elementDescriptions["As"] = {"Arsenic (As)", "Atomic number : 33 \nGroup: P-Block \nPhase @STP : Solid", "Arsenic may have first been obtained in 1250 A.D., but preparation instructions were not published until 1649."};
    elementDescriptions["Se"] = {"Selenium (Se)", "Atomic number : 34  \nGroup: P-Block \nPhase @STP : Solid", "Discovered in 1817, selenium exists in several allotropic forms and with amorphous or crystalline structures. As a member of the sulfur family, it resembles sulfur in form and in its compounds."};
    elementDescriptions["Br"] = {"Bromine (Br)", "Atomic number : 35  \nGroup: P-Block \nPhase @STP : Liquid", "Bromine is a nonmetallic liquid element. It is a heavy, reddish-brown liquid that produces a red vapor with a distinct and unpleasant odor. The vapor irritates the eyes and throat, and skin exposure results in painful sores."};
    elementDescriptions["Kr"] = {"Krypton (Kr)", "Atomic number : 36  \nGroup: Noble Gas  \nPhase @STP : Gas", "Discovered in 1898, krypton’s spectrum became the international standard for the length of the meter from 1960 to 1983."};
    elementDescriptions["Rb"] = {"Rubidium (Rb)", "Atomic number : 37  \nGroup: S-Block \nPhase @STP : Solid", "Discovered in 1861, rubidium was first found by spectroscopy in the mineral lepidolite. The element is more abundant than originally believed; it also occurs in pollucite, leucite, zinnwaldite, and other minerals."};
    elementDescriptions["Sr"] = {"Strontium (Sr)", "Atomic number : 38  \nGroup: S-Block \nPhase @STP : Solid", "Named after a town in Scotland and isolated in 1808, strontium was recognized in 1790."};
    elementDescriptions["Y"] = {"Yttrium (Y)", "Atomic number : 39  \nGroup: Catalyst \nPhase @STP : Solid", "Yttrium was discovered in 1794 and is found in nearly all of the rare-earth minerals. Relatively stable in air, yttrium has a silver-metallic luster. However, fine pieces of the metal will ignite in air at temperatures greater than 400°C."};
    elementDescriptions["Zr"] = {"Zirconium (Zr)", "Atomic number : 40  \nGroup: Catalyst \nPhase @STP : Solid", "Although the gemstone zircon was known earlier, zirconium was identified as a new element in 1789."};
    elementDescriptions["Nb"] = {"Niobium (Nb)", "Atomic number : 41  \nGroup: Catalyst \nPhase @STP : Solid", "Discovered in 1801 in an ore, the name niobium officially replaced the name “columbium” in 1950 after 100 years of controversy. Niobium is a soft, shiny white, ductile metal that becomes bluish with long exposure to air. Eighteen isotopes of niobium are known."};
    elementDescriptions["Mo"] = {"Molybdenum (Mo)", "Atomic number : 42  \nGroup: Catalyst \nPhase @STP : Solid", "Recognized as a new element in 1778, the first impure form of molybdenum was produced in 1782."};
    elementDescriptions["Tc"] = {"Technetium (Tc)", "Atomic number : 43  \nGroup: Catalyst \nPhase @STP : Solid", "The existence of element 43 was first predicted by the periodic table. Technetium was not discovered until 1937 and was the first element to be artificially produced."};
    elementDescriptions["Ru"] = {"Ruthenium (Ru)", "Atomic number : 44  \nGroup: Catalyst \nPhase @STP : Solid", "Discovered in 1844, ruthenium is a member of the platinum group and occurs naturally where other group members are found."};
    elementDescriptions["Rh"] = {"Rhodium (Rh)", "Atomic number : 45  \nGroup: Catalyst \nPhase @STP : Solid", "It is silvery white, slowly changes to the sesquioxide when heated in air, and converts back to the element at higher temperatures. It is highly reflective, hard, and durable."};
    elementDescriptions["Pd"] = {"Palladium (Pd)", "Atomic number : 46  \nGroup: Catalyst \nPhase @STP : Solid", "t is a silvery-white metal that does not tarnish in air. Soft and ductile when annealed, its strength and hardness increase with cold working. At room temperature, palladium can also absorb hydrogen in amounts up to 900 times its own volume."};
    elementDescriptions["Ag"] = {"Silver (Ag)", "Atomic number : 47  \nGroup: Catalyst \nPhase @STP : Solid", "Silver has been known since ancient times. It occurs natively and in argentite, horn silver, lead, lead-zinc, copper, gold, copper-nickel, and other ores."};
    elementDescriptions["Cd"] = {"Cadmium (Cd)", "Atomic number : 48  \nGroup: Catalyst \nPhase @STP : Solid", "Discovered in 1817, cadmium occurs in association with zinc ores. Almost all cadmium is a byproduct of processing ores for zinc, copper, and lead."};
    elementDescriptions["In"] = {"Indium (In)", "Atomic number : 49 \nGroup: P-Block \nPhase @STP : Solid", "Discovered spectroscopically in 1863 and isolated in 1864, indium is named for the indigo (blue) line in its spectrum. It is most frequently associated with zinc materials, is a by-product of zinc refinement, and can be found in iron, lead, and copper ores."};
    elementDescriptions["Sn"] = {"Tin (Sn)", "Atomic number : 50  \nGroup: P-Block \nPhase @STP : Solid", "Tin is also called stannum and has been known since ancient times. Found chiefly in the cassiterite ore, tin is obtained by processing the ore with coal in a reverberatory furnace."};
    elementDescriptions["Sb"] = {"Antimony (Sb)", "Atomic number : 51 \nGroup: P-Block \nPhase @STP : Solid", "Antimony was recognized in ancient times and has been known as a metal since at least the 17th century. Antimony is widespread and found in more than 100 minerals, most frequently in the form of sulfide stibnite."};
    elementDescriptions["Te"] = {"Tellerium (Te)", "Atomic number : 52  \nGroup: P-Block \nPhase @STP : Solid", "Discovered in 1782 and isolated in 1798, tellurium in its crystalline form is brittle and silvery-white with a metallic luster."};
    elementDescriptions["I"] = {"Iodine (I)", "Atomic number : 53  \nGroup: P-Block \nPhase @STP : Solid", "A bluish-black and lustrous solid, iodine at ambient temperatures turns into a blue-violet gas with a distinct odor. It forms compounds, but is less reactive than other halogens. Iodine has some metallic properties, is slightly water-soluble, and forms a purple solution when dissolved in chloroform, carbon tetrachloride, or carbon disulfide."};
    elementDescriptions["Xe"] = {"Xenon (Xe)", "Atomic number : 54  \nGroup: Noble Gas  \nPhase @STP : Gas", "Discovered in 1898, xenon is a noble or inert gas. It is present in the atmospheres of Earth and Mars and in gases from certain mineral springs."};


    //if the exit button (top right corner) is clicked, close the element card
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
    //set the appropriate images and information
    SetAssetContent(element);
    SetImageContent(element);
    SetKeyProperties(element);
    //then signal to display the element card
    emit RequestDisplayElementInfo();
}

void ElementInfo::ExitElement(){
    emit closeElement();
}

void ElementInfo::SetAssetContent(const QString &element)
{
    //get the image from the resources file and check that it is valid
    QImage assetImage(":/Elements/Elements/"+element+".png");
    if (assetImage.isNull()) {
        qDebug() << "Error loading asset image for element card";
    }
    else{
        // make the image the same size as the label that contains it
        QSize size(ui->elementAsset->width(), ui->elementAsset->height());
        QImage resizedImage = assetImage.scaled(size, Qt::KeepAspectRatio);

        //display the image on the label
        ui->elementAsset->setPixmap(QPixmap::fromImage(resizedImage));
    }
}


void ElementInfo::SetImageContent(const QString &element)
{

    //get the image from the resources file and check that it is valid
    QImage image(":/ElementImages/elementImages/"+element+"Image.jpg");
    if (image.isNull()) {
        qDebug() << "Error loading element image for element card";
    }
    else{
        //make the image the same size as the label that contains it
        QSize size(ui->elementImage->width(), ui->elementImage->height());
        QImage resizedImage = image.scaled(size, Qt::KeepAspectRatio);

        //display the image on the label
        ui->elementImage->setPixmap(QPixmap::fromImage(resizedImage));
    }
}

void ElementInfo::SetKeyProperties(const QString &element)
{
    //set the element name label to the name stored in the map
    ui->elementName->setText(elementDescriptions[element][0]);
    //set the key properties label to the properties stored in the map
    ui->keyProperties->setText(elementDescriptions[element][1]);
    //set the uses/facts label to the uses/facts stored in the map
    ui->uses->setText(elementDescriptions[element][2]);
}
