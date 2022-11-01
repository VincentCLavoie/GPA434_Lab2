#pragma once


#include <QWidget>
#include "QInteractiveDataViewer.h"
#include <QButtonGroup>
#include <QPushButton>
#include <QHouseMap.h>
#include <AnnualWeather.h>


class QHouseSimulationVisualisationPanel : public QWidget
{
public:
    QHouseSimulationVisualisationPanel(QHouseMap & houseMap, QWidget * parent = nullptr);
    ~QHouseSimulationVisualisationPanel();

public slots:
    void updateView();
    void setDeviceId(int id);

private:
    QHouseMap & mHouseMap;
    int mDeviceId;
    QInteractiveDataViewer * mInteractiveDataViewer;
    QButtonGroup * mButtonGroup;
    QPushButton * mHousePlanRadioButton;
    QPushButton * mTemperatureRadioButton;
};

