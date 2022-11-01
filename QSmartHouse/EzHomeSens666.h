#pragma once


#include "HouseSensor.h"


class EzHomeSens666 : public SinglePointTemperatureSensor
{
public:
    EzHomeSens666(QHouseMap & house);

    QString deviceName() const override;
    QDeviceHMI* createHMI() override;
};


class EzHomeSens666HMI : public QPaintDeviceHMI
{
    Q_OBJECT

public:
    EzHomeSens666HMI(EzHomeSens666 & device);

protected:
    void paint(QPainter & painter) override;
};

