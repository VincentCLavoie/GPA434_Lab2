#pragma once



#include <QtWidgets/QMainWindow>
#include "ui_QSmartHouse.h"

//House Simulation Panel
#include "QHouseSimulationControlPanel.h"
#include "QHouseSimulationDevicePanel.h"
#include "QHouseSimulationGlobalInformationPanel.h"
#include "QHouseSimulationHistoryGraphPanel.h"
#include "QHouseSimulationTemperaturePanel.h"
#include "QHouseSimulationVisualisationPanel.h"


class QSmartHouse : public QMainWindow
{
    Q_OBJECT

public:
    QSmartHouse(QWidget *parent = Q_NULLPTR);

private:
    Ui::QSmartHouseClass ui;

    QHouseSimulationControlPanel* mHouseSimCtrPanel;
    QHouseSimulationDevicePanel* mHouseSimDevicePanel;
    QHouseSimulationGlobalInformationPanel* mHouseSimGlobalInfoPanel;
    QHouseSimulationHistoryGraphPanel* mHouseSimHistoryGraphPanel;
    QHouseSimulationTemperaturePanel* mHouseSimTempPanel;
    QHouseSimulationVisualisationPanel* mHouseSimVisualisationPanel;

    House1 mHouse;
};
