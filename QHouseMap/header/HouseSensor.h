#pragma once


#include "HouseDevice.h"


// Classe repr�sentant un capteur
class HouseSensor : public HouseDevice
{
public:
    HouseSensor(QHouseMap& house);

    virtual double measure() const = 0;
};


// Classe repr�sentant un capteur de temp�rature avec un seul point de lecture.
class SinglePointTemperatureSensor : public HouseSensor
{
public:
    SinglePointTemperatureSensor(QHouseMap & house);

    QSize size() const override;

    double measure() const override;
};