#include "descriptivecard.h"
#include "ui_descriptivecard.h"
#include "datamanager.h"

#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QTextEdit>
#include <QSlider>
#include <QRadioButton>
#include <QPushButton>
#include <QDate>

DescriptiveCard::DescriptiveCard(DataManager *dataManager, QString codeObject, QString key, QString selection, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DescriptiveCard),
    dataManager(dataManager)

{
    ui->setupUi(this);

    const QMap<QString, QMap<QString, QString> >* selectedMap;
    QMap<QString,QString> mapsOfKey;
    QMap<QString, QString> ::Iterator iterator;
    QString type;
    QString value;
    QString name;
    QStringList attributesOfCurrentConfig;
    QStringList attributesOfExportConfig;
    QStringList attributeNamesOfCurrentConfig;

    if(codeObject == "GAT")
    {
        this->setWindowTitle("Fiche descriptive d'Attribut");
        selectedMap = dataManager->getMapFromName("mapGAT");
        attributesOfExportConfig = dataManager->getAttributesOfExportConfig("GAT");

        if(selection == "current")
        {
            ui->label->setText("Fiche d'attribut pour la configuration courante: "+dataManager->getCurrentConfigNameGAT());
        }
        else if(selection == "complete")
        {
            ui->label->setText("Fiche complete d'attribut");
        }

        attributesOfCurrentConfig = dataManager->getAttributesOfCurrentConfig("GAT");
    }
    else if(codeObject == "GCA")
    {
        this->setWindowTitle("Fiche descriptive de Configuration d'Attribut");
        selectedMap = dataManager->getMapFromName("mapGCA");
        attributesOfExportConfig = dataManager->getAttributesOfExportConfig("GCA");

        if(selection == "current")
        {
            ui->label->setText("Fiche de configuration d'attributs pour la configuration courante: "+dataManager->getCurrentConfigNameGAT());
        }
        else if(selection == "complete")
        {
            ui->label->setText("Fiche complete de configuration d'attributs");
        }

        attributesOfCurrentConfig = dataManager->getAttributesOfCurrentConfig("GCA");
    }
    else if(codeObject == "GRS")
    {
        this->setWindowTitle("Fiche descriptive de Responsable");
        selectedMap = dataManager->getMapFromName("mapGRS");
        attributesOfExportConfig = dataManager->getAttributesOfExportConfig("GRS");

        if(selection == "current")
        {
            ui->label->setText("Fiche de responsable pour la configuration courante: "+dataManager->getCurrentConfigNameGAT());
        }
        else if(selection == "complete")
        {
            ui->label->setText("Fiche complete de responsable");
        }

        attributesOfCurrentConfig = dataManager->getAttributesOfCurrentConfig("GRS");
    }
    else if(codeObject == "GVE")
    {
        this->setWindowTitle("Fiche descriptive de Variable d'Environnement");
        selectedMap = dataManager->getMapFromName("mapGVE");
        attributesOfExportConfig = dataManager->getAttributesOfExportConfig("GVE");

        if(selection == "current")
        {
            ui->label->setText("Fiche de variable d'environnement pour la configuration courante: "+dataManager->getCurrentConfigNameGAT());
        }
        else if(selection == "complete")
        {
            ui->label->setText("Fiche complete de variable d'environnement");
        }

        attributesOfCurrentConfig = dataManager->getAttributesOfCurrentConfig("GVE");
    }
    else if(codeObject == "GDO")
    {
        this->setWindowTitle("Fiche descriptive de Document");
        selectedMap = dataManager->getMapFromName("mapGDO");
        attributesOfExportConfig = dataManager->getAttributesOfExportConfig("GDO");

        if(selection == "current")
        {
            ui->label->setText("Fiche de document pour la configuration courante: "+dataManager->getCurrentConfigNameGDO());
        }
        else if(selection == "complete")
        {
            ui->label->setText("Fiche complete de document");
        }

        attributesOfCurrentConfig = dataManager->getAttributesOfCurrentConfig("GDO");
    }


    mapsOfKey = selectedMap->value(key);

    attributeNamesOfCurrentConfig = dataManager->getAttributesOfCurrentConfigNames(attributesOfCurrentConfig);
    QString testName;
    QString nameAttributeSelected;
    const QMap<QString, QMap<QString, QString> > mapGAT = *dataManager->getMapFromName("mapGAT");
    QStringList list;
    QString baliseName;

    for(iterator = mapsOfKey.begin(); iterator != mapsOfKey.end(); ++iterator)
    {
        name = iterator.key();
        value = iterator.value();
        ++iterator;
        type = iterator.value();
        for(int i=0; i!=attributesOfExportConfig.length();i++)
        {
            testName = attributesOfExportConfig[i];
            baliseName = mapGAT[testName]["Titre"];
            list = baliseName.split(" ");
            baliseName = list[0];

            if(baliseName == name)
            {
                if(selection == "current")
                {
                    for(int j=0; j!=attributeNamesOfCurrentConfig.length();++j)
                    {
                        if(attributeNamesOfCurrentConfig[j]==name)
                        {
                            nameAttributeSelected = mapGAT[testName]["NomAttribut"];
                            setNewWidget(type, name, value, nameAttributeSelected);
                            break;
                        }
                    }
                }
                else if(selection == "complete")
                {
                    nameAttributeSelected = mapGAT[testName]["NomAttribut"];
                    setNewWidget(type, name, value, nameAttributeSelected);
                    break;
                }

            }

        }

        //++iterator;

    }


    ui->instructionsLabel->setText("Modifiez les attributs editables voulus et cliquez sur OK pour valider les modifications");

    QPalette Pal(palette());
    Pal.setColor(QPalette::Window, QColor(255,255,255,240));
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    this->show();
}



