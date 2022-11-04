#include "QSmartHouse.h"

QSmartHouse::QSmartHouse(QWidget* parent)
    : QMainWindow(parent),
    mHouse(),
    mHouseSimCtrlPanel{ new QHouseSimulationControlPanel(mHouse) },
    mHouseSimDevicePanel{ new QHouseSimulationDevicePanel(mHouse) },
    mHouseSimGlobalInfoPanel{ new QHouseSimulationGlobalInformationPanel(mHouse) },
    mHouseSimHistoryGraphPanel{ new QHouseSimulationHistoryGraphPanel(mHouse) },
    mHouseSimTempPanel{ new QHouseSimulationTemperaturePanel(mHouse) },
    mHouseSimVisualisationPanel{ new QHouseSimulationVisualisationPanel(mHouse) }
{
    // Initialise l'interface initiale
    ui.setupUi(this);

    // Initialise le titre et l'icône de la fenêtre
    setWindowTitle("Smart House");
    setWindowIcon(QIcon(":/QSmartHouse/HouseIcon"));

    
    // 1) Utiliser un agencement vertical pour la partie
    // gauche du GUI
    QVBoxLayout* controlLayout{ new QVBoxLayout };
    // 1.1) Ajouter le contrôle de la simulation
    controlLayout->addWidget(mHouseSimCtrlPanel);
    // 1.2) Ajouter le contrôle de la gestion de
    // la température annuelle
    controlLayout->addWidget(mHouseSimTempPanel);
    // 1.3) Ajouter une élongation (stretch).
    // Voir page 7 du cahier de laboratoire
    controlLayout->addStretch();
    // 1.4) Ajouter l'affichage des statistiques
    controlLayout->addWidget(mHouseSimGlobalInfoPanel);


    QSplitter* splitter{ new QSplitter };
    splitter->setOrientation(Qt::Vertical);
    // 2.1) Ajouter le contrôle de l'affichage du plan
    // d'une résidence et sa carte de température.
    splitter->addWidget(mHouseSimVisualisationPanel);
    // 2.2) Ajouter le contrôle de l'affichage de
    // l'historique de la température
    splitter->addWidget(mHouseSimHistoryGraphPanel);
    // 2.3) Indiquer le comportement du splitter lors des redimensionnements
    // de la fenêtre en largeur et en hauteur.
    // Voir: https://doc.qt.io/qt-5/qsizepolicy.html#details
    // Ici le splitter a une taille:
    // - horizontale qui est minimale et pourrait profiter de l'espace pour agrandir;
    // - verticale qui est de bonne taille et ne souhaiterait pas agrandir.
    splitter->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    // 2.4) Régler la hauteur des widgets dans le splitter. Ici, on les règle à la valeur
    // maximale. Qt fera le nécessaire pour régler la hauteur des widgets convenablement.
    splitter->setSizes(QList<int>({ INT_MAX, INT_MAX }));


    // 3) la partie gauche du GUI à l'aide d’un
    // agencement vertical
    QVBoxLayout* deviceLayout{ new QVBoxLayout };
    // 3.1) Ajouter le contrôle des sources de
    // chauffage/refroidissement et des capteurs de
    // température.
    // 3.2) Ajouter une élongation (stretch). Voir page
    // 7 du cahier de laboratoire
    // 3.3) Ajouter le bouton "À propos"
    QPushButton* about{ new QPushButton("À propos...") };
    deviceLayout->addWidget(about);


    QWidget* centralWidget{ new QWidget };
    // 4.1) Assembler horizontalement de la gauche à vers la droite
    QHBoxLayout* centralLayout{ new QHBoxLayout };
    centralLayout->addLayout(controlLayout); // assemblage à gauche
    centralLayout->addWidget(splitter); // assemblage au milieu
    centralLayout->addLayout(deviceLayout); // assemblage à droite
    // 4.2) Insérer les assemblages dans le widget principal de la fenêtre
    centralWidget->setLayout(centralLayout);
    // 4.3) Insérer le widget principal dans la fenêtre
    setCentralWidget(centralWidget);


    //QHouseSimulationTemperature Panel
    mHouseSimTempPanel->add(new TypicalMontrealAnnualWeather);
    mHouseSimTempPanel->add(new ExtremeAnnualWeather);
}