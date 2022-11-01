#pragma once


#include "HouseDevice.h"


// Classe représentant un capteur
class HouseSensor : public HouseDevice
{
public:
    HouseSensor(QHouseMap& house);

    virtual double measure() const = 0;
};


// Classe représentant un capteur de température avec un seul point de lecture.
class SinglePointTemperatureSensor : public HouseSensor
{
public:
    SinglePointTemperatureSensor(QHouseMap & house);

    QSize size() const override;

    double measure() const override;
};