#pragma once


#include "HouseSensor.h"


class EzHomeSens200 : public SinglePointTemperatureSensor
{
public:
    EzHomeSens200(QHouseMap & house);

    QString deviceName() const override;
    QDeviceHMI* createHMI() override;
};



#include <QLabel>
#include <QPushButton>
#include <QLCDNumber>


class EzHomeSens200HMI : public QDeviceHMI
{
    Q_OBJECT

public:
    EzHomeSens200HMI(EzHomeSens200 & device);

protected:
    void updateDevice() override;

private:
    QLabel* mPowerStateLabel;
    QPushButton* mPowerOffButton;
    QPushButton* mPowerOnButton;
    QLCDNumber* mTempLCDNumber;

private slots:
    void turnOn();
    void turnOff();
};
