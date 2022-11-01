#pragma once


#include "HouseActuator.h"


class EzHomeThermal200 : public OnOffHeatPump
{
public:
    EzHomeThermal200(QHouseMap & house);

    QSize size() const override;
    QString deviceName() const override;
    QDeviceHMI* createHMI() override;
};



#include <QLabel>
#include <QPushButton>
#include <QScrollBar>


class EzHomeThermal200HMI : public QDeviceHMI
{
    Q_OBJECT

public:
    EzHomeThermal200HMI(EzHomeThermal200 & device);

protected:
    void updateDevice() override;

private:
    QLabel* mPowerStateLabel;
    QLabel* mActiveStateLabel;
    QPushButton* mPowerOffButton;
    QPushButton* mPowerOnButton;
    QPushButton* mActiveOffButton;
    QPushButton* mActiveOnButton;
    QScrollBar* mThermalSetPointSB;
    QLabel* mThermalSetPointLabel;

private slots:
    void turnPowerOn();
    void turnPowerOff();
    void turnActiveOn();
    void turnActiveOff();
    void setThermalPoint();
};
