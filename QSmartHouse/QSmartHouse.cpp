#include "QSmartHouse.h"




QSmartHouse::QSmartHouse(QWidget *parent)
    : QMainWindow(parent)
{
    // Initialise l'interface initiale
    ui.setupUi(this);

    // Initialise le titre et l'icône de la fenêtre
    setWindowTitle("Smart House");
    setWindowIcon(QIcon(":/QSmartHouse/HouseIcon"));

    // Vote code doit suivre ---v---
    
}