DescriptiveCard::~DescriptiveCard()
{
    delete ui;
}


void DescriptiveCard::setNewWidget(QString type, QString name, QString value, QString nameAttributeSelected)
{
    if(type == "string")
    {
        QLineEdit *lineEdit = new QLineEdit;
        QLabel *label = new QLabel;
        lineEdit->setText(value);
        //lineEdit->setGraphicsEffect();
        label->setText(nameAttributeSelected);
        label->setAccessibleName(name);
        ui->verticalLayout->addWidget(label);
        ui->verticalLayout->addWidget(lineEdit);
        lineEdit->setStyleSheet("background-color: hsv(120, 20, 255)");

    }
    else if(type == "stringF")
    {
        QLineEdit *lineEdit = new QLineEdit;
        QLabel *label = new QLabel;
        lineEdit->setText(value);
        lineEdit->setReadOnly(true);
        label->setText(nameAttributeSelected);
        label->setAccessibleName(name);
        lineEdit->setStyleSheet("background-color: hsv(0, 20, 255)");
        ui->verticalLayout->addWidget(label);
        ui->verticalLayout->addWidget(lineEdit);
    }
    else if(type == "int")
    {
        int valueInt = value.toInt();
        QSpinBox *spinBox = new QSpinBox;
        QLabel *label = new QLabel;
        label->setText(nameAttributeSelected);
        label->setAccessibleName(name);
        spinBox->setValue(valueInt);
        spinBox->setStyleSheet("background-color: hsv(120, 20, 255)");
        ui->verticalLayout->addWidget(label);
        ui->verticalLayout->addWidget(spinBox);
    }
    else if(type == "intF")
    {
        QLineEdit *lineEdit = new QLineEdit;
        QLabel *label = new QLabel;
        lineEdit->setText(value);
        lineEdit->setReadOnly(true);
        label->setText(nameAttributeSelected);
        label->setAccessibleName(name);
        lineEdit->setStyleSheet("background-color: hsv(0, 20, 255)");
        ui->verticalLayout->addWidget(label);
        ui->verticalLayout->addWidget(lineEdit);
    }
    else if(type == "date")
    {
        QLineEdit *lineEdit = new QLineEdit;
        QLabel *label = new QLabel;
        lineEdit->setText(value);
        lineEdit->setReadOnly(true);
        label->setText(nameAttributeSelected);
        label->setAccessibleName(name);
        lineEdit->setStyleSheet("background-color: hsv(0, 20, 255)");
        ui->verticalLayout->addWidget(label);
        ui->verticalLayout->addWidget(lineEdit);
    }

    else if(type == "time")
    {
        QLineEdit *lineEdit = new QLineEdit;
        QLabel *label = new QLabel;
        lineEdit->setText(value);
        lineEdit->setReadOnly(true);
        label->setText(nameAttributeSelected);
        label->setAccessibleName(name);
        lineEdit->setStyleSheet("background-color: hsv(0, 20, 255)");
        ui->verticalLayout->addWidget(label);
        ui->verticalLayout->addWidget(lineEdit);
    }
    else if(type == "indic")
    {
        QHBoxLayout *layout = new QHBoxLayout;
        QPushButton *pushButton1 = new QPushButton;
        pushButton1->setCheckable(true);
        QPushButton *pushButton2 = new QPushButton;
        pushButton2->setCheckable(true);
        pushButton1->setText("Oui");
        pushButton2->setText("Non");
        QLabel *label = new QLabel;
        layout->addWidget(pushButton1);
        layout->addWidget(pushButton2);

        if(pushButton1->text() == value)
        {
            pushButton1->setChecked(true);
        }
        else if(pushButton2->text() == value)
        {
            pushButton2->setChecked(true);
        }
        label->setText(nameAttributeSelected);
        label->setAccessibleName(name);

        connect(pushButton1,SIGNAL(released()),pushButton2,SLOT(toggle()));
        connect(pushButton2,SIGNAL(released()),pushButton1,SLOT(toggle()));

        ui->verticalLayout->addWidget(label);
        ui->verticalLayout->addWidget(pushButton1);
        ui->verticalLayout->addWidget(pushButton2);
    }
    else if(type == "cadrage")
    {
        QComboBox *comboBox = new QComboBox;
        QLabel *label = new QLabel;
        QStringList list = QStringList() << tr("Gauche") <<tr("Droite") <<tr("Centre");
        comboBox->addItems(list);
        int index = comboBox->findText(value);
        if(index >=0)
        {
            comboBox->setCurrentIndex(index);
        }
        label->setText(nameAttributeSelected);
        label->setAccessibleName(name);
        comboBox->setStyleSheet("background-color: hsv(120, 20, 255)");
        ui->verticalLayout->addWidget(label);
        ui->verticalLayout->addWidget(comboBox);
    }
    else if(type == "format")
    {
        QComboBox *comboBox = new QComboBox;
        QLabel *label = new QLabel;
        QStringList list = QStringList() << tr("L") <<tr("C");
        comboBox->addItems(list);
        int index = comboBox->findText(value);
        if(index >=0)
        {
            comboBox->setCurrentIndex(index);
        }
        label->setText(nameAttributeSelected);
        label->setAccessibleName(name);
        comboBox->setStyleSheet("background-color: hsv(120, 20, 255)");
        ui->verticalLayout->addWidget(label);
        ui->verticalLayout->addWidget(comboBox);
    }
    else if(type == "orient")
    {
        QComboBox *comboBox = new QComboBox;
        QLabel *label = new QLabel;
        QStringList list = QStringList() << tr("Paysage") <<tr("Portrait");
        comboBox->addItems(list);
        int index = comboBox->findText(value);
        if(index >=0)
        {
            comboBox->setCurrentIndex(index);
        }
        label->setText(nameAttributeSelected);
        label->setAccessibleName(name);
        comboBox->setStyleSheet("background-color: hsv(120, 20, 255)");
        ui->verticalLayout->addWidget(label);
        ui->verticalLayout->addWidget(comboBox);
    }
    else if(type == "comment")
    {
        QTextEdit *textEdit = new QTextEdit;
        QLabel *label = new QLabel;
        textEdit->setText(value);
        label->setText(nameAttributeSelected);
        label->setAccessibleName(name);
        textEdit->setStyleSheet("background-color: hsv(120, 20, 255)");
        ui->verticalLayout->addWidget(label);
        ui->verticalLayout->addWidget(textEdit);
    }
    else if(type == "largeur")
    {
        int valueInt = value.toInt();
        QSpinBox *spinBox = new QSpinBox;
        QSlider *slider = new QSlider;
        slider->setOrientation(Qt::Horizontal);
        QLabel *label = new QLabel;
        connect(slider,SIGNAL(valueChanged(int)), spinBox,SLOT(setValue(int)));
        connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
        label->setText(nameAttributeSelected);
        label->setAccessibleName(name);
        spinBox->setValue(valueInt);
        spinBox->setStyleSheet("background-color: hsv(120, 20, 255)");
        ui->verticalLayout->addWidget(label);
        ui->verticalLayout->addWidget(spinBox);
        ui->verticalLayout->addWidget(slider);
    }
    else
    {
        QLineEdit *lineEdit = new QLineEdit;
        QLabel *label = new QLabel;
        lineEdit->setText(value);
        lineEdit->setReadOnly(true);
        label->setText(nameAttributeSelected);
        label->setAccessibleName(name);
        ui->verticalLayout->addWidget(label);
        ui->verticalLayout->addWidget(lineEdit);

    }

}


