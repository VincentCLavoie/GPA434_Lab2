#pragma once



#include <QtWidgets/QMainWindow>
#include "ui_QSmartHouse.h"




class QSmartHouse : public QMainWindow
{
    Q_OBJECT

public:
    QSmartHouse(QWidget *parent = Q_NULLPTR);

private:
    Ui::QSmartHouseClass ui;
};
