#pragma once

#include <QHouseMap.h>
#include <qsplitter.h>

#include <QtWidgets/QMainWindow>
#include "ui_QSmartHouse.h"

//House Simulation Panel
#include "QHouseSimulationControlPanel.h"
#include "QHouseSimulationDevicePanel.h"
#include "QHouseSimulationGlobalInformationPanel.h"
#include "QHouseSimulationHistoryGraphPanel.h"
#include "QHouseSimulationTemperaturePanel.h"
#include "QHouseSimulationVisualisationPanel.h"

//QVBoxLayout
#include <qwidget.h>
#include <qlayout.h>

//QHouseSimulationTemperaturePanel
#include <AnnualWeather.h>
#include <ExtremeAnnualWeather.h>
#include <TypicalMontrealAnnualWeather.h>

class QSmartHouse : public QMainWindow
{
    Q_OBJECT

public:
    QSmartHouse(QWidget *parent = Q_NULLPTR);

private:
    Ui::QSmartHouseClass ui;

    House1 mHouse;

    QHouseSimulationControlPanel* mHouseSimCtrlPanel;
    QHouseSimulationDevicePanel* mHouseSimDevicePanel;
    QHouseSimulationGlobalInformationPanel* mHouseSimGlobalInfoPanel;
    QHouseSimulationHistoryGraphPanel* mHouseSimHistoryGraphPanel;
    QHouseSimulationTemperaturePanel* mHouseSimTempPanel;
    QHouseSimulationVisualisationPanel* mHouseSimVisualisationPanel;

    
    
    
};